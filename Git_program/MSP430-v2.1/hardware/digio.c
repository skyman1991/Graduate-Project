/***********************************************************************************
    Filename: digio.c

    Copyright 2007 Texas Instruments, Inc.
***********************************************************************************/

#include "digio.h"
#include "common.h"

// The number of ports and pins supported by a microcontroller will
// vary (e.g. different families of MSP430 have different number of
// ports, and not all will support interrupts on port 2). The TEMPLATE
// HAL implements support for interrupts on port 1 and up to two ports.


//static ISR_FUNC_PTR port1_isr_tbl[8] = {0};
//static ISR_FUNC_PTR port2_isr_tbl[8] = {0};



//----------------------------------------------------------------------------------
//  uint8 halDigioConfig(const digioConfig* p)
//
//  DESCRIPTION:
//    Configure the pin as specified by p.
//----------------------------------------------------------------------------------
uint8 halDigioConfig(const digioConfig* p)
{
    register volatile uint8* dir;
    register volatile uint8* out;
    register const uint8 bitmask = p->pin_bm;

    // Sanity check
    if ((bitmask == 0) || (bitmask != (uint8)BV(p->pin)))
    {
        return(HAL_DIGIO_ERROR);
    }

    switch(p->port)
    {
        case 1: P1SEL &= ~bitmask; out = &P1OUT; dir = &P1DIR; break;
        case 2: P2SEL &= ~bitmask; out = &P2OUT; dir = &P2DIR; break;
        case 3: P3SEL &= ~bitmask; out = &P3OUT; dir = &P3DIR; break;
        default: return(HAL_DIGIO_ERROR);
    }

    if (p->dir == HAL_DIGIO_OUTPUT)
    {
        if (p->initval == 1)
        {
            *out |= bitmask;
        }
        else
        {
            *out &= ~bitmask;
        }
        *dir |= bitmask;
    }
    else // input
    {
        *out &= ~bitmask;
        *dir &= ~bitmask;
    }
    return(HAL_DIGIO_OK);
}

//----------------------------------------------------------------------------------
//  uint8 halDigioSet(digioConfig* p)
//----------------------------------------------------------------------------------
uint8 halDigioSet(const digioConfig* p)
{
    if (p->dir == HAL_DIGIO_OUTPUT)
    {
        switch (p->port)
        {
            case 1: P1OUT |= p->pin_bm; break;
            case 2: P2OUT |= p->pin_bm; break;
            case 3: P3OUT |= p->pin_bm; break;
            default: return(HAL_DIGIO_ERROR);
        }
        return(HAL_DIGIO_OK);
    }
    return(HAL_DIGIO_ERROR);
}

//----------------------------------------------------------------------------------
//  uint8 halDigioClear(const digioConfig* p)
//----------------------------------------------------------------------------------
uint8 halDigioClear(const digioConfig* p)
{
    if (p->dir == HAL_DIGIO_OUTPUT)
    {
        switch (p->port)
        {
            case 1: P1OUT &= ~p->pin_bm; break;
            case 2: P2OUT &= ~p->pin_bm; break;
            case 3: P3OUT &= ~p->pin_bm; break;
            default: return(HAL_DIGIO_ERROR);
        }
        return(HAL_DIGIO_OK);
    }
    return(HAL_DIGIO_ERROR);
}

//----------------------------------------------------------------------------------
//  uint8 halDigioToggle(const digioConfig* p)
//----------------------------------------------------------------------------------
uint8 halDigioToggle(const digioConfig* p)
{
    if (p->dir == HAL_DIGIO_OUTPUT)
    {
        switch (p->port)
        {
            case 1: P1OUT ^= p->pin_bm; break;
            case 2: P2OUT ^= p->pin_bm; break;
            case 3: P3OUT ^= p->pin_bm; break;
            default: return(HAL_DIGIO_ERROR);
        }
        return(HAL_DIGIO_OK);
    }
    return(HAL_DIGIO_ERROR);
}

