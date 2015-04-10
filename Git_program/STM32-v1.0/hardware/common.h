#ifndef __COMMON_H
#define __COMMON_H

#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"	 
#include "spi.h"
#include "A7129.h"
#include "sys.h" 
#include "delay.h"
#include "stm32f10x.h"
#include "core_cm3.h"
#include "timer.h"
#include "A7139_CONFIG.h"
#include "stm32f10x_exti.h"
#include "../trsdata/trsdata.h"


#define __enable_irq                              __enable_interrupt        /*!< global Interrupt enable */
#define __disable_irq                             __disable_interrupt       /*!< global Interrupt disable */
#define __enable_interrupt                        { __ASM ("cpsie I"); }
#define __disable_interrupt                       { __ASM ("cpsid I"); }


#endif
