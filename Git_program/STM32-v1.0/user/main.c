#include "common.h"
uint8 DataSendBuffer[MAX_PACK_LENGTH];
int main(void)
{	 
	  uint8 test[64],i;
		DisableInterrupt();
		sys_init();
		EnableInterrupt();

	  for(;;)
		{
				Process_Event();
		}
	
	
	
// 		for(i=0;i<64;i++)
// 		{
// 				test[i]=i;
// 		}
/********************send test***********************/ 	 
// 		while(1)
// 		{
// 				A7139_StrobeCmd(CMD_PLL);
// 				delay_us(1);
// 			  A7139_WriteFIFO(test,MAX_PACK_LENGTH);
// 				delay_us(1);
// 				A7139_StrobeCmd(CMD_TX);
// 		    delay_us(1);
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

