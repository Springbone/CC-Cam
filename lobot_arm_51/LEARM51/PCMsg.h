#ifndef _PC_MSG_H_
#define _PC_MSG_H_




//指令
#define CMD_MULT_SERVO_MOVE					3	//多个舵机相同时间运动
#define CMD_MY_LEFT         4
#define CMD_MY_RIGHT        5
#define CMD_MY_UP         1
#define CMD_MY_DOWN        2
#define CMD_FULL_ACTION_RUN					6
#define CMD_FULL_ACTION_STOP				7
#define CMD_FULL_ACTION_ERASE				8
#define CMD_ACTION_DOWNLOAD					25



//存放起始地址
#define MEM_LOBOT_LOGO_BASE					0L	//"LOBOT"存放基地址，用于识别是否是新FLASH
#define MEM_FRAME_INDEX_SUM_BASE			4096L//每个动作组有多少动作，从这个地址开始存放，共计256个动作组
#define MEM_ACT_FULL_BASE					8192L//动作组文件从这个地址开始存放

//大小
#define ACT_SUB_FRAME_SIZE					64L		//一个动作帧占64字节空间
#define ACT_FULL_SIZE						16384L	//16KB,一套完整动作组占14kb字节







void InitUart1(void);

void TaskPCMsgHandle(void);
void InitMemory(void);

#endif

