/*******************************************************************************
** 延时函数，头文件
** 2014/08/25  yxk
** 
*******************************************************************************/
#ifndef DELAY_H
#define DELAY_H

#include "intrinsics.h"

#define CPU_F ((double)16000000)   
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))  
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))  
#define delay_s(x) __delay_cycles((long)(CPU_F*(double)x/1.0)) 


#ifdef __cplusplus
extern "C" {
#endif
//----------------------------------------------------------------------------------
// Function declarations
//----------------------------------------------------------------------------------
void delay_1us();
void delay_10us();
void delay_50us();
void delay_100us();
void delay_600us();
void delay_1ms();
void delay_10ms();
void delay_100ms();
void delay_1s();
//void delay_10s();


#ifdef __cplusplus
}
#endif
extern void delayus(uint16 time);
extern void delayms(uint16 time);
extern void delays(uint16 time);
/**********************************************************************************/
#endif