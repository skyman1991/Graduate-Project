#include "common.h"

uint8 rssise = 0;
uint8 bud = 0;
int main(void)
{	 
	  uint8 test[64],i;
 		DisableInterrupt();
		sys_init();
		RootDevice.pyh_address = 0xFFFF;
		RootDevice.cluster_id = ROOT;
		RootDevice.cluster_innernum = 0;
		RootDevice.free_node = MAX_NODE_NUM;
		EnableInterrupt();
		PostTask(EVENT_REJOIN_SEND);
	  for(;;)
		{
				Process_Event();
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
// 			  A7139_WriteFIFO(test,12);
// 				delay_us(1);
// 				A7139_StrobeCmd(CMD_TX);
// 		    delay_us(1);
// 				while(GIO2); 		
// 				//delay_ms(11);																																																																		delay_ms(1000);
// 				LED1_REV();	
// 				delay_ms(500);	
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

