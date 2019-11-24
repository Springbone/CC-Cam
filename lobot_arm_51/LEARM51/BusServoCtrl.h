#ifndef _BUS_SERVO_CTRL_H_
#define _BUS_SERVO_CTRL_H_



#define UART4_BAUD	115200

#define S4RI  0x01              //S4CON.0
#define S4TI  0x02              //S4CON.1
#define S4RB8 0x04              //S4CON.2
#define S4TB8 0x08              //S4CON.3



#define UART_RX_ENABLE()		P33 = 1;P34 = 0
#define UART_TX_ENABLE()		P33 = 0;P34 = 1


#define BROADCAST_ID 0xFE


#define SERVO_MOVE_TIME_WRITE 1 //通过时间控制舵机打到指定角度


#define SERVO_MOVE_TIME_DATA_LEN 7

void InitUart4(void);
void InitBusServoCtrl(void);

void BusServoCtrl(uint8 id,uint8 cmd,uint16 prm1,uint16 prm2);

#endif
