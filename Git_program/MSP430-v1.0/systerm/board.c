/***********************************************************************************
Filename: board.c

Copyright 2007 Texas Instruments, Inc.
***********************************************************************************/
#include "common.h"

//------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------

// The constants below define some of the I/O signals used by the board
// Port, pin number, pin bitmask, direction and initial value should be
// set in order to match the target hardware. Once defined, the pins are
// configured in halBoardInit() by calling halDigioConfig()

const digioConfig pinLed1   = {1, 3, BIT3, HAL_DIGIO_OUTPUT, 0};
//const digioConfig pinLed2   = {1, 2, BIT2, HAL_DIGIO_OUTPUT, 0};
const digioConfig pinGIO2   = {1, 5, BIT5, HAL_DIGIO_INPUT,  0};
const digioConfig pinGIO1   = {1, 2, BIT2, HAL_DIGIO_INPUT,  0};
//------------------------------------------------------------------------------
//  void halBoardInit(void)
//
//  DESCRIPTION:
//    Set up board. Initialize MCU, configure I/O pins and user interfaces
//------------------------------------------------------------------------------
void halBoardInit(void)
{
    halMcuInit();
    
    halDigioConfig(&pinLed1);
    //halDigioConfig(&pinLed2);
    halDigioConfig(&pinGIO1);
    halDigioConfig(&pinGIO2);//中断
    halUartInit(0, 0);
    halLedSet(1);
    // sched_init();
    //中断初始化
    time_init();
    SPI3_Init();
    A7139_Init(470.001f);
    Interrupt_Init();
}
