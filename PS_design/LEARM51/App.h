#ifndef _APP_H_
#define _APP_H_


#define FOSC 12000000L//22118400L      //System frequency

#define LED 		P25
#define BUZZER 		P37
#define KEY 		P17

#define LED_ON		0
#define LED_OFF		1


extern u32 gSystemTickCount;	//系统从启动到现在的毫秒数


void DelayMs(uint16 ms);

void InitADC(void);
void InitTimer3(void);
void InitUart2(void);
void Uart1SendData(BYTE dat);
uint16 GetBatteryVoltage(void);


void TaskRun(u8 ps2_ok);

#endif
