/***********************************************************************************
    Filename: hal_digio.h

    Copyright 2007 Texas Instruments, Inc.
***********************************************************************************/

#ifndef DIGIO_H
#define DIGIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>


enum {
    HAL_DIGIO_INPUT,
    HAL_DIGIO_OUTPUT
};

enum {
    HAL_DIGIO_INT_FALLING_EDGE,
    HAL_DIGIO_INT_RISING_EDGE
};


typedef struct {
    uint8 port;     // port number
    uint8 pin;      // pin number
    uint8 pin_bm;   // pin bitmask
    uint8 dir;      // direction (input or output)
    uint8 initval;  // initial value
} digioConfig;


#define HAL_DIGIO_OK       0
#define HAL_DIGIO_ERROR  (~0)


//----------------------------------------------------------------------------------
// Function declarations
//----------------------------------------------------------------------------------

uint8 halDigioConfig(const digioConfig* p);
uint8 halDigioClear(const digioConfig* p);
uint8 halDigioToggle(const digioConfig* p);
uint8 halDigioSet(const digioConfig* p);
uint8 halDigioGet(const digioConfig* p);

uint8 halDigioIntConnect(const digioConfig *p, ISR_FUNC_PTR func);
uint8 halDigioIntEnable(const digioConfig *p);
uint8 halDigioIntDisable(const digioConfig *p);
uint8 halDigioIntClear(const digioConfig *p);
uint8 halDigioIntSetEdge(const digioConfig *p, uint8 edge);


#ifdef  __cplusplus
}
#endif

#define TIME1_HIGH     (P2OUT |= BIT1)
#define TIME1_LOW      (P2OUT &= ~ BIT1)
extern void GPIO_Init();

/**********************************************************************************/
#endif
