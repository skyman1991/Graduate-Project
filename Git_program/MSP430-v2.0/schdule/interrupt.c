#include "common.h"
uint8   Receive_Timeout = 0;
int     Frame_Time = 0;
void Interrupt_Init(void)
{
    P1DIR &=~ pinGIO2.pin_bm;
    /*halDigioIntSetEdge(&pinGIO2, HAL_DIGIO_INT_RISING_EDGE);
    halDigioIntConnect(&pinGIO2, &EXTI9_5_IRQHandler);
    halDigioIntEnable(&pinGIO2);*/
    P1REN |= pinGIO2.pin_bm;                            // P1.4 pullup
    P1IE |= pinGIO2.pin_bm;                             // P1.4 interrupt enabled
    P1IES &= ~pinGIO2.pin_bm;                            // HAL_DIGIO_INT_RISING_EDGE
    P1IFG &= ~pinGIO2.pin_bm;                           // P1.4 IFG cleared
   
    RXMode();
    
}
int error_test = 0;
uint16 packet_count = 0;
uint8 rssi_what = 0;
#pragma vector=PORT1_VECTOR
__interrupt void port1_ISR(void)
{
    
    if(P1IFG & pinGIO2.pin_bm)
    {
        P1IFG &= ~pinGIO2.pin_bm;                           // P1.4 IFG cleared
        //DIS_TIMER1;
        A7139_ReadFIFO(DataRecvBuffer,MAX_PACK_LENGTH);
        delay_us(2);
        A7139_StrobeCmd(CMD_RX);
        delay_us(2);
        EndPointDevice.state = CMD_RX;
        Receive_Timeout = 0;
        switch (Unpack(DataRecvBuffer))
        {
            case BEACON_TYPE:
              PostTask(BEACON_HANDLER);
              break;
        }
        Frame_Time = 0;
        halLedToggle(1);
        //EN_TIMER1;
          
              
    }
    
}

//100us
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer_A (void)
{
    TA1CCTL0 &= ~CCIFG;
    Frame_Time++;
   
}

//1s
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0(void)
{
    TA0CCTL0 &= ~CCIFG;
    Receive_Timeout++;
    if(Receive_Timeout>10)
    {
        EndPointDevice.state = CMD_STBY;
        A7139_StrobeCmd(CMD_STBY);
        delay_us(1);
        A7139_StrobeCmd(CMD_PLL);
        delay_us(1);
        A7139_StrobeCmd(CMD_RX);
        delay_us(1);
        Receive_Timeout = 0;
    }

}