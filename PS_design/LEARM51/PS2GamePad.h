#ifndef _PS2_GAME_PAD_H_
#define _PS2_GAME_PAD_H_


#define DI   P21           //P12输入

#define DO_H P22=1        //命令位高
#define DO_L P22=0        //命令位低

#define CS_H P23=1       //CS拉高
#define CS_L P23=0       //CS拉低

#define CLK_H P20=1      //时钟拉高
#define CLK_L P20=0      //时钟拉低


//These are our button constants
#define PSB_SELECT      1
#define PSB_L3          2
#define PSB_R3          3
#define PSB_START       4
#define PSB_PAD_UP      5
#define PSB_PAD_RIGHT   6
#define PSB_PAD_DOWN    7
#define PSB_PAD_LEFT    8
#define PSB_L2			9
#define PSB_R2          10
#define PSB_L1          11
#define PSB_R1          12
#define PSB_TRIANGLE    13	//三角形
#define PSB_CIRCLE      14	//圆圈
#define PSB_CROSS       15	//叉叉
#define PSB_SQUARE      16	//方框

//#define WHAMMY_BAR		8

//These are stick values
#define PSS_RX 5                //右摇杆X轴数据
#define PSS_RY 6
#define PSS_LX 7
#define PSS_LY 8



u8 InitPS2(void);
u8 PS2_RedLight(void);//判断是否为红灯模式
void PS2_ReadData(void);
void PS2_Cmd(u8 CMD);		  //
u8 PS2_DataKey(void);		  //键值读取
u8 PS2_AnologData(u8 button); //得到一个摇杆的模拟量
void PS2_ClearData(void);	  //清除数据缓冲区
void PS2_Vibration(u8 motor1, u8 motor2);//振动设置motor1  0xFF开，其他关，motor2  0x40~0xFF

void PS2_EnterConfing(void);	 //进入配置
void PS2_TurnOnAnalogMode(void); //发送模拟量
void PS2_VibrationMode(void);    //振动设置
void PS2_ExitConfing(void);	     //完成配置
u8 PS2_SetInit(void);		     //配置初始化

bool PS2_Button(u16 button);
bool PS2_ButtonPressed(u16 button);
bool PS2_NewButtonState(u16 button);
#endif
