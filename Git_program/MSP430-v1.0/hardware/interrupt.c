#include "common.h"
uint8  DataRecv[MAX_DATA_LENGTH];
uint8  DataSend[MAX_DATA_LENGTH];
void Interrupt_Init(void)
{
    P1DIR &=~ pinGIO2.pin_bm;
    /*halDigioIntSetEdge(&pinGIO2, HAL_DIGIO_INT_RISING_EDGE);
    halDigioIntConnect(&pinGIO2, &EXTI9_5_IRQHandler);
    halDigioIntEnable(&pinGIO2);*/
    P1REN |= pinGIO2.pin_bm;                            // P1.4 pullup
    P1IE |= pinGIO2.pin_bm;                             // P1.4 interrupt enabled
    P1IES |= pinGIO2.pin_bm;                            // HAL_DIGIO_INT_RISING_EDGE
    P1IFG &= ~pinGIO2.pin_bm;                           // P1.4 IFG cleared
    
    A7139_StrobeCmd(CMD_PLL);
    delay_us(2);
    A7139_StrobeCmd(CMD_RX);
    delay_us(2);
    
}

void EXTI9_5_IRQHandler(void)
{
    A7139_ReadFIFO(DataRecv,MAX_DATA_LENGTH);
    halLedToggle(1);
    A7139_StrobeCmd(CMD_STBY);
    delay_ms(2);
    A7139_StrobeCmd(CMD_PLL);
    delay_ms(2);
    A7139_StrobeCmd(CMD_RX);
    delay_ms(2);
    halDigioIntClear(&pinGIO2);                           // P1.5 IFG cleared
    
}
#pragma vector=PORT1_VECTOR
__interrupt void port1_ISR(void)
{
    
    if(P1IFG & pinGIO2.pin_bm)
    {
        P1IFG &= ~pinGIO2.pin_bm;                           // P1.4 IFG cleared
        A7139_ReadFIFO(DataRecv,10);
        delay_us(2);
        A7139_StrobeCmd(CMD_RX);
        delay_us(2);
  
    }
    
}
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer_A (void)
{
    TA1CCTL0 &= ~CCIFG;
}