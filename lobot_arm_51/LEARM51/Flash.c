#include "include.h"



/************************************************
SPI初始化
入口参数: 无
出口参数: 无
************************************************/
void InitSpi()
{
	ACC = P_SW1;                                //切换到第一组SPI
	ACC &= ~(SPI_S0 | SPI_S1);                  //SPI_S0=0 SPI_S1=0
	P_SW1 = ACC;                                //(P1.2/SS, P1.3/MOSI, P1.4/MISO, P1.5/SCLK)

	SPSTAT = SPIF | WCOL;                       //清除SPI状态
	SS = 1;
	SPCTL = SSIG | SPEN | MSTR;                 //设置SPI为主模式
}


void InitFlash()
{
	InitSpi();
}

/************************************************
使用SPI方式与Flash进行数据交换
入口参数:
    dat : 准备写入的数据
出口参数:
    从Flash中读出的数据
************************************************/
BYTE SpiShift(BYTE dat)
{
    SPDAT = dat;                                //触发SPI发送
    while (!(SPSTAT & SPIF));                   //等待SPI数据传输完成
    SPSTAT = SPIF | WCOL;                       //清除SPI状态
    
    return SPDAT;
}



/************************************************
检测Flash的忙状态
入口参数: 无
出口参数:
    0 : Flash处于空闲状态
    1 : Flash处于忙状态
************************************************/
BOOL IsFlashBusy()
{
    BYTE dat;
    
    SS = 0;
    SpiShift(SFC_RDSR);                         //发送读取状态命令
    dat = SpiShift(0);                          //读取状态
    SS = 1;
    
    return (dat & 0x01);                        //状态值的Bit0即为忙标志
}

/************************************************
使能Flash写命令
入口参数: 无
出口参数: 无
************************************************/
void FlashWriteEnable()
{
    while (IsFlashBusy());                      //Flash忙检测
    SS = 0;
    SpiShift(SFC_WREN);                         //发送写使能命令
    SS = 1;
}

/************************************************
擦除整片Flash
入口参数: 无
出口参数: 无
************************************************/
void FlashErase()
{
    FlashWriteEnable();                     //使能Flash写命令
    SS = 0;
    SpiShift(SFC_CHIPER);                   //发送片擦除命令
    SS = 1;
}

/************************************************
擦除扇区 扇区大小4096,Flash最小擦除大小是以扇区为单位擦除
入口参数: 
		addr
出口参数: 无
************************************************/
void FlashEraseSector(DWORD addr)
{
    FlashWriteEnable();                     //使能Flash写命令
    SS = 0;
    SpiShift(SFC_SECTOR_ERASE);                   //发送扇区擦除命令
	SpiShift((BYTE)(addr>>16));
	SpiShift((BYTE)(addr>>8));
	SpiShift((BYTE)addr);
    SS = 1;
}

/************************************************
从Flash中读取数据
入口参数:
    addr   : 地址参数
    size   : 数据块大小
    buffer : 缓冲从Flash中读取的数据
出口参数:
    无
************************************************/
void FlashRead(DWORD addr, DWORD size, BYTE *buffer)
{
    while (IsFlashBusy());                  //Flash忙检测
    SS = 0;
    SpiShift(SFC_FASTREAD);                 //使用快速读取命令
    SpiShift(((BYTE *)&addr)[1]);           //设置起始地址
    SpiShift(((BYTE *)&addr)[2]);
    SpiShift(((BYTE *)&addr)[3]);
    SpiShift(0);                            //需要空读一个字节
    while (size)
    {
        *buffer = SpiShift(0);              //自动连续读取并保存
        addr++;
        buffer++;
        size--;
    }
    SS = 1;
}

/************************************************
写数据到Flash中
入口参数:
    addr   : 地址参数
    size   : 数据块大小
    buffer : 缓冲需要写入Flash的数据
出口参数: 无
************************************************/
void FlashWrite(DWORD addr, DWORD size, BYTE *buffer)
{
    while (size)
    {
        FlashWriteEnable();                     //使能Flash写命令
        SS = 0;
        SpiShift(SFC_PAGEPROG);                 //发送页编程命令
        SpiShift(((BYTE *)&addr)[1]);           //设置起始地址
        SpiShift(((BYTE *)&addr)[2]);
        SpiShift(((BYTE *)&addr)[3]);
        while (size)
        {
            SpiShift(*buffer);                  //连续页内写
            addr++;
            buffer++;
            size--;
            if ((addr & 0xff) == 0) break;
        }
        SS = 1;
    }
}

