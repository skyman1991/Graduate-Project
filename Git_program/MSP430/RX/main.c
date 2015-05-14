#include "common.h"

uint8 normal_test[MAX_PACK_LENGTH];
uint8 test_rssi = 0;
uint16 address = 0;

int main(void)
{	    
    uint8 i=0;
    __disable_interrupt();
    halBoardInit();    
    A7139_SetPackLen(MAX_PACK_LENGTH);
    delay_us(1);
    A7139_SetFreq(470.001f);
    delay_us(1);
    A7139_Cal();                    //更改完频率后校准
    delay_us(1);
    
    for(i=0;i<MAX_PACK_LENGTH;i++)
    {
       normal_test[i]=i;
    }


    __enable_interrupt();
    for(;;)
    {
        
    }
 
    /****************receive test**********************/
//    while(1)
//    {
//        A7139_StrobeCmd(CMD_RX);
//        delay_us(2);
//        while((GIO1)); 	
//        A7139_ReadFIFO(DataRecvBuffer,12);
//        halLedToggle(1);
//    }
    /***************************************************/
}
