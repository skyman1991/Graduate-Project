/***********************************************************************************
    Filename: hal_int.h

    Copyright 2007 Texas Instruments, Inc.
***********************************************************************************/

#ifndef INT_H
#define INT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>


//----------------------------------------------------------------------------------
// MACROS
//----------------------------------------------------------------------------------

#ifdef __ICC430__

// Use the macros below to reduce function call overhead for common
// global interrupt control functions

#define HAL_INT_ON(x)      st( __enable_interrupt();)
#define HAL_INT_OFF(x)     st( __disable_interrupt();)
#define HAL_INT_LOCK(x)    st( (x) = __get_interrupt_state(); __disable_interrupt();)
#define HAL_INT_UNLOCK(x)  st( __set_interrupt_state(x);)

#else
#error "Unsupported compiler"
#endif

//----------------------------------------------------------------------------------
// Function declarations
//----------------------------------------------------------------------------------

extern void  halIntOn(void);
void   halIntOff(void);
uint16 halIntLock(void);
void   halIntUnlock(uint16 key);


#ifdef  __cplusplus
}
#endif

/**********************************************************************************/
#endif
