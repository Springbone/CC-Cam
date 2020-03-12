/*****************************************************************************
 ** File			: ApiPS2GamePad.c
 ** Author			: Zheng23
 ** Date			: 			
 ** Function		: PS2游戏手柄接收器驱动
/*****************************************************************************/
#include "include.h"


u16 xdata Handkey;
u16 xdata Lastkey;
u8 xdata Comd[2]={0x01,0x42};	//开始命令。请求数据
u8 xdata Data[9]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; //数据存储数组
u8 ps2_ok = 0;

u16 code MASK[]={
    PSB_SELECT,
    PSB_L3,
    PSB_R3 ,
    PSB_START,
    PSB_PAD_UP,
    PSB_PAD_RIGHT,
    PSB_PAD_DOWN,
    PSB_PAD_LEFT,
    PSB_L2,
    PSB_R2,
    PSB_L1,
    PSB_R1 ,
    PSB_TRIANGLE,
    PSB_CIRCLE,
    PSB_CROSS,
    PSB_SQUARE
	};	//按键值与按键明



static void Delay(unsigned char time)
{
	time *=1;
	while(--time);
}

u8 InitPS2(void)
{
	u8 mode;
	P2M0 |= ((1 << 2) | (1 << 3) | 1);
	P2M1 &= ~((1 << 2) | (1 << 3) | 1);
	mode = PS2_SetInit();		 //配配置初始化,配置“红绿灯模式”，并选择是否可以修改	
	return mode;	
}

//向手柄发送命令
void PS2_Cmd(u8 CMD)
{
	u16 ref=0x01;
	Data[1] = 0;
	for(ref=0x01;ref<0x0100;ref<<=1)
	{
		if(ref&CMD)
		{
			DO_H;                   //输出以为控制位
		}
		else DO_L;

		Delay(10);
		CLK_L;
		Delay(40);
		CLK_H;
		if(DI)
			Data[1] = ref|Data[1];
		Delay(10);
	}
}
//判断是否为红灯模式
//返回值；0，红灯模式
//		  其他，其他模式
u8 PS2_RedLight(void)
{
	CS_L;
	PS2_Cmd(Comd[0]);  //开始命令
	PS2_Cmd(Comd[1]);  //请求数据
	CS_H;
	if( Data[1] == 0X73)   return 0 ;
	else return 1;

}
//读取手柄数据
void PS2_ReadData(void)
{
	u8 byte;
	u16 ref;

	CS_L;
	Delay(10);
	PS2_Cmd(Comd[0]);  //开始命令
	PS2_Cmd(Comd[1]);  //请求数据

	for(byte=2;byte<9;byte++)          //开始接受数据
	{
		for(ref=0x01;ref<0x100;ref<<=1)
		{

			CLK_L;
				Delay(50);
			CLK_H;
		      if(DI)
		      {
				Data[byte] = ref|Data[byte];
			  }
		    Delay(45); 
		}
			Delay(10);
	}
	CS_H;
}

//对读出来的PS2的数据进行处理      只处理了按键部分         默认数据是红灯模式  只有一个按键按下时
//按下为0， 未按下为1
u8 PS2_DataKey()
{
	u8 index;
  Lastkey = Handkey;
	PS2_ClearData();
	PS2_ReadData();

	Handkey=(Data[4]<<8)|Data[3];     //这是16个按键  按下为0， 未按下为1
	for(index=0;index<16;index++)
	{	    
		if((Handkey&(1<<(MASK[index]-1)))==0)
		return index+1;
	}
	return 0;          //没有任何按键按下
}
bool PS2_NewButtonState( u16 button )
{
  button = 0x0001u << ( button - 1 );  //输入的button的值是 该按键在数据中所在bit的值+1， 例如 PSB_SELECT 宏的值 是 1， 在数据中的位是0位， 如此类推，
  return ( ( ( Lastkey ^ Handkey ) & button ) > 0 );  //将上次的按键数据和这次的按键数据进行异或运算，结果就是两次不同的部分会是1，就得到了状态发生了变化的按键
	                                                    //然后在与我们想要检测的按键进行与运算，如果这个按键发生了变化，那么结果就是1， 大于0，所以返回就是true
}

