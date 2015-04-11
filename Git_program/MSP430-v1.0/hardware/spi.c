/* Includes ------------------------------------------------------------------*/

#include "spi.h"
#include "common.h"

const digioConfig mosi_in   = {3, 1, BIT1, HAL_DIGIO_INPUT, 0};
const digioConfig mosi_out  = {3, 1, BIT1, HAL_DIGIO_OUTPUT, 0};
const digioConfig gio2      = {1, 5, BIT5, HAL_DIGIO_INPUT, 0};
const digioConfig sck       = {3, 3, BIT3, HAL_DIGIO_OUTPUT, 0};
const digioConfig scs       = {3, 2, BIT2, HAL_DIGIO_OUTPUT, 0};

void MOSI_IN(void)
{
    P3DIR &= ~BIT1;  
    
}
void MOSI_OUT(void)
{
    P3DIR |= BIT1; //1Êä³ö
}

void SPI3_Init(void)
{
    halDigioConfig(&mosi_in);
    halDigioConfig(&mosi_out);
    halDigioConfig(&sck);
    halDigioConfig(&scs);
    
    SCS_SET; 
    SCK_CLEAR;
    
}

void SPIx_WriteByte(uint8 dat)
{
    uint8 i;
    for(i=0; i<8; i++)
    {
        if(dat & 0x80)
            MOSI_SET;
        else
            MOSI_CLEAR;
        delay_1us();
        SCK_SET;
        delay_1us();
        SCK_CLEAR;
        dat=dat<<1;
        delay_1us();
    }
}
void SPIx_WriteWord(uint16 wrd)
{
    uint8 i;
    MOSI_CLEAR;
    for(i=0; i<16; i++)
    {
        if(wrd & 0x8000)
            MOSI_SET;
        else
            MOSI_CLEAR;
        delay_1us();
        SCK_SET;
        delay_1us();
        SCK_CLEAR;
        wrd=wrd<<1;
        delay_1us();
    }
}
uint16 SPIx_ReadWord(void)
{
    uint8  i;
    uint16 tmp=0;
    MOSI_CLEAR;
    MOSI_IN();	
    for(i=0; i<16; i++)
    {
        if(MOSI_DATA)
            tmp = 0x01|(tmp << 1);
        else
            tmp = tmp << 1;
        delay_1us();
        SCK_SET;
        delay_1us();
        SCK_CLEAR;
        //tmp = tmp << 1;
        delay_1us();
    }
    MOSI_OUT();
    return tmp;
}
uint8 SPIx_ReadByte(void)
{
    uint8 i,tmp=0;
    MOSI_IN();
    for(i=0; i<8; i++)
    {
        if(MOSI_DATA)
            tmp = 0x01|(tmp << 1);
        else
            tmp = tmp << 1;
        delay_1us();
        SCK_SET;
        delay_1us();
        SCK_CLEAR;
        //tmp = tmp << 1;
        delay_1us();
    }
    MOSI_OUT();
    return tmp;
}

