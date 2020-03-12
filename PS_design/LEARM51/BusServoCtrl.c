#include "include.h"

static bool UartBusy = FALSE;

void InitUart4(void)
{
	S4CON = 0x10;		//8位数据,可变波特率
	S4CON |= 0x40;		//串口4选择定时器4为波特率发生器
	T4T3M |= 0x20;		//定时器4时钟为Fosc,即1T
	T4L = (65536 - (FOSC/4/UART4_BAUD));   //设置波特率重装值
    T4H = (65536 - (FOSC/4/UART4_BAUD))>>8;
	T4T3M |= 0x80;		//启动定时器4
	IE2 |= 0x10;                 //使能串口4中断
}


void InitBusServoCtrl(void)
{
	InitUart4();//串口2初始化
	UART_TX_ENABLE();
}

/***********************************************************
* 名    称： bool Uart4SendData(UINT8 dat)
* 功    能： 
* 入口参数：  
* 出口参数：
* 说    明： 					 
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
* 名    称： void Uart4() interrupt 18 using 1
* 功    能： 
* 入口参数：  
* 出口参数：
* 说    明： 					 
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
