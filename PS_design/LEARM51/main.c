#include "include.h"

//作者:深圳市乐幻索尔科技有限公司
//我们的店铺:lobot-zone.taobao.com
//系统运行的晶振频率为12M
void main(void)
{
	uint8 ps_ok = 1;
	P0M1=P0M0=P1M1=P1M0=P2M1=P2M0=P3M1=P3M0=P4M1=P4M0=P5M1=P5M0=P6M1=P6M0=P7M1=P7M0= 0;	
	//全部设置成准双向口
	
	InitPWM();		//里面有初始化Timer0，初始化舵机的PWM，

	InitTimer3();	//初始化Timer3,用于产生100us的定时中断
	InitUart1();	//波特率 用Timer1产生，用于与PC端进行通信
  InitUart2();
	InitADC();
	InitBusServoCtrl();
	
	P3M0 |= 0x80;	//蜂鸣器控制引脚推挽输出
	EA = 1;			//开总中断
	LED = LED_ON;
	ps_ok = InitPS2();//PS2游戏手柄接收器初始化
	InitFlash();
	InitMemory();
	
	BusServoCtrl(1,SERVO_MOVE_TIME_WRITE,500,1000);
	BusServoCtrl(2,SERVO_MOVE_TIME_WRITE,500,1000);
	BusServoCtrl(3,SERVO_MOVE_TIME_WRITE,500,1000);
	BusServoCtrl(4,SERVO_MOVE_TIME_WRITE,500,1000);
	BusServoCtrl(5,SERVO_MOVE_TIME_WRITE,500,1000);
	BusServoCtrl(6,SERVO_MOVE_TIME_WRITE,500,1000);
	for(;;)
	{
		TaskRun(ps_ok);
	}
}

