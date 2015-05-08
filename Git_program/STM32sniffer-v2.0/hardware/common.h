#ifndef __COMMON_H
#define __COMMON_H


#define    SINK_NUM     1
#define    BROADCAST    0xFF

#define    ACK_EN     1
#define    ACK_DIS    0

#define    BEACON_TYPE    1
#define    MAX_PACK_LENGTH    12

#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"	 
#include "spi.h"
#include "A7139.h"
#include "sys.h" 
#include "delay.h"
#include "stm32f10x.h"
#include "core_cm3.h"
#include "timer.h"
#include "A7139_CONFIG.h"
#include "stm32f10x_exti.h"

#include "stdio.h"
#include "interrupt.h"
#include "join.h"
#include "ProcessEvent.h"
#include "beacon.h"


extern uint8 DataSendBuffer[MAX_PACK_LENGTH];
#endif
