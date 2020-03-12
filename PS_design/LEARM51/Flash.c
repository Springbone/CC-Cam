#include "include.h"



/************************************************
SPI��ʼ��
��ڲ���: ��
���ڲ���: ��
************************************************/
void InitSpi()
{
	ACC = P_SW1;                                //�л�����һ��SPI
	ACC &= ~(SPI_S0 | SPI_S1);                  //SPI_S0=0 SPI_S1=0
	P_SW1 = ACC;                                //(P1.2/SS, P1.3/MOSI, P1.4/MISO, P1.5/SCLK)

	SPSTAT = SPIF | WCOL;                       //���SPI״̬
	SS = 1;
	SPCTL = SSIG | SPEN | MSTR;                 //����SPIΪ��ģʽ
}


void InitFlash()
{
	InitSpi();
}

/************************************************
ʹ��SPI��ʽ��Flash�������ݽ���
��ڲ���:
    dat : ׼��д�������
���ڲ���:
    ��Flash�ж���������
************************************************/
BYTE SpiShift(BYTE dat)
{
    SPDAT = dat;                                //����SPI����
    while (!(SPSTAT & SPIF));                   //�ȴ�SPI���ݴ������
    SPSTAT = SPIF | WCOL;                       //���SPI״̬
    
    return SPDAT;
}



/************************************************
���Flash��æ״̬
��ڲ���: ��
���ڲ���:
    0 : Flash���ڿ���״̬
    1 : Flash����æ״̬
************************************************/
BOOL IsFlashBusy()
{
    BYTE dat;
    
    SS = 0;
    SpiShift(SFC_RDSR);                         //���Ͷ�ȡ״̬����
    dat = SpiShift(0);                          //��ȡ״̬
    SS = 1;
    
    return (dat & 0x01);                        //״ֵ̬��Bit0��Ϊæ��־
}

/************************************************
ʹ��Flashд����
��ڲ���: ��
���ڲ���: ��
************************************************/
void FlashWriteEnable()
{
    while (IsFlashBusy());                      //Flashæ���
    SS = 0;
    SpiShift(SFC_WREN);                         //����дʹ������
    SS = 1;
}

/************************************************
������ƬFlash
��ڲ���: ��
���ڲ���: ��
************************************************/
void FlashErase()
{
    FlashWriteEnable();                     //ʹ��Flashд����
    SS = 0;
    SpiShift(SFC_CHIPER);                   //����Ƭ��������
    SS = 1;
}

/************************************************
�������� ������С4096,Flash��С������С��������Ϊ��λ����
��ڲ���: 
		addr
���ڲ���: ��
************************************************/
void FlashEraseSector(DWORD addr)
{
    FlashWriteEnable();                     //ʹ��Flashд����
    SS = 0;
    SpiShift(SFC_SECTOR_ERASE);                   //����������������
	SpiShift((BYTE)(addr>>16));
	SpiShift((BYTE)(addr>>8));
	SpiShift((BYTE)addr);
    SS = 1;
}

/************************************************
��Flash�ж�ȡ����
��ڲ���:
    addr   : ��ַ����
    size   : ���ݿ��С
    buffer : �����Flash�ж�ȡ������
���ڲ���:
    ��
************************************************/
void FlashRead(DWORD addr, DWORD size, BYTE *buffer)
{
    while (IsFlashBusy());                  //Flashæ���
    SS = 0;
    SpiShift(SFC_FASTREAD);                 //ʹ�ÿ��ٶ�ȡ����
    SpiShift(((BYTE *)&addr)[1]);           //������ʼ��ַ
    SpiShift(((BYTE *)&addr)[2]);
    SpiShift(((BYTE *)&addr)[3]);
    SpiShift(0);                            //��Ҫ�ն�һ���ֽ�
    while (size)
    {
        *buffer = SpiShift(0);              //�Զ�������ȡ������
        addr++;
        buffer++;
        size--;
    }
    SS = 1;
}

/************************************************
д���ݵ�Flash��
��ڲ���:
    addr   : ��ַ����
    size   : ���ݿ��С
    buffer : ������Ҫд��Flash������
���ڲ���: ��
************************************************/
void FlashWrite(DWORD addr, DWORD size, BYTE *buffer)
{
    while (size)
    {
        FlashWriteEnable();                     //ʹ��Flashд����
        SS = 0;
        SpiShift(SFC_PAGEPROG);                 //����ҳ�������
        SpiShift(((BYTE *)&addr)[1]);           //������ʼ��ַ
        SpiShift(((BYTE *)&addr)[2]);
        SpiShift(((BYTE *)&addr)[3]);
        while (size)
        {
            SpiShift(*buffer);                  //����ҳ��д
            addr++;
            buffer++;
            size--;
            if ((addr & 0xff) == 0) break;
        }
        SS = 1;
    }
}

