/* Includes ------------------------------------------------------------------*/
#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

#define LED1_ON() PDout(1)=0
#define LED2_ON() PDout(2)=0
#define LED3_ON() PDout(3)=0
#define LED4_ON() PDout(4)=0
#define LED1_OFF() PDout(1)=1
#define LED2_OFF() PDout(2)=1
#define LED3_OFF() PDout(3)=1
#define LED4_OFF() PDout(4)=1
#define LED1_REV() PDout(1)^=1
#define LED2_REV() PDout(2)^=1
#define LED3_REV() PDout(3)^=1
#define LED4_REV() PDout(4)^=1

void LED_Init(void);//≥ı ºªØ
	 				    
#endif
