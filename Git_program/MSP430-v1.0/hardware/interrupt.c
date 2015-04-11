#include "common.h"
int    send_flag = 0;
uint8  DataRecv[MAX_DATA_LENGTH];
uint8  DataSend[MAX_DATA_LENGTH];
uint16 TDMA_time = 0;
uint8  SendOnce = 0;
uint32 StateError = 0;
uint8  StateErrorTimes = 0;
uint8  ResetEnable = 0;
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
        /*************************/
        //halLedClear(1);
        ResetEnable = 1;
        P1IFG &= ~pinGIO2.pin_bm;                           // P1.4 IFG cleared
        A7139_ReadFIFO(DataRecv,MAX_DATA_LENGTH);
        delay_us(2);
        A7139_StrobeCmd(CMD_RX);
        delay_us(2);
        if((DataRecv[1] == SINK_ADDRESS)&&(DataRecv[0] == CMD_BEACON))
        {
            EN_TIMER;
            DIS_EXITINT;
            TDMA_time = 0;
            halLedSet(1);
#if(SLEEP_ENABLE)
            if(S_ADDRESS != 2)
            {
                A7139_StrobeCmd(CMD_SLEEP);
                delay_us(1);
            }
#endif
        } 
        
        //halLedToggle(1);
        /********2.4ms*************/   
    }
    
}
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer_A (void)
{
    TA1CCTL0 &= ~CCIFG;
    //halLedToggle(1);
    if(TDMA_time == (NODE_NUM-2)*TDMA_GAP_K+TDMA_GAP_D)
        //if(TDMA_time == 150)
    {
        send_flag = 1;
        DataRecv[1] = 0;
        DataRecv[2] = 0;
        DIS_TIMER;
    }
#if(SLEEP_ENABLE)
    if(TDMA_time == (NODE_NUM-2)*TDMA_GAP_K-30+TDMA_GAP_D)
    {
        A7139_StrobeCmd(CMD_STBY);
        delay_us(1);
    }
#endif
    TDMA_time++;
}