bool PS2_Button( u16 button )
{
  button = 0x0001u << ( button - 1 );  //输入的button的值是 该按键在数据中所在bit的值+1， 例如 PSB_SELECT 宏的值 是 1， 在数据中的位是0位， 如此类推，
  return ( ( (~Handkey) & button ) > 0 );  //按键按下则对应位为0，没按下为1， 将按键数据取反之后，就变成了按键为1，没按下为0
	                                         //再与我们想要检测的按键做与运算，若这个按键被按下，对应位就是1，没按下就是0，返回与0比较的结果，
}
bool PS2_ButtonPressed( u16 button )
{
  return (PS2_NewButtonState( button ) && PS2_Button( button ));  //按键被按住，并且这个是按键的一个新的状态，那么就是按键刚被按下
}

//得到一个摇杆的模拟量	 范围0~256
u8 PS2_AnologData(u8 button)
{
	return Data[button];
}

//清除数据缓冲区
void PS2_ClearData()
{
	u8 a;
	for(a=0;a<9;a++)
		Data[a]=0x00;
}
/******************************************************
Function:    void PS2_Vibration(u8 motor1, u8 motor2)
Description: 手柄震动函数，
Calls:		 void PS2_Cmd(u8 CMD);
Input: motor1:右侧小震动电机 0x00关，其他开
	   motor2:左侧大震动电机 0x40~0xFF 电机开，值越大 震动越大
******************************************************/
void PS2_Vibration(u8 motor1, u8 motor2)
{
	CS_L;
	Delay(50);
    PS2_Cmd(0x01);  //开始命令
	PS2_Cmd(0x42);  //请求数据
	PS2_Cmd(0X00);
	PS2_Cmd(motor1);
	PS2_Cmd(motor2);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	CS_H;
	Delay(50);  
}
//short poll
void PS2_ShortPoll(void)
{
	CS_L;
	Delay(50);
	PS2_Cmd(0x01);  
	PS2_Cmd(0x42);  
	PS2_Cmd(0X00);
	PS2_Cmd(0x00);
	PS2_Cmd(0x00);
	CS_H;
	Delay(50);	
}
//进入配置
void PS2_EnterConfing(void)
{
    CS_L;
	Delay(50);
	PS2_Cmd(0x01);  
	PS2_Cmd(0x43);  
	PS2_Cmd(0X00);
	PS2_Cmd(0x01);
	PS2_Cmd(0x00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	CS_H;
	Delay(50);
}
//发送模式设置
void PS2_TurnOnAnalogMode(void)
{
	CS_L;
	Delay(50);
	PS2_Cmd(0x01);  
	PS2_Cmd(0x44);  
	PS2_Cmd(0X00);
	PS2_Cmd(0x01); //analog=0x01;digital=0x00  软件设置发送模式
	PS2_Cmd(0x03); //Ox03锁存设置，即不可通过按键“MODE”设置模式。
				   //0xEE不锁存软件设置，可通过按键“MODE”设置模式。
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	CS_H;
	Delay(50);
}
//振动设置
void PS2_VibrationMode(void)
{
	CS_L;
	Delay(50);
	PS2_Cmd(0x01);  
	PS2_Cmd(0x4D);  
	PS2_Cmd(0X00);
	PS2_Cmd(0x00);
	PS2_Cmd(0X01);
	CS_H;
	Delay(50);	
}
//完成并保存配置
void PS2_ExitConfing(void)
{
    CS_L;
	Delay(50);
	PS2_Cmd(0x01);  
	PS2_Cmd(0x43);  
	PS2_Cmd(0X00);
	PS2_Cmd(0x00);
	PS2_Cmd(0x5A);
	PS2_Cmd(0x5A);
	PS2_Cmd(0x5A);
	PS2_Cmd(0x5A);
	PS2_Cmd(0x5A);
	CS_H;
	Delay(50);
}
//手柄配置初始化
u8 PS2_SetInit(void)
{	
	LED = LED_ON;
	PS2_ShortPoll();
	PS2_ShortPoll();
	PS2_ShortPoll();
	PS2_EnterConfing();		//进入配置模式
	PS2_TurnOnAnalogMode();	//“红绿灯”配置模式，并选择是否保存	


	PS2_VibrationMode();	//开启震动模式
	PS2_ExitConfing();		//完成并保存配置	
	if (PS2_RedLight() == 0)
		return 0;
	else
		return 1;
}

