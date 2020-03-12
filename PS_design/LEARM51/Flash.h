#ifndef _FLASH_H_
#define _FLASH_H_

sbit SS             =   P1^2;                   //SPI的SS脚,连接到Flash的CE



#define SPI_S0          0x04
#define SPI_S1          0x08



#define SPIF            0x80                    //SPSTAT.7
#define WCOL            0x40                    //SPSTAT.6

#define SSIG            0x80                    //SPCTL.7
#define SPEN            0x40                    //SPCTL.6
#define DORD            0x20                    //SPCTL.5
#define MSTR            0x10                    //SPCTL.4
#define CPOL            0x08                    //SPCTL.3
#define CPHA            0x04                    //SPCTL.2
#define SPDHH           0x00                    //CPU_CLK/4
#define SPDH            0x01                    //CPU_CLK/16
#define SPDL            0x02                    //CPU_CLK/64
#define SPDLL           0x03                    //CPU_CLK/128


#define SFC_WREN        		0x06                    //串行Flash命令集
#define SFC_WRDI        		0x04
#define SFC_RDSR        		0x05
#define SFC_WRSR        		0x01
#define SFC_READ        		0x03
#define SFC_FASTREAD    		0x0B
#define SFC_RDID        		0xAB
#define SFC_PAGEPROG    		0x02
#define SFC_RDCR        		0xA1
#define SFC_WRCR        		0xF1
#define SFC_SECTORER    		0xD7
#define SFC_BLOCKER     		0xD8
#define SFC_SECTOR_ERASE		0x20
#define SFC_CHIPER      		0xC7


#define BUFFER_SIZE     1024                    //缓冲区大小
#define TEST_ADDR       0                       //Flash测试地址



void InitFlash();
void InitSpi();
BYTE SpiShift(BYTE dat);
BOOL IsFlashBusy();
void FlashWriteEnable();
void FlashEraseSector(DWORD addr);
void FlashErase();
void FlashRead(DWORD addr, DWORD size, BYTE *buffer);
void FlashWrite(DWORD addr, DWORD size, BYTE *buffer);

#endif

