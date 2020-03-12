#include "include.h"
//作者:深圳市乐幻索尔科技有限公司
//我们的店铺:lobot-zone.taobao.com


#define ADC_POWER   0x80            //ADC电源控制位
#define ADC_FLAG    0x10            //ADC完成标志
#define ADC_START   0x08            //ADC起始控制位
#define ADC_SPEEDLL 0x00            //540个时钟
#define ADC_SPEEDL  0x20            //360个时钟
#define ADC_SPEEDH  0x40            //180个时钟
#define ADC_SPEEDHH 0x60            //90个时钟

#define ADC_BAT		6		//电池电压的AD检测通道
static bool UartBusy = FALSE;

u32 gSystemTickCount = 0;	//系统从启动到现在的毫秒数

uint8 BuzzerState = 0;
uint8 Mode = 0;
uint16 xdata Ps2TimeCount = 0;

uint16 xdata BatteryVoltage;

void DelayMs(uint16 ms)
{
	uint16 i,j;
	for(i=0;i<800;i++)
		for(j=0;j<ms;j++);
}


void InitADC(void)
{
    P1ASF = 0x40;                   //
    ADC_RES = 0;                    //清除结果寄存器
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL;
    //Delay(2);                       //ADC上电并延时
}


uint16 GetADCResult(BYTE ch)
{
	uint16 ad;
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ch | ADC_START;
    _nop_();                        //等待4个NOP
    _nop_();
    _nop_();
    _nop_();
    while (!(ADC_CONTR & ADC_FLAG));//等待ADC转换完成
    ADC_CONTR &= ~ADC_FLAG;         //Close ADC
    
    ad = ADC_RES;
	ad = (ad << 2) + (ADC_RESL & 0x03);
	return ad;
}



void InitTimer3(void)		//100us@12.000MHz
{
	T4T3M |= 0x02;
	T3L = 0x50;
	T3H = 0xFB;
	T4T3M |= 0x08;
	IE2 |= 0x20;
}




void CheckBatteryVoltage(void)
{
	uint8 i;
	uint32 v = 0;
	for(i = 0;i < 8;i++)
	{
		v += GetADCResult(ADC_BAT);
	}
	v >>= 3;
	
	v = v * 2475 / 256;//adc / 1024 * 3300 * 3(3代表放大3倍，因为采集电压时电阻分压了)
	BatteryVoltage = v;
}

uint16 GetBatteryVoltage(void)
{//电压毫伏
	return BatteryVoltage;
}

void Buzzer(void)
{//放到100us的定时中断里面
	static bool fBuzzer = FALSE;
	static uint32 t1 = 0;
	static uint32 t2 = 0;
	if(fBuzzer)
	{
		if(++t1 >= 2)
		{
			t1 = 0;
			BUZZER = !BUZZER;//2.5KHz
		}
	}
	else
	{
		BUZZER = 0;
	}

	
	if(BuzzerState == 0)
	{
		fBuzzer = FALSE;
		t2 = 0;
	}
	else if(BuzzerState == 1)
	{
		t2++;
		if(t2 < 5000)
		{
			fBuzzer = TRUE;
		}
		else if(t2 < 10000)
		{
			fBuzzer = FALSE;
		}
		else
		{
			t2 = 0;
		}
	}
}

bool  manual = FALSE;
void t3int() interrupt 19
{//定时器3中断  100us
	static uint16 time = 0;
	static uint16 timeBattery = 0;

	Buzzer();
	if(++time >= 10)
	{
		time = 0;
		gSystemTickCount++;
		Ps2TimeCount++;
		if(GetBatteryVoltage() < 6400)//小于6.4V报警
		{
			timeBattery++;
			if(timeBattery > 5000)//持续5秒
			{
				BuzzerState = 1;
			}
		}
		else
		{
			timeBattery = 0;
			if ( manual == FALSE)
			{
				BuzzerState = 0;
			}
		}
	}
}

