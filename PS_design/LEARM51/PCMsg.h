#ifndef _PC_MSG_H_
#define _PC_MSG_H_




//ָ��
#define CMD_MULT_SERVO_MOVE					3	//��������ͬʱ���˶�
#define CMD_MY_LEFT         4
#define CMD_MY_RIGHT        5
#define CMD_MY_UP         1
#define CMD_MY_DOWN        2
#define CMD_FULL_ACTION_RUN					6
#define CMD_FULL_ACTION_STOP				7
#define CMD_FULL_ACTION_ERASE				8
#define CMD_ACTION_DOWNLOAD					25



//�����ʼ��ַ
#define MEM_LOBOT_LOGO_BASE					0L	//"LOBOT"��Ż���ַ������ʶ���Ƿ�����FLASH
#define MEM_FRAME_INDEX_SUM_BASE			4096L//ÿ���������ж��ٶ������������ַ��ʼ��ţ�����256��������
#define MEM_ACT_FULL_BASE					8192L//�������ļ��������ַ��ʼ���

//��С
#define ACT_SUB_FRAME_SIZE					64L		//һ������֡ռ64�ֽڿռ�
#define ACT_FULL_SIZE						16384L	//16KB,һ������������ռ14kb�ֽ�







void InitUart1(void);

void TaskPCMsgHandle(void);
void InitMemory(void);

#endif