//----------------------------------------------------------------------------------
//  uint8 halDigioGet(const digioConfig* p)
//----------------------------------------------------------------------------------
uint8 halDigioGet(const digioConfig* p)
{
    if (p->dir == HAL_DIGIO_INPUT)
    {
        switch (p->port)
        {
            case 1: return (P1IN & p->pin_bm ? 1 : 0);
            case 2: return (P2IN & p->pin_bm ? 1 : 0);
            case 3: return (P3IN & p->pin_bm ? 1 : 0);
            default: break;
        }
    }
    return(HAL_DIGIO_ERROR);
}

//----------------------------------------------------------------------------------
//  uint8 halDigioIntConnect(const digioConfig *p, ISR_FUNC_PTR func)
//----------------------------------------------------------------------------------
//uint8 halDigioIntConnect(const digioConfig *p, ISR_FUNC_PTR func)
//{
//    istate_t key;
//    HAL_INT_LOCK(key);
//    switch (p->port)
//    {
//        case 1: port1_isr_tbl[p->pin] = func; break;
//        case 2: port2_isr_tbl[p->pin] = func; break;
//        default: HAL_INT_UNLOCK(key); return(HAL_DIGIO_ERROR);
//    }
//    halDigioIntClear(p);
//    HAL_INT_UNLOCK(key);
//    return(HAL_DIGIO_OK);
//}


//----------------------------------------------------------------------------------
//  uint8 halDigioIntEnable(const digioConfig *p)
//----------------------------------------------------------------------------------
uint8 halDigioIntEnable(const digioConfig *p)
{
    switch (p->port)
    {
        case 1: P1IE |= p->pin_bm; break;
        case 2: P2IE |= p->pin_bm; break;
        default: return(HAL_DIGIO_ERROR);
    }
    return(HAL_DIGIO_OK);
}

//----------------------------------------------------------------------------------
//  uint8 halDigioIntDisable(const digioConfig *p)
//----------------------------------------------------------------------------------
uint8 haldigioIntDisable(const digioConfig *p)
{
    switch (p->port)
    {
        case 1: P1IE &= ~p->pin_bm; break;
        case 2: P2IE &= ~p->pin_bm; break;
        default: return(HAL_DIGIO_ERROR);
    }
    return(HAL_DIGIO_OK);
}

//----------------------------------------------------------------------------------
//  uint8 halDigioIntClear(const digioConfig *p)
//----------------------------------------------------------------------------------
uint8 halDigioIntClear(const digioConfig *p)
{
    switch (p->port)
    {
        case 1: P1IFG &= ~p->pin_bm; break;
        case 2: P2IFG &= ~p->pin_bm; break;
        default: return(HAL_DIGIO_ERROR);
    }
    return(HAL_DIGIO_OK);
}

//----------------------------------------------------------------------------------
//  uint8 halDigioIntSetEdge(const digioConfig *p, uint8 edge)
//----------------------------------------------------------------------------------
uint8 halDigioIntSetEdge(const digioConfig *p, uint8 edge)
{
    switch(edge)
    {
        case HAL_DIGIO_INT_FALLING_EDGE:
            switch(p->port)
            {
                case 1: P1IES |= p->pin_bm; break;
                case 2: P2IES |= p->pin_bm; break;
                default: return(HAL_DIGIO_ERROR);
            }
            break;

         case HAL_DIGIO_INT_RISING_EDGE:
            switch(p->port)
            {
                case 1: P1IES &= ~p->pin_bm; break;
                case 2: P2IES &= ~p->pin_bm; break;
                default: return(HAL_DIGIO_ERROR);
            }
            break;

         default:
            return(HAL_DIGIO_ERROR);
    }
    return(HAL_DIGIO_OK);
}


//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------


//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
/*#pragma vector=PORT2_VECTOR
__interrupt void port2_ISR(void)
{
    register uint8 i;
    if (P2IFG)
    {
        for (i = 0; i < 8; i++)
        {
            register const uint8 pinmask = 1 << i;
            if ((P2IFG & pinmask) && (P2IE & pinmask) && (port2_isr_tbl[i] != 0))
            {
                (*port2_isr_tbl[i])();
                P2IFG &= ~pinmask;
            }
        }
        __low_power_mode_off_on_exit();
    }
}*/
