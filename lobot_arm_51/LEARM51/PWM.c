#include "include.h"


			
uint16 xdata ServoPwmDuty[8] = {1500,1500,1500,1050,1000,1700,1500,1500};	//PWM脉冲宽度
uint16 ServoPwmDutySet[8] = {1500,1500,1500,1050,1000,1700,1500,1500};	//PWM脉冲宽度
float xdata ServoPwmDutyInc[8];		//为了速度控制，当PWM脉宽发生变化时，每2.5ms或20ms递增的PWM脉宽

bool ServoPwmDutyHaveChange = FALSE;	//脉宽有变化标志位

uint16 ServoTime = 2000;			//舵机从当前角度运动到指定角度的时间，也就是控制速度


void ServoSetPluseAndTime(uint8 id,uint16 p,uint16 time)
{
	if(id >= 0 && id <= 7 && p >= 500 && p <= 2500)
	{
		if(time < 20)
			time = 20;
		if(time > 30000)
			time = 30000;

		ServoPwmDutySet[id] = p;
		ServoTime = time;
		ServoPwmDutyHaveChange = TRUE;
	}
}


void ServoSetPluseAndTime_my(uint8 id,uint8 dir,uint8 mul)
{	
	uint16 p_my;
	uint16 time;
	time=20*mul;
	/*	if(time < 20)
			time = 20;
		if(time > 30000)
			time = 30000;*/
	if(dir==0) 
		p_my=ServoPwmDutySet[id]-mul;
	else 
		p_my=ServoPwmDutySet[id]+mul;
		
/*	if(p_my >= 500 && p_my <= 2500)
		{
		ServoPwmDutySet[id] = p_my;
		ServoTime = time;
		ServoPwmDutyHaveChange = TRUE;
	}*/
	ServoSetPluseAndTime( id, p_my, time);
}

void ServoPwmDutyCompare(void)//脉宽变化比较及速度控制
{
	uint8 i;
	
	static uint16 ServoPwmDutyIncTimes;	//需要递增的次数
	static bool ServoRunning = FALSE;	//舵机正在以指定速度运动到指定的脉宽对应的位置
	if(ServoPwmDutyHaveChange)//停止运动并且脉宽发生变化时才进行计算      ServoRunning == FALSE && 
	{
		ServoPwmDutyHaveChange = FALSE;
		ServoPwmDutyIncTimes = ServoTime/20;	//当每20ms调用一次ServoPwmDutyCompare()函数时用此句
		for(i=0;i<8;i++)
		{
			//if(ServoPwmDuty[i] != ServoPwmDutySet[i])
			{
				if(ServoPwmDutySet[i] > ServoPwmDuty[i])
				{
					ServoPwmDutyInc[i] = ServoPwmDutySet[i] - ServoPwmDuty[i];
					ServoPwmDutyInc[i] = -ServoPwmDutyInc[i];
				}
				else
				{
					ServoPwmDutyInc[i] = ServoPwmDuty[i] - ServoPwmDutySet[i];
					
				}
				ServoPwmDutyInc[i] /= ServoPwmDutyIncTimes;//每次递增的脉宽
			}
		}
		ServoRunning = TRUE;	//舵机开始动作
	}
	if(ServoRunning)
	{
		ServoPwmDutyIncTimes--;
		for(i=0;i<8;i++)
		{
			if(ServoPwmDutyIncTimes == 0)
			{		//最后一次递增就直接将设定值赋给当前值

				ServoPwmDuty[i] = ServoPwmDutySet[i];

				ServoRunning = FALSE;	//到达设定位置，舵机停止运动
			}
			else
			{

				ServoPwmDuty[i] = ServoPwmDutySet[i] + 
					(signed short int)(ServoPwmDutyInc[i] * ServoPwmDutyIncTimes);

			}
		}
		
	}
}



void InitTimer0(void)
{
// 	AUXR &= 0x7F;		//定时器时钟12T模式
// 	AUXR |= 0x00;		//T0,T1工作在12T
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x00;			//设置定时初值
	TH0 = 0x00;			//设置定时初值
	TF0 = 0;			//清除TF0标志
	TR0 = 1;			//定时器0开始计时
	ET0 = 1;			//开定时器0中断

	PT0 = 1;
}


void InitPWM(void)
{
	InitTimer0();
	P2M0 |= 0x10;	//设置推挽输出
	P3M0 |= 0x7C;
	P5M0 |= 0x30;
}

void Timer0Value(uint16 pwm)
{
	uint16 value;
	value=0xffff-pwm;
	TR0 = 0;			//
	TL0=value;			//16位数据给8位数据赋值默认将16位数据的低八位直接赋给八位数据
    TH0=value>>8;		//将16位数据右移8位，也就是将高8位移到低八位，再赋值给8位数据
    TR0 = 1;			//定时器0开始计时
}





void Timer0_isr(void) interrupt 1// using 1
{
	static uint16 i = 1;	//静态变量：每次调用函数时保持上一次所赋的值，
							//跟全局变量类似，不同是它只能用于此函数内部
	switch(i)
	{
		case 1:
//			SERVO0 = 1;	//PWM控制脚高电平
			//给定时器0赋值，计数Pwm0Duty个脉冲后产生中断，下次中断会进入下一个case语句
			Timer0Value(ServoPwmDuty[0]);	
			break;
		case 2:
//			SERVO0 = 0;	//PWM控制脚低电平
			//此计数器赋值产生的中断表示下一个单元要进行任务的开始
			Timer0Value(2500-ServoPwmDuty[0]);	
			break;
		case 3:
			SERVO1 = 1;	
			Timer0Value(ServoPwmDuty[1]);	
			break;
		case 4:
			SERVO1 = 0;	//PWM控制脚低电平
			Timer0Value(2500-ServoPwmDuty[1]);	
			break;
		case 5:
			SERVO2 = 1;	
			Timer0Value(ServoPwmDuty[2]);	
			break;
		case 6:
			SERVO2 = 0;	//PWM控制脚低电平
			Timer0Value(2500-ServoPwmDuty[2]);	
			break;	
		case 7:
			SERVO3 = 1;	
			Timer0Value(ServoPwmDuty[3]);	
			break;
		case 8:
			SERVO3 = 0;	//PWM控制脚低电平
			Timer0Value(2500-ServoPwmDuty[3]);	
			break;	
		case 9:
			SERVO4 = 1;	
			Timer0Value(ServoPwmDuty[4]);	
			break;
		case 10:
			SERVO4 = 0;	//PWM控制脚低电平
			Timer0Value(2500-ServoPwmDuty[4]);	
			break;	
		case 11:
			SERVO5 = 1;	
			Timer0Value(ServoPwmDuty[5]);	
			break;
		case 12:
			SERVO5 = 0;	//PWM控制脚低电平
			Timer0Value(2500-ServoPwmDuty[5]);	
			break;
		case 13:
 			SERVO6 = 1;	
			Timer0Value(ServoPwmDuty[6]);	
			break;
		case 14:
 			SERVO6 = 0;	//PWM控制脚低电平
			Timer0Value(2500-ServoPwmDuty[6]);	
			break;
		case 15:
// 			SERVO7 = 1;	
			Timer0Value(ServoPwmDuty[7]);	
			break;
		case 16:
// 			SERVO7 = 0;	//PWM控制脚低电平
			Timer0Value(2500-ServoPwmDuty[7]);
			i = 0;	
			break;				 
	}
	i++;
}

