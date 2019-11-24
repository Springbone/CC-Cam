#ifndef _BLUETOOTH_H_
#define _BLUETOOTH_H_


// #define UART2_BAUD	115200L	//HC11
#define S2RI  0x01          //S2CON.0
#define S2TI  0x02          //S2CON.1
#define S2RB8 0x04          //S2CON.2
#define S2TB8 0x08          //S2CON.3


void InitUart2(void);
void TaskBLEMsgHandle(void);

#endif

