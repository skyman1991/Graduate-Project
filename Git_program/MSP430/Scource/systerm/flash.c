#include "common.h"
uint16 address_segment = PHY_ADDRESS_SEGMENT;
/****************************************************************************************

*NAME:       void FLASHInit(void)
*FUNCTION:   FLASH初始化
*Parameter:  无参数
*RETURN:     无返回值
*****************************************************************************************/
void FLASHInit(void)
{
    FCTL2=FWKEY+FSSEL_1+FN3+FN4;//时钟源为MCLK,25分频
}

/****************************************************************************************
*NAME:       void FLASH_Writew(unsigned int *Address,unsigned int nValue)
*FUNCTION:   将一个WORD类型的数据写入到指定的FLASH偶数起始地址
*Parameter:  Address，写入起始地址；nValue，写入值
*RETURN:     无返回值
*****************************************************************************************/
void FLASH_Writew(unsigned int *Address,unsigned int nValue)
{
    while((FCTL3&BUSY)==BUSY);    //等待FLASH存储器完成操作
    FCTL3=FWKEY;             // LOCK = 0
    FCTL1=FWKEY+WRT;             // WRT = 1
    
    *Address=nValue;
    
    FCTL1=FWKEY;        // WRT = 0
    while((FCTL3&BUSY)==BUSY);    //等待FLASH存储器完成操作
    FCTL3=FWKEY+LOCK;   // LOCK = 1
    
}

/****************************************************************************************
*NAME:       void FLASH_Writeb(unsigned int *Address,unsigned char nValue)
*FUNCTION:   将一个BYTE类型的数据写入到指定的FLASH地址
*Parameter:  Address，写入地址；nValue，写入值
*RETURN:     无返回值
*****************************************************************************************/
void FLASH_Writeb(unsigned int *Address,unsigned char nValue)
{
    FCTL1=FWKEY+WRT;             // WRT = 1
    FCTL3=FWKEY;             // LOCK = 0
    while((FCTL3&BUSY)==BUSY);    //等待FLASH存储器完成操作
    *Address=nValue;
    FCTL1=FWKEY;        // WRT = 0
    FCTL3=FWKEY+LOCK;   // LOCK = 1
    while((FCTL3&BUSY)==BUSY);    //等待FLASH存储器完成操作
}

/****************************************************************************************
*NAME:       void FLASH_Erase(unsigned int *Address)
*FUNCTION:   将FLASH里面的内容擦除掉
*Parameter:  Address，写入地址（段内任意）
*RETURN:     无返回值
*****************************************************************************************/
void FLASH_Erase(unsigned int *Address)
{
    
    while((FCTL3&BUSY)==BUSY);    //等待FLASH存储器完成操作
    FCTL3=FWKEY;                 // LOCK = 0
    FCTL1=FWKEY+ERASE;             //ERASE=1
    *Address=0;            //向段内地址任意写，启动擦除操作
    FCTL1=FWKEY;
    while((FCTL3&BUSY)==BUSY);    //等待FLASH存储器完成操作
    FCTL3=FWKEY+LOCK;
}

/****************************************************************************************
*NAME:       unsigned int FLASH_Readw(unsigned int *Address)
*FUNCTION:   读指定FLASH偶数地址开始的字内容
*Parameter:  Address，读出地址
*RETURN:     返回读出值
*****************************************************************************************/
unsigned int FLASH_Readw(unsigned int *Address)
{
    unsigned int Rdata;
    Rdata=*Address;
    return Rdata;
}

/****************************************************************************************
*NAME:       unsigned char FLASH_Readb(unsigned int *Address)
*FUNCTION:   读指定FLASH地址的字节内容
*Parameter:  Address，读出地址
*RETURN:     返回读出值
*****************************************************************************************/
unsigned char FLASH_Readb(unsigned int *Address)
{
    unsigned char Rdata;
    Rdata=*Address;
    return Rdata;
    
}



void WritePhyAddress()
{
#if (WRITE_PHY_ADDRESS)
    FLASH_Erase((uint16 *)PHY_ADDRESS_SEGMENT);
    FLASH_Writew((uint16 *)PHY_ADDRESS_SEGMENT,PHY_ADDRESS);
#endif
}
unsigned int GetPhyAddress()
{
    return FLASH_Readw((uint16 *)PHY_ADDRESS_SEGMENT);
}





