#include "include.h"

//����:�������ֻ������Ƽ����޹�˾
//���ǵĵ���:lobot-zone.taobao.com
//ϵͳ���еľ���Ƶ��Ϊ12M
void main(void)
{
	uint8 ps_ok = 1;
	P0M1=P0M0=P1M1=P1M0=P2M1=P2M0=P3M1=P3M0=P4M1=P4M0=P5M1=P5M0=P6M1=P6M0=P7M1=P7M0= 0;	
	//ȫ�����ó�׼˫���
	
	InitPWM();		//�����г�ʼ��Timer0����ʼ�������PWM��

	InitTimer3();	//��ʼ��Timer3,���ڲ���100us�Ķ�ʱ�ж�
	InitUart1();	//������ ��Timer1������������PC�˽���ͨ��
  InitUart2();
	InitADC();
	InitBusServoCtrl();
	
	P3M0 |= 0x80;	//���������������������
	EA = 1;			//�����ж�
	LED = LED_ON;
	ps_ok = InitPS2();//PS2��Ϸ�ֱ���������ʼ��
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

