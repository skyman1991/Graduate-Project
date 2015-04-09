/***********************************************************************************
    Filename: hal_timer.h

    Copyright 2007 Texas Instruments, Inc.
***********************************************************************************/

#ifndef TIMER_H
#define TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>

//----------------------------------------------------------------------------------
// Function declarations
//----------------------------------------------------------------------------------
extern void time_init(void);
void halTimerRestart(void);
void halTimerIntEnable(void);
void halTimerIntDisable(void);


#ifdef  __cplusplus
}
#endif

/**********************************************************************************/
#endif

