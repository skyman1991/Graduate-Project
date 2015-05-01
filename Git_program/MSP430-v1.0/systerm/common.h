#ifndef _COMMON_h_
#define _COMMON_h_

#define    MAX_PACK_LENGTH    12
#define    MAX_DEVICE_NUM  254
#define    PHY_ADDRESS     0x00000001

#include "types.h"
#include "A7139.h"
#include "A7139_CONFIG.h"
#include "board.h"
#include "digio.h"
#include "defs.h"
#include "int.h"
#include "delay.h"
#include "led.h"
#include <msp430.h>
#include "spi.h"
#include "mcu.h"
#include "sys.h"
#include "timer.h"
#include "uart.h"
#include "in430.h"
#include "adc.h"
#include "trsdata.h"
#include "join.h"
#include "ProcessEvent.h"
#include "interrupt.h"
#include <stdio.h>
#include <string.h>

#define    ACK_EN    1
#define    ACK_DIS   0
#define    BEACON_TYPE         1
#define    JOINREQUEST_TYPE    2
typedef struct{
    uint8 cluster_id;
    uint8 cluster_innernum;
    uint8 des_cluster_id;
    uint8 channel;
    uint8 pyh_address;
}EndPointDeviceStruct;
extern EndPointDeviceStruct EndPointDevice;
#endif