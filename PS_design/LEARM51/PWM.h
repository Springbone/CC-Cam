#ifndef _PWM_H_
#define _PWM_H_

sbit SERVO1=P2^4;			//控制爪子的开合
sbit SERVO2=P5^4;			//上下爪子的舵机
sbit SERVO3=P5^5;
sbit SERVO4=P3^2;		
sbit SERVO5=P3^6;		
sbit SERVO6=P3^5;			
sbit SERVO7=P3^4;		
sbit SERVO8=P3^3;	


extern uint16 ServoPwmDutySet[];

extern bool ServoPwmDutyHaveChange;

void ServoSetPluseAndTime(uint8 id,uint16 p,uint16 time);
void ServoSetPluseAndTime_my(uint8 id,uint8 dir,uint8 mul);
void ServoPwmDutyCompare(void);//脉宽变化比较及速度控制
void InitPWM(void);

#endif

