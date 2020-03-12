#include "include.h"

static bool UartBusy = FALSE;

void InitUart4(void)
{
	S4CON = 0x10;		//8λ����,�ɱ䲨����
	S4CON |= 0x40;		//����4ѡ��ʱ��4Ϊ�����ʷ�����
	T4T3M |= 0x20;		//��ʱ��4ʱ��ΪFosc,��1T
	T4L = (65536 - (FOSC/4/UART4_BAUD));   //���ò�������װֵ
    T4H = (65536 - (FOSC/4/UART4_BAUD))>>8;
	T4T3M |= 0x80;		//������ʱ��4
	IE2 |= 0x10;                 //ʹ�ܴ���4�ж�
}


void InitBusServoCtrl(void)
{
	InitUart4();//����2��ʼ��
	UART_TX_ENABLE();
}

/***********************************************************
* ��    �ƣ� bool Uart4SendData(UINT8 dat)
* ��    �ܣ� 
* ��ڲ�����  
* ���ڲ�����
* ˵    ���� 					 
/**********************************************************/ 
void Uart4SendData(UINT8 dat)
{
    S4BUF = dat;             			//Send data to UART buffer
	UartBusy = TRUE;
	while (UartBusy);
}

void Uart4SendDataPacket(UINT8 dat[],uint8 len)
{
	uint8 i;
	for(i = 0;i < len;i++)
	{
		Uart4SendData(dat[i]);
	}
}
/***********************************************************
* ��    �ƣ� void Uart4() interrupt 18 using 1
* ��    �ܣ� 
* ��ڲ�����  
* ���ڲ�����
* ˵    ���� 					 
/**********************************************************/ 
void Uart4() interrupt 18 using 1
{
	uint8 rxBuf;
	
    if (S4CON & S4RI)
    {
        S4CON &= ~S4RI;     //Clear receive interrupt flag
		rxBuf = S4BUF; 

    }
    if (S4CON & S4TI)
    {
        S4CON &= ~S4TI;     //Clear transmit interrupt flag
        UartBusy = FALSE;           //Clear transmit busy flag
    }
}
void BusServoCtrl(uint8 id,uint8 cmd,uint16 prm1,uint16 prm2)
{
	uint32 i;
	uint8 tx[20];
	uint8 datalLen = 4;
	uint32 checkSum = 0;

	switch(cmd)
	{
	case SERVO_MOVE_TIME_WRITE:
		datalLen = SERVO_MOVE_TIME_DATA_LEN;
		break;
		
	
	}
	tx[0] = 0x55;
	tx[1] = 0x55;
	tx[2] = id;
	tx[3] = datalLen;
	tx[4] = cmd;
	tx[5] = prm1;
	tx[6] = prm1 >> 8;
	tx[7] = prm2;
	tx[8] = prm2 >> 8;
	for(i = 2; i <= datalLen + 1; i++)
	{
		checkSum += tx[i];
	}
	tx[datalLen + 2] = ~checkSum;
	UART_TX_ENABLE();
	Uart4SendDataPacket(tx,datalLen + 3);
}
