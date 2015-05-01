#include "common.h"


#define SIZE sizeof(TEXT_Buffer)
u8 test[64];

int main(void)
{	 
    int i=0;
    for(i=0;i<64;i++)
        test[i]=i+20;
    DisableInterrupt();
    sys_init();
    EnableInterrupt();
    while(1)
    {
        
    }
    // 	  for(;;)
    // 		{
    // 				//Process_Event();
    // 		}
    
    /********************send test***********************/ 	 
    // 		A7139_SetPackLen(32);	
    // 		while(1)
    // 		{
    // 				A7139_WriteFIFO(test,32);
    // 				delay_us(2);
    // 				A7139_StrobeCmd(CMD_TX);
    // 		    delay_us(2);
    // 				//while(GIO1); 		
    // 				//delay_ms(11);																																																																		delay_ms(1000);
    // 				LED1_REV();	
    // 				delay_ms(500);			
    // 		}
    /*******************************************************/		
    /*****************receive test**************************///用中断测接收	
    // 		while(1)
    // 		{
    // 				//A7139_StrobeCmd(CMD_PLL);
    // 				//delay_us(2);
    // 				A7139_StrobeCmd(CMD_RX);
    // 				delay_us(1);
    // 				while((GIO2==0) ); 	
    // 				A7139_ReadFIFO(DataRecv,32);
    // 				LED2_REV();
    // 		}	  
    /*******************************************************/							
    
}

