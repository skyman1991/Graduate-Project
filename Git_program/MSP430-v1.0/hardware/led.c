/***********************************************************************************
Filename: led.c

Copyright 2007 Texas Instruments, Inc.
***********************************************************************************/
#include "led.h"
#include "common.h"



//----------------------------------------------------------------------------------
//  void halLedSet(uint8 id)
//
//  DESCRIPTION:
//    Turn LED on.
//----------------------------------------------------------------------------------
void halLedSet(uint8 id)
{
    switch (id)
    {
        case 1: HAL_LED_SET_1; break;
        case 2: HAL_LED_SET_2; break;
        default: break;
    }
}

//----------------------------------------------------------------------------------
//  void halLedClear(uint8 id)
//
//  DESCRIPTION:
//    Turn LED off.
//----------------------------------------------------------------------------------
void halLedClear(uint8 id)
{
    switch (id)
    {
        case 1: HAL_LED_CLR_1; break;
        case 2: HAL_LED_CLR_2; break;
        default: break;
    }
}
//----------------------------------------------------------------------------------
//  void halLedToggle(uint8 id)
//
//  DESCRIPTION:
//    Change state of LED. If on, turn it off. Else turn on.
//----------------------------------------------------------------------------------
void halLedToggle(uint8 id)
{
    switch (id)
    {
        case 1: HAL_LED_TGL_1; break;
        case 2: HAL_LED_TGL_2; break;
        default: break;
    }
}


