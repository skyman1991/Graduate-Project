/*******************************************************************************
** ÑÓÊ±º¯Êý
** 2014/08/05  yxk
** 
*******************************************************************************/

#include "common.h"


// real time 0.95us
void delayus(uint16 time)
{
    int i=0;
    for(i=0;i<time;i++)
        delay_us(1);
}
void delayms(uint16 time)
{
    int i=0;
    for(i=0;i<time;i++)
        delay_ms(1);
}
void delays(uint16 time)
{
    int i=0;
    for(i=0;i<time;i++)
        delay_s(1);
}
void inline delay_1us()
 {
     asm("NOP");
     asm("NOP");
     asm("NOP");
     asm("NOP");
     asm("NOP");
     asm("NOP");
     asm("NOP");	
 }
 
 //real time 10.03us
 void inline delay_10us()
 {
     delay_1us();
     delay_1us();
     delay_1us();
     delay_1us();
     delay_1us();
     delay_1us();
     delay_1us();
     delay_1us();
     delay_1us();
     delay_1us();
     asm("NOP");
     asm("NOP");
     asm("NOP");
     asm("NOP");		
 }
 

 void inline delay_50us()
 {
     delay_10us();
     delay_10us();
     delay_10us();
     delay_10us();
     delay_10us();
 }
 
 //real time 100.3us
 void inline delay_100us()
 {
     delay_10us();
     delay_10us();
     delay_10us();
     delay_10us();
     delay_10us();
     delay_10us();
     delay_10us();
     delay_10us();
     delay_10us();
     delay_10us();
 }

 void inline delay_600us()
 {
     delay_100us();
     delay_100us();
     delay_100us();
     delay_100us();
     delay_100us();
     delay_100us();
 }

// real time 1.002us
void inline delay_1ms()
 {
     delay_100us();
     delay_100us();
     delay_100us();
     delay_100us();
     delay_100us();
     delay_100us();
     delay_100us();
     delay_100us();
     delay_100us();
     delay_100us();
 }
  
void inline delay_10ms()
{
    delay_1ms();
    delay_1ms();
    delay_1ms();
    delay_1ms();
    delay_1ms();
    delay_1ms();
    delay_1ms();
    delay_1ms();
    delay_1ms();
    delay_1ms();
}
void inline delay_100ms()
{
    delay_10ms();
    delay_10ms();
    delay_10ms();
    delay_10ms();
    delay_10ms();
    delay_10ms();
    delay_10ms();
    delay_10ms();
    delay_10ms();
    delay_10ms();
}

void inline delay_1s(void)
{
    delay_100ms();
    delay_100ms();
    delay_100ms();
    delay_100ms();
    delay_100ms();
    delay_100ms();
    delay_100ms();
    delay_100ms();
    delay_100ms();
    delay_100ms();
}

void inline delay_10s(void)
{
    delay_1s();
    delay_1s();
    delay_1s();
    delay_1s();
    delay_1s();
    delay_1s();
    delay_1s();
    delay_1s();
    delay_1s();
    delay_1s();
}