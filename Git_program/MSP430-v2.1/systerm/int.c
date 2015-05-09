/***********************************************************************************
    Filename: hal_int.c

    Copyright 2007 Texas Instruments, Inc.
***********************************************************************************/

#include "common.h"


//----------------------------------------------------------------------------------
//  void halIntOn(void)
//
//  DESCRIPTION:
//    Enable global interrupts.
//----------------------------------------------------------------------------------
void halIntOn(void)
{
    HAL_INT_ON();
}

//----------------------------------------------------------------------------------
//  void halIntOff(void)
//
//  DESCRIPTION:
//    Turns global interrupts off.
//----------------------------------------------------------------------------------
void halIntOff(void)
{
    HAL_INT_OFF();
}

//----------------------------------------------------------------------------------
//  uint16 halIntLock(void)
//
//  DESCRIPTION:
//    Turns global interrupts off and returns current interrupt state.
//    Should always be used together with halIntUnlock().
//----------------------------------------------------------------------------------
uint16 halIntLock(void)
{
    istate_t key;
    HAL_INT_LOCK(key);
    return(key);
}

//----------------------------------------------------------------------------------
//  void halIntUnlock(uint16 key)
//
//  DESCRIPTION:
//    Set interrupt state back to the state it had before calling halIntLock().
//    Should always be used together with halIntLock().
//----------------------------------------------------------------------------------
void halIntUnlock(uint16 key)
{
    HAL_INT_UNLOCK(key);
}
