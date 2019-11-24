#include "include.h"


static bool Uart2Busy = FALSE;

static bool fUartRxComplete = FALSE;
static uint8 xdata UartRxBuffer[260];

static bool UartBusy = FALSE;



void InitUart2(void)
{
	S2CON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x04;		//��ʱ��2ʱ��ΪFosc,��1T
	T2L = 0xC7;		//�趨��ʱ��ֵ	//9600bps@12.000MHz
	T2H = 0xFE;		//�趨��ʱ��ֵ
	AUXR |= 0x10;		//������ʱ��2
	IE2 |= 0x01;                 //ʹ�ܴ���2�ж�
}



/***********************************************************
* ��    �ƣ� bool Uart2SendData(UINT8 dat)
* ��    �ܣ� 
* ��ڲ�����  
* ���ڲ�����
* ˵    ���� 					 
/**********************************************************/ 
void Uart2SendData(UINT8 dat)
{
    S2BUF = dat;             			//Send data to UART buffer
	Uart2Busy = TRUE;
	while (Uart2Busy);
}

void Uart2SendDataPacket(UINT8 dat[],uint8 len)
{
	uint8 i;
	for(i = 0;i < len;i++)
	{
		Uart2SendData(dat[i]);
	}
}





/***********************************************************
* ��    �ƣ� void Uart4() interrupt 18 using 1
* ��    �ܣ� 
* ��ڲ�����  
* ���ڲ�����
* ˵    ���� 					 
/**********************************************************/ 
void Uart2() interrupt 8 using 1
{
	uint8 rxBuf;

	static uint8 startCodeSum = 0;
	static bool fFrameStart = FALSE;
	static uint8 messageLength = 0;
	static uint8 messageLengthSum = 2;
	
	if (S2CON & S2RI)		//����2�յ����������ж�
    {
        S2CON &= ~S2RI;     //Clear receive interrupt flag
		rxBuf = S2BUF; 		//��ֵ����2����
		
		if(!fFrameStart)
		{
			if(rxBuf == 0x55)
			{

				startCodeSum++;
				if(startCodeSum == 2)
				{
					startCodeSum = 0;
					fFrameStart = TRUE;
					messageLength = 1;
				}
			}
			else
			{

				fFrameStart = FALSE;
				messageLength = 0;
	
				startCodeSum = 0;
			}
			
		}
		if(fFrameStart)
		{
			UartRxBuffer[messageLength] = rxBuf;
			if(messageLength == 2)
			{
				messageLengthSum = UartRxBuffer[messageLength];
				if(messageLengthSum < 2)// || messageLengthSum > 30
				{
					messageLengthSum = 2;
					fFrameStart = FALSE;
					
				}
					
			}
			messageLength++;
	
			if(messageLength == messageLengthSum + 2) 
			{

				fUartRxComplete = TRUE;

				fFrameStart = FALSE;
			}
		}
    }
    if (S2CON & S2TI)
    {
        S2CON &= ~S2TI;     //Clear transmit interrupt flag
        Uart2Busy = FALSE;           //Clear transmit busy flag
    }
}


static bool UartRxOK(void)
{
	if(fUartRxComplete)
	{
		fUartRxComplete = FALSE;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
void TaskBLEMsgHandle(void)
{

	uint16 i;
	uint8 cmd;
	uint8 id;
	uint8 servoCount;
	uint16 time;
	uint16 pos;
	uint16 times;
	uint8 fullActNum;
	if(UartRxOK())
	{
		LED = !LED;
		cmd = UartRxBuffer[3];
 		switch(cmd)
 		{
 			case CMD_MULT_SERVO_MOVE:
				servoCount = UartRxBuffer[4];
				time = UartRxBuffer[5] + (UartRxBuffer[6]<<8);
				for(i = 0; i < servoCount; i++)
				{
					id =  UartRxBuffer[7 + i * 3];
					pos = UartRxBuffer[8 + i * 3] + (UartRxBuffer[9 + i * 3]<<8);
	
					ServoSetPluseAndTime(id,pos,time);
					BusServoCtrl(id,SERVO_MOVE_TIME_WRITE,pos,time);
				}
 				break;
			
			case CMD_FULL_ACTION_RUN:
				fullActNum = UartRxBuffer[4];//��������
				times = UartRxBuffer[5] + (UartRxBuffer[6]<<8);//���д���
				FullActRun(fullActNum,times);
				break;
				
			case CMD_FULL_ACTION_STOP:
				FullActStop();
				break;
				

 		}
	}
}



