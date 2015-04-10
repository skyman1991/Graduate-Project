/***********************************************************************************
    Filename: hal_led.h

    Copyright 2007 Texas Instruments, Inc.
***********************************************************************************/

#ifndef HAL_LED_H
#define HAL_LED_H

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>

//----------------------------------------------------------------------------------
// Function declarations
//----------------------------------------------------------------------------------

void halLedSet(uint8 led_id);
void halLedClear(uint8 led_id);
void halLedToggle(uint8 led_id);


#ifdef  __cplusplus
}
#endif

/**********************************************************************************/
#endif
