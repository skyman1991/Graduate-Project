/******************************************************************************
    Filename: mcu.c

    Copyright 2007 Texas Instruments, Inc.
******************************************************************************/

#include "common.h"



//----------------------------------------------------------------------------------
//  void halMcuInit(void)
//
//  DESCRIPTION:
//    Turn off watchdog and set up system clock. Set system clock to 4 MHz using
//    external crystal at 32 kHz
//----------------------------------------------------------------------------------
void halMcuInit(void)
{
    uint16 i;

    /* disable watchdog timer */
     WDTCTL = WDTPW | WDTHOLD;

     //Wait for xtal to stabilize
//    while (IFG1 & OFIFG)
//    {
//        // Clear oscillator fault flag
//        IFG1 &= ~OFIFG;
//       for (i = 0x4800; i > 0; i--) asm("NOP");
//        //for (i = 0x0048; i > 0; i--) asm("NOP");
//    }

    /* configure internal digitally controlled oscillator */
     DCOCTL  = CALDCO_16MHZ;   /* factory calibrated value from flash */
     BCSCTL1 = CALBC1_16MHZ;   /* factory calibrated value from flash */
  
    // BCSCTL3 |= XCAP_3;  //ÅäÖÃµçÈÝÎª12pF  
    // Wait for DCO to synchronize with ACLK (at least 28*32 ACLK cycles)
    for (i = 0x1C00; i > 0; i--) asm("NOP");
}


//-----------------------------------------------------------------------------
//  void halMcuWaitUs(uint16 usec)
//
//  DESCRIPTION:
//    Busy wait function. Waits the specified number of microseconds. Use
//    assumptions about number of clock cycles needed for the various instructions.
//    The duration of one cycle depends on MCLK. In this HAL, it is set
//    to 4 MHz, thus 4 cycles per usec.
//
//    NB! This function is highly dependent on architecture and compiler!
//-----------------------------------------------------------------------------
void halMcuWaitUs(uint16 usec) // 5 cycles for calling
{
    // The least we can wait is 3 usec:
    // ~1 usec for call, 1 for first compare and 1 for return

    while(usec > 3)       // 2 cycles for compare
    {                     // 2 cycles for jump
        asm("NOP");       // 1 cycles for nop
        asm("NOP");       // 1 cycles for nop
        asm("NOP");       // 1 cycles for nop
        asm("NOP");       // 1 cycles for nop
        asm("NOP");       // 1 cycles for nop
        usec -= 2;        // 1 cycles for optimized decrement
    }
}                         // 4 cycles for returning



//-----------------------------------------------------------------------------
//  void halMcuSetLowPowerMode(uint8 mode)
//
//  DESCRIPTION:
//    Sets the MCU in a low power mode. Will turn global interrupts on at
//    the same time as entering the LPM mode. The MCU must be waken from
//    an interrupt (status register on stack must be modified).
//-----------------------------------------------------------------------------
void halMcuSetLowPowerMode(uint8 mode)
{
    switch (mode)
    {
        case HAL_MCU_LPM_0:
            __low_power_mode_0();
            break;
        case HAL_MCU_LPM_1:
            __low_power_mode_1();
            break;
        case HAL_MCU_LPM_2:
            __low_power_mode_2();
            break;
        case HAL_MCU_LPM_3:
            __low_power_mode_3();
            break;
        case HAL_MCU_LPM_4:
            __low_power_mode_4();
            break;
    }
}
