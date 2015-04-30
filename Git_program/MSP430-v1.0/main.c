/*
*
*
*不同节点程序修改trsdata.h中NODE_NUM即可
*/

#include "common.h"
uint8  s;
uint16 t;
uint8 test[128];
int time = 0;

int main(void)
{	 
    int i=0; 
    for(i=0;i<128;i++)
        test[i] = i;
    
    __disable_interrupt();
    halBoardInit();
    
    //  __enable_interrupt();
    //    PostTask(EVENT_SCAN_CHANNEL);
    //
    //    __enable_interrupt();
    //
    //    for(;;)
    //    {
    //        //Process_Event();
    //
    //    }
    /****************send test**********************/  
    while(1) 
    {    
        A7139_WriteFIFO(test,32);
        delay_us(1);
        A7139_StrobeCmd(CMD_TX);
        delay_us(1);
        halLedToggle(1);
        while(GIO1)
        {}
        delay_ms(1000);
    }
    /*************************************************/  
    /****************receive test**********************/
//    while(1)
//    {
//        A7139_StrobeCmd(CMD_RX);
//        delay_us(2);
//        while((GIO1==1)); 	
//        A7139_ReadFIFO(DataRecv,32);
//        halLedToggle(1);
//    }
    /***************************************************/
}
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0(void)
{
    TA0CCTL0 &= ~CCIFG;
    s++;
    if(s==20)
    {
        s=0;
        Sensor_status_Value();
        t++;
        if(t==1000)
        {
            t=0;
            if(AD_flag==0)
                AD_curvalue=ADC10MEM;
        }
    }
}