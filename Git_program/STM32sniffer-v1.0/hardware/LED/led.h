/* Includes ------------------------------------------------------------------*/
#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

#define LED0_ON() PDout(0)=0
#define LED1_ON() PDout(1)=0
#define LED2_ON() PDout(2)=0
#define LED3_ON() PDout(3)=0
#define LED4_ON() PDout(4)=0
#define LED5_ON() PDout(5)=0
#define LED6_ON() PDout(6)=0
#define LED0_OFF() PDout(0)=1
#define LED1_OFF() PDout(1)=1
#define LED2_OFF() PDout(2)=1
#define LED3_OFF() PDout(3)=1
#define LED4_OFF() PDout(4)=1
#define LED5_OFF() PDout(5)=1
#define LED6_OFF() PDout(6)=1
#define LED0_REV() PDout(0)^=1
#define LED1_REV() PDout(1)^=1
#define LED2_REV() PDout(2)^=1
#define LED3_REV() PDout(3)^=1
#define LED4_REV() PDout(4)^=1
#define LED5_REV() PDout(5)^=1
#define LED6_REV() PDout(6)^=1
void LED_Init(void);//≥ı ºªØ
	 				    
#endif