void TaskTimeHandle(void)
{
	static uint32 time = 10;
	static uint32 times = 0;
	if(gSystemTickCount > time)
	{
		time += 10;
		times++;
		if(times % 2 == 0)//20ms
		{
			ServoPwmDutyCompare();
		}
	}
	
}

int16 BusServoPwmDutySet[8] = {500,500,500,500,500,500,500,500};
uint8 xdata i;
void TaskRun(u8 ps2_ok)
{
	static bool Ps2State = FALSE;
	uint8 PS2KeyValue;
	static uint8 keycount = 0;
	TaskTimeHandle();
	CheckBatteryVoltage();
	TaskPCMsgHandle();
	TaskBLEMsgHandle();
	TaskRobotRun();
	
	
	if(KEY == 0)
	{
		DelayMs(60);
		{
			if(KEY == 0)
			{
				keycount++;
			}
			else
			{
				if (keycount > 20)
				{
					keycount = 0;
					FullActRun(100,0);
					return;
				}
				else
				{
					keycount = 0;
					LED = ~LED;
					FullActRun(100,1);	
				}
			}
		}
	}

if (ps2_ok	== 0)
{
	if(Ps2TimeCount > 50)
		{
			
			Ps2TimeCount = 0;
			PS2KeyValue = PS2_DataKey();
			if(Mode == 0)
			{
				if( PS2_Button( PSB_SELECT ) & PS2_ButtonPressed( PSB_START ) )
				{
					FullActStop();  //停止动作组运行
					ServoSetPluseAndTime( 1, 1500, 1000 );  //将机械臂的舵机都转到1500的位置
					ServoSetPluseAndTime( 2, 1500, 1000 );
					ServoSetPluseAndTime( 3, 1500, 1000 );
					ServoSetPluseAndTime( 4, 1500, 1000 );
					ServoSetPluseAndTime( 5, 1500, 1000 );
					ServoSetPluseAndTime( 6, 1500, 1000 );
					for (i = 1; i < 7; i++)
						BusServoCtrl(i,SERVO_MOVE_TIME_WRITE,500,1000);
					Mode = 1;
					Ps2State = 1;
					manual = TRUE;
					BuzzerState = 1;
					LED=~LED;
					DelayMs(80);
					manual = FALSE;
					DelayMs(50);
					manual = TRUE;
					BuzzerState = 1;
					DelayMs(80);
					manual = FALSE;
					LED=~LED;
				}
				else
				{
					if(PS2KeyValue && !PS2_Button(PSB_SELECT))
				{
					LED=~LED;
				}
							
					switch( PS2KeyValue )
							{
								//根据按下的按键，控制舵机转动
								case PSB_PAD_LEFT:
									ServoSetPluseAndTime( 6, ServoPwmDutySet[6] + 20, 50 );
									BusServoPwmDutySet[6] = BusServoPwmDutySet[6] + 10;
									if (BusServoPwmDutySet[6] > 1000)
										BusServoPwmDutySet[6] = 1000;
									BusServoCtrl(6,SERVO_MOVE_TIME_WRITE,BusServoPwmDutySet[6],50);
									break;
								case PSB_PAD_RIGHT:
									ServoSetPluseAndTime( 6, ServoPwmDutySet[6] - 20, 50 );
									BusServoPwmDutySet[6] = BusServoPwmDutySet[6] - 10;
									if (BusServoPwmDutySet[6] < 0)
										BusServoPwmDutySet[6] = 0;
									BusServoCtrl(6,SERVO_MOVE_TIME_WRITE,BusServoPwmDutySet[6],50);
									break;
								case PSB_PAD_UP:
									ServoSetPluseAndTime( 5, ServoPwmDutySet[5] + 20, 50 );
									BusServoPwmDutySet[5] = BusServoPwmDutySet[5] - 10;
									if (BusServoPwmDutySet[5] < 0)
										BusServoPwmDutySet[5] = 0;
									BusServoCtrl(5,SERVO_MOVE_TIME_WRITE,BusServoPwmDutySet[5],50);
									break;
								case PSB_PAD_DOWN:
									ServoSetPluseAndTime( 5, ServoPwmDutySet[5] - 20, 50 );
									BusServoPwmDutySet[5] = BusServoPwmDutySet[5] + 10;
									if (BusServoPwmDutySet[5] > 1000)
										BusServoPwmDutySet[5] = 1000;
									BusServoCtrl(5,SERVO_MOVE_TIME_WRITE,BusServoPwmDutySet[5],50);
									break;
								case PSB_L1:
									ServoSetPluseAndTime( 2, ServoPwmDutySet[2] + 20, 50 );
									BusServoPwmDutySet[2] = BusServoPwmDutySet[2] + 10;
									if (BusServoPwmDutySet[2] > 1000)
										BusServoPwmDutySet[2] = 1000;
									BusServoCtrl(2,SERVO_MOVE_TIME_WRITE,BusServoPwmDutySet[2],50);
									break;
								case PSB_L2:
									ServoSetPluseAndTime( 1, ServoPwmDutySet[1] + 20, 50 );
									BusServoPwmDutySet[1] = BusServoPwmDutySet[1] + 10;
									if (BusServoPwmDutySet[1] > 1000)
										BusServoPwmDutySet[1] = 1000;
									BusServoCtrl(1,SERVO_MOVE_TIME_WRITE,BusServoPwmDutySet[1],50);
									break;
								case PSB_TRIANGLE:
									ServoSetPluseAndTime( 4, ServoPwmDutySet[4] - 20, 50 );
									BusServoPwmDutySet[4] = BusServoPwmDutySet[4] + 10;
									if (BusServoPwmDutySet[4] > 1000)
										BusServoPwmDutySet[4] = 1000;
									BusServoCtrl(4,SERVO_MOVE_TIME_WRITE,BusServoPwmDutySet[4],50);
									break;
								case PSB_CROSS:
									ServoSetPluseAndTime( 4, ServoPwmDutySet[4] + 20, 50 );
									BusServoPwmDutySet[4] = BusServoPwmDutySet[4] - 10;
									if (BusServoPwmDutySet[4] < 0)
										BusServoPwmDutySet[4] = 0;
									BusServoCtrl(4,SERVO_MOVE_TIME_WRITE,BusServoPwmDutySet[4],50);
									break;
								case PSB_R1:
									ServoSetPluseAndTime( 2, ServoPwmDutySet[2] - 20, 50 );
									BusServoPwmDutySet[2] = BusServoPwmDutySet[2] - 10;
									if (BusServoPwmDutySet[2] < 0)
										BusServoPwmDutySet[2] = 0;
									BusServoCtrl(2,SERVO_MOVE_TIME_WRITE,BusServoPwmDutySet[2],50);
									break;
								case PSB_R2:
									ServoSetPluseAndTime( 1, ServoPwmDutySet[1] - 20, 50 );
									BusServoPwmDutySet[1] = BusServoPwmDutySet[1] - 10;
									if (BusServoPwmDutySet[1] < 0)
										BusServoPwmDutySet[1] = 0;
									BusServoCtrl(1,SERVO_MOVE_TIME_WRITE,BusServoPwmDutySet[1],50);
									break;
								case PSB_CIRCLE:
									ServoSetPluseAndTime( 3, ServoPwmDutySet[3] + 20, 50 );
									BusServoPwmDutySet[3] = BusServoPwmDutySet[3] + 10;
									if (BusServoPwmDutySet[3] > 1000)
										BusServoPwmDutySet[3] = 1000;
									BusServoCtrl(3,SERVO_MOVE_TIME_WRITE,BusServoPwmDutySet[3],50);
									break;
								case PSB_SQUARE:
									ServoSetPluseAndTime( 3, ServoPwmDutySet[3] - 20, 50 );
									BusServoPwmDutySet[3] = BusServoPwmDutySet[3] - 10;
									if (BusServoPwmDutySet[3] < 0)
										BusServoPwmDutySet[3] = 0;
									BusServoCtrl(3,SERVO_MOVE_TIME_WRITE,BusServoPwmDutySet[3],50);
									break;
								case PSB_START:
									ServoSetPluseAndTime( 1, 1500, 1000 );
									ServoSetPluseAndTime( 2, 1500, 1000 );
									ServoSetPluseAndTime( 3, 1500, 1000 );
									ServoSetPluseAndTime( 4, 1500, 1000 );
									ServoSetPluseAndTime( 5, 1500, 1000 );
									ServoSetPluseAndTime( 6, 1500, 1000 );
									for (i = 1; i < 7; i++)
										BusServoCtrl(i,SERVO_MOVE_TIME_WRITE,500,1000);
									break;
								default:
									if (PS2_AnologData(PSS_LX) == 255)
									{
										ServoSetPluseAndTime( 3, ServoPwmDutySet[3] + 30, 60 );
										BusServoPwmDutySet[3] = BusServoPwmDutySet[3] + 10;
										if (BusServoPwmDutySet[3] > 1000)
											BusServoPwmDutySet[3] = 1000;
										BusServoCtrl(3,SERVO_MOVE_TIME_WRITE,BusServoPwmDutySet[3],50);
									}
									if (PS2_AnologData(PSS_LX) == 0)
									{
										ServoSetPluseAndTime( 3, ServoPwmDutySet[3] - 30, 60 );
										BusServoPwmDutySet[3] = BusServoPwmDutySet[3] - 10;
										if (BusServoPwmDutySet[3] < 0)
											BusServoPwmDutySet[3] = 0;
										BusServoCtrl(3,SERVO_MOVE_TIME_WRITE,BusServoPwmDutySet[3],50);
									}
									if (PS2_AnologData(PSS_RY) == 0)
									{
										ServoSetPluseAndTime( 4, ServoPwmDutySet[4] + 30, 60 );
										BusServoPwmDutySet[4] = BusServoPwmDutySet[4] + 10;
										if (BusServoPwmDutySet[4] > 1000)
											BusServoPwmDutySet[4] = 1000;
										BusServoCtrl(4,SERVO_MOVE_TIME_WRITE,BusServoPwmDutySet[4],50);
									}
									if (PS2_AnologData(PSS_RY) == 255)
									{
										ServoSetPluseAndTime( 4, ServoPwmDutySet[4] - 30, 60 );
										BusServoPwmDutySet[4] = BusServoPwmDutySet[4] - 10;
										if (BusServoPwmDutySet[4] < 0)
											BusServoPwmDutySet[4] = 0;
										BusServoCtrl(4,SERVO_MOVE_TIME_WRITE,BusServoPwmDutySet[4],50);
									}
									if (PS2_AnologData(PSS_LY) == 0)
									{
										ServoSetPluseAndTime( 5, ServoPwmDutySet[5] - 30, 60 );
										BusServoPwmDutySet[5] = BusServoPwmDutySet[5] - 10;
										if (BusServoPwmDutySet[5] < 0)
											BusServoPwmDutySet[5] = 0;
										BusServoCtrl(5,SERVO_MOVE_TIME_WRITE,BusServoPwmDutySet[5],50);
									}
									if (PS2_AnologData(PSS_LY) == 255)
									{
										ServoSetPluseAndTime( 5, ServoPwmDutySet[5] + 30, 60 );
										BusServoPwmDutySet[5] = BusServoPwmDutySet[5] + 10;
										if (BusServoPwmDutySet[5] > 1000)
											BusServoPwmDutySet[5] = 1000;
										BusServoCtrl(5,SERVO_MOVE_TIME_WRITE,BusServoPwmDutySet[5],50);	
									}
									if (PS2_AnologData(PSS_RX) == 0)
									{
										ServoSetPluseAndTime( 6, ServoPwmDutySet[6] + 30, 60 );
										BusServoPwmDutySet[6] = BusServoPwmDutySet[6] + 10;
										if (BusServoPwmDutySet[6] > 1000)
											BusServoPwmDutySet[6] = 1000;
										BusServoCtrl(6,SERVO_MOVE_TIME_WRITE,BusServoPwmDutySet[6],50);
									}
									if (PS2_AnologData(PSS_RX) == 255)
									{
										ServoSetPluseAndTime( 6, ServoPwmDutySet[6] - 30, 60 );
										BusServoPwmDutySet[6] = BusServoPwmDutySet[6] - 10;
										if (BusServoPwmDutySet[6] < 0)
											BusServoPwmDutySet[6] = 0;
										BusServoCtrl(6,SERVO_MOVE_TIME_WRITE,BusServoPwmDutySet[6],50);
									}
									break;
							}
				}
			}
			else
			{	
				 if( PS2_Button( PSB_SELECT ) && PS2_ButtonPressed( PSB_START ) )  //检查是不是 SELECT按钮被按住，然后按下START按钮， 是的话，切换模式
					{
						Mode = 0; //将模式变为0， 就动作组模式
						Ps2State = 1;  //清除标志。
						manual = TRUE;
						BuzzerState = 1;
						LED=~LED;
						DelayMs(80);
						manual = FALSE;
						DelayMs(50);
						manual = TRUE;
						BuzzerState = 1;
						DelayMs(80);
						manual = FALSE;
						LED=~LED;
					}
					else
					{
				if(PS2KeyValue && !Ps2State && !PS2_Button(PSB_SELECT))
				{
					LED=~LED;
				}

				switch(PS2KeyValue)
				{
					case 0:
						if(Ps2State)
						{
							Ps2State = FALSE;
						}
						break;
					
					case PSB_START:
						if(!Ps2State)
						{
							FullActRun(0,1);
						}
						Ps2State = TRUE;
						break;
					
					case PSB_PAD_UP:
						if(!Ps2State)
						{
							FullActRun(1,1);
						}
						Ps2State = TRUE;
						break;
					
					case PSB_PAD_DOWN:
						if(!Ps2State)
						{
							FullActRun(2,1);
						}
						Ps2State = TRUE;
						break;
					
					case PSB_PAD_LEFT:
						if(!Ps2State)
						{
						FullActRun(3,1);
					}
					Ps2State = TRUE;
					break;
					
				case PSB_PAD_RIGHT:
					if(!Ps2State)
					{
						FullActRun(4,1);
					}
					Ps2State = TRUE;
					break;

				case PSB_TRIANGLE:
					if(!Ps2State)
					{
						FullActRun(5,1);
					}
					Ps2State = TRUE;
					break;
					
				case PSB_CROSS:
					if(!Ps2State)
					{
						FullActRun(6,1);
					}
					Ps2State = TRUE;
					break;
					
	//			case PSB_SQUARE:
	//				if(!Ps2State)
	//				{
	//					FullActRun(7,1);
	//				}
	//				Ps2State = TRUE;
	//				break;
					
				case PSB_CIRCLE:
					if(!Ps2State)
					{
						FullActRun(8,1);
					}
					Ps2State = TRUE;
					break;

				case PSB_L1:
					if(!Ps2State)
					{
						FullActRun(9,1);
					}
					Ps2State = TRUE;
					break;
					
				case PSB_R1:
					if(!Ps2State)
					{
						FullActRun(10,1);
					}
					Ps2State = TRUE;
					break;
					
				case PSB_L2:
					if(!Ps2State)
					{
						FullActRun(11,1);
					}
					Ps2State = TRUE;
					break;
					
				case PSB_R2:
					if(!Ps2State)
					{
						FullActRun(12,1);
					}
					Ps2State = TRUE;
					break;
			}
		}
		}
	}
}
}
