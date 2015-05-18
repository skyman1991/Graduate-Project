#include "common.h"
uint8   Receive_Timeout = 0;            //接收超时重启
uint32     Frame_Time = 0;                 //超帧内计时
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
        
        
        if(PackValid())
        {
            switch (Unpack(DataRecvBuffer))
            {
              case BEACON_TYPE:
                Frame_Time = 0;
                //EN_TIMER1;
                TA1CCTL0 = CCIE;
                PostTask(EVENT_BEACON_HANDLER);
                break;
              case JOINREQUESTACK_TYPE:
                PostTask(EVENT_JOINREQUESTACK_HANDLER);
                break;
              case DATAACK_TYPE:
                PostTask(EVENT_DATAACK_HANDLER);
                break;
            }
            halLedClear(1);
            TIME1_HIGH;
        }
        

        Receive_Timeout = 0;   
    } 
}

//100us
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer_A (void)
{
    TA1CCTL0 &= ~CCIFG;
    Frame_Time++;
#if (SLEEP_EN)
    if(Frame_Time==BEFOR_BEACON_WAKE)
    {
        PostTask(EVENT_WAKE_A7139);
    }
#endif
        

}

//1s
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0(void)
{
    TA0CCTL0 &= ~CCIFG;
    if(EndPointDevice.power == 0)
    {
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
    else if(EndPointDevice.power == 1)
    {
        PostTask(EVENT_COLLECT_DATA);
        Receive_Timeout++;
        if(Receive_Timeout>=(EndPointDevice.cluster_innernum))
        {
            Receive_Timeout = 0;
            Data_Change_Flag = 1;
        }
    }
    

}