/******************************************************************************
    Filename: board.h

    Copyright 2007 Texas Instruments, Inc.
******************************************************************************/

#ifndef BOARD_H
#define BOARD_H

#include "types.h"
#include "digio.h"
#include "msp430.h"


//----------------------------------------------------------------------------------
//  Easy access, zero overhead LED macros
//  Adapted to hardware interface on MSP430 Experimenter Board
//----------------------------------------------------------------------------------
#define HAL_LED_SET_1   (P1OUT |= BIT3)//¡¡
#define HAL_LED_SET_2   (P1OUT |= BIT2)
#define HAL_PLU_SET     (P3OUT |= BIT0)
      
#define HAL_LED_CLR_1   (P1OUT &= ~ BIT3)
#define HAL_LED_CLR_2   (P1OUT &= ~ BIT2)
#define HAL_PLU_CLR     (P3OUT &= ~ BIT0)

#define HAL_LED_TGL_1   (P1OUT ^= BIT3)
#define HAL_LED_TGL_2   (P1OUT ^= BIT2)
#define HAL_PLU_TGL     (P3OUT ^= BIT0)

//----------------------------------------------------------------------------------
//  Define ports and pins used by SPI interface to CC1100/CC2500
//----------------------------------------------------------------------------------
/*#define HAL_SPI_SOMI_PORT 3
#define HAL_SPI_SOMI_PIN  2
#define HAL_SPI_SIMO_PORT 3
#define HAL_SPI_SIMO_PIN  1
#define HAL_SPI_CLK_PORT  3
#define HAL_SPI_CLK_PIN   3
#define HAL_SPI_CS_PORT   3
#define HAL_SPI_CS_PIN    0*/

//----------------------------------------------------------------------------------
// Select interface on MSP430 to use for SPI (define only one!)
//----------------------------------------------------------------------------------

// #define HAL_SPI_INTERFACE_USART0
//#define HAL_SPI_INTERFACE_USART1
// #define HAL_SPI_INTERFACE_USCIA0
// #define HAL_SPI_INTERFACE_USCIA1
 #define HAL_SPI_INTERFACE_USCIB0
// #define HAL_SPI_INTERFACE_USCIB1
// #define HAL_SPI_INTERFACE_USI
// #define HAL_SPI_INTERFACE_BITBANG



#ifdef __cplusplus
extern "C" {
#endif

extern const digioConfig pinLed1;
extern const digioConfig pinLed2;
extern const digioConfig pinGIO2;

//----------------------------------------------------------------------------------
// Function declarations
//----------------------------------------------------------------------------------

extern void halBoardInit(void);


#ifdef __cplusplus
}

#endif

/**********************************************************************************/
#endif
