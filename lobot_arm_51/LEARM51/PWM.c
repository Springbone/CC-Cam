#include "include.h"


			
uint16 xdata ServoPwmDuty[8] = {1500,1500,1500,1050,1000,1700,1500,1500};	//PWM������
uint16 ServoPwmDutySet[8] = {1500,1500,1500,1050,1000,1700,1500,1500};	//PWM������
float xdata ServoPwmDutyInc[8];		//Ϊ���ٶȿ��ƣ���PWM�������仯ʱ��ÿ2.5ms��20ms������PWM����

bool ServoPwmDutyHaveChange = FALSE;	//�����б仯��־λ

uint16 ServoTime = 2000;			//����ӵ�ǰ�Ƕ��˶���ָ���Ƕȵ�ʱ�䣬Ҳ���ǿ����ٶ�


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

void ServoPwmDutyCompare(void)//����仯�Ƚϼ��ٶȿ���
{
	uint8 i;
	
	static uint16 ServoPwmDutyIncTimes;	//��Ҫ�����Ĵ���
	static bool ServoRunning = FALSE;	//���������ָ���ٶ��˶���ָ���������Ӧ��λ��
	if(ServoPwmDutyHaveChange)//ֹͣ�˶������������仯ʱ�Ž��м���      ServoRunning == FALSE && 
	{
		ServoPwmDutyHaveChange = FALSE;
		ServoPwmDutyIncTimes = ServoTime/20;	//��ÿ20ms����һ��ServoPwmDutyCompare()����ʱ�ô˾�
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
				ServoPwmDutyInc[i] /= ServoPwmDutyIncTimes;//ÿ�ε���������
			}
		}
		ServoRunning = TRUE;	//�����ʼ����
	}
	if(ServoRunning)
	{
		ServoPwmDutyIncTimes--;
		for(i=0;i<8;i++)
		{
			if(ServoPwmDutyIncTimes == 0)
			{		//���һ�ε�����ֱ�ӽ��趨ֵ������ǰֵ

				ServoPwmDuty[i] = ServoPwmDutySet[i];

				ServoRunning = FALSE;	//�����趨λ�ã����ֹͣ�˶�
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
// 	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
// 	AUXR |= 0x00;		//T0,T1������12T
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0x00;			//���ö�ʱ��ֵ
	TH0 = 0x00;			//���ö�ʱ��ֵ
	TF0 = 0;			//���TF0��־
	TR0 = 1;			//��ʱ��0��ʼ��ʱ
	ET0 = 1;			//����ʱ��0�ж�

	PT0 = 1;
}


void InitPWM(void)
{
	InitTimer0();
	P2M0 |= 0x10;	//�����������
	P3M0 |= 0x7C;
	P5M0 |= 0x30;
}

void Timer0Value(uint16 pwm)
{
	uint16 value;
	value=0xffff-pwm;
	TR0 = 0;			//
	TL0=value;			//16λ���ݸ�8λ���ݸ�ֵĬ�Ͻ�16λ���ݵĵͰ�λֱ�Ӹ�����λ����
    TH0=value>>8;		//��16λ��������8λ��Ҳ���ǽ���8λ�Ƶ��Ͱ�λ���ٸ�ֵ��8λ����
    TR0 = 1;			//��ʱ��0��ʼ��ʱ
}





void Timer0_isr(void) interrupt 1// using 1
{
	static uint16 i = 1;	//��̬������ÿ�ε��ú���ʱ������һ��������ֵ��
							//��ȫ�ֱ������ƣ���ͬ����ֻ�����ڴ˺����ڲ�
	switch(i)
	{
		case 1:
//			SERVO0 = 1;	//PWM���ƽŸߵ�ƽ
			//����ʱ��0��ֵ������Pwm0Duty�����������жϣ��´��жϻ������һ��case���
			Timer0Value(ServoPwmDuty[0]);	
			break;
		case 2:
//			SERVO0 = 0;	//PWM���ƽŵ͵�ƽ
			//�˼�������ֵ�������жϱ�ʾ��һ����ԪҪ��������Ŀ�ʼ
			Timer0Value(2500-ServoPwmDuty[0]);	
			break;
		case 3:
			SERVO1 = 1;	
			Timer0Value(ServoPwmDuty[1]);	
			break;
		case 4:
			SERVO1 = 0;	//PWM���ƽŵ͵�ƽ
			Timer0Value(2500-ServoPwmDuty[1]);	
			break;
		case 5:
			SERVO2 = 1;	
			Timer0Value(ServoPwmDuty[2]);	
			break;
		case 6:
			SERVO2 = 0;	//PWM���ƽŵ͵�ƽ
			Timer0Value(2500-ServoPwmDuty[2]);	
			break;	
		case 7:
			SERVO3 = 1;	
			Timer0Value(ServoPwmDuty[3]);	
			break;
		case 8:
			SERVO3 = 0;	//PWM���ƽŵ͵�ƽ
			Timer0Value(2500-ServoPwmDuty[3]);	
			break;	
		case 9:
			SERVO4 = 1;	
			Timer0Value(ServoPwmDuty[4]);	
			break;
		case 10:
			SERVO4 = 0;	//PWM���ƽŵ͵�ƽ
			Timer0Value(2500-ServoPwmDuty[4]);	
			break;	
		case 11:
			SERVO5 = 1;	
			Timer0Value(ServoPwmDuty[5]);	
			break;
		case 12:
			SERVO5 = 0;	//PWM���ƽŵ͵�ƽ
			Timer0Value(2500-ServoPwmDuty[5]);	
			break;
		case 13:
 			SERVO6 = 1;	
			Timer0Value(ServoPwmDuty[6]);	
			break;
		case 14:
 			SERVO6 = 0;	//PWM���ƽŵ͵�ƽ
			Timer0Value(2500-ServoPwmDuty[6]);	
			break;
		case 15:
// 			SERVO7 = 1;	
			Timer0Value(ServoPwmDuty[7]);	
			break;
		case 16:
// 			SERVO7 = 0;	//PWM���ƽŵ͵�ƽ
			Timer0Value(2500-ServoPwmDuty[7]);
			i = 0;	
			break;				 
	}
	i++;
}

