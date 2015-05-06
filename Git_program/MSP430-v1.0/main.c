#include "common.h"
uint8 normal_test[MAX_PACK_LENGTH];

int main(void)
{	    
    int i=0;
    __disable_interrupt();
    halBoardInit();
    EndPointDevice.pyh_address = PHY_ADDRESS;
    EndPointDevice.device_type = DEVICE;
    for(i=0;i<MAX_PACK_LENGTH;i++)
    {
       normal_test[i]=i; 
    }
    
    Scan_Channel(StartChannel,EndChannel);
    SortChannel();
//    SendJoinRequest();
    __enable_interrupt();
    
    for(;;)
    {
        Process_Event();
    }
    /****************send test**********************/  
//    while(1) 
//    {    
//        A7139_WriteFIFO(normal_test,MAX_PACK_LENGTH);
//        delay_us(1);
//        A7139_StrobeCmd(CMD_TX);
//        delay_us(1);
//        halLedToggle(1);
//        while(GIO1)
//        {}
//        delay_ms(100);
//    }
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
