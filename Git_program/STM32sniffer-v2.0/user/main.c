#include "common.h"
uint8 DataSendBuffer[MAX_PACK_LENGTH];
uint8 rssise = 0;
int main(void)
{	 
	  uint8 test[64],i;
		DisableInterrupt();
		sys_init();
		EnableInterrupt();
	  for(;;)
		{
				//Process_Event();
		}
	
	
	
// 		for(i=0;i<64;i++)
// 		{
// 				test[i]=i;
// 		}
// /********************send test***********************/ 	 
// 		
// 		while(1)
// 		{
// 				A7139_StrobeCmd(CMD_PLL);
// 				delay_us(1);
// 			  A7139_WriteFIFO(test,64);
// 				delay_us(1);
// 				A7139_StrobeCmd(CMD_TX);
// 		    delay_us(1);
// 				while(GIO2); 		
// 				//delay_ms(11);																																																																		delay_ms(1000);
// 				LED1_REV();	
// 				delay_ms(50);	
// 		}
/*******************************************************/		
/*****************receive test**************************///用中断测接收	
// 		while(1)
// 		{
// 				A7139_StrobeCmd(CMD_PLL);
// 				delay_us(2);
// 				A7139_StrobeCmd(CMD_RX);
// 				delay_us(1);
// 				while(GIO1); 	
// 				A7139_ReadFIFO(DataRecv,64);
// 				LED2_REV();
// 		}	  
/*******************************************************/							

}

