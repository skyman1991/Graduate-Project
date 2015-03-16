#include "common.h"


#define SIZE sizeof(TEXT_Buffer)
u8 test[64];

int main(void)
{	 
		int i=0;
	  for(i=0;i<64;i++)
			test[i]=i;
		sys_init();
	
	  for(;;)
		{

			
			if(BeaconSendFlag == 1)
				{					  
					  //------------4.48MS---------------
					  //LED2_OFF();
					  BeaconSendFlag = 0;
					  DataQueue();
					  A7139_StrobeCmd(CMD_PLL);
					  delay_us(1);
						A7139_WriteFIFO(DataSend,64);
						delay_us(1);
					  A7139_StrobeCmd(CMD_TX);
					  //----------------------------------
					  
					  delay_ms(11);  //发送时间大约为9ms
					  //LED2_ON();
						//接到GPO1后把delay换成while(GPO1);
					  
						//while(GIO1);
					  //A7139_StrobeCmd(CMD_PLL);
						//delay_us(2);

					  //----------------------------------
						A7139_StrobeCmd(CMD_RX);
						delay_us(1);
					  //----------------------------------
					  LED1_REV();

				}
		}
	 
	 
	 
	 
	 
		
	 

		/*while(1)
		{
			
				//A7139_StrobeCmd(CMD_PLL);
				//delay_us(2);
			  LED2_ON();
				A7139_WriteFIFO(test,MAX_DATA_LENGTH);
				delay_us(2);
				A7139_StrobeCmd(CMD_TX);
		    delay_us(2);
				
				while(GIO2); 		
			  LED2_OFF();
				LED1_REV();
			  
				delay_ms(1000);*/
				
			  /*A7139_WriteFIFO(DataSend,MAX_DATA_LENGTH);
				LED1_REV();
				delay_ms(50);*/
				
				
			  /*A7139_StrobeCmd(CMD_PLL);
				delay_us(2);
				A7139_StrobeCmd(CMD_RX);
				delay_us(2);
				while((GIO2==1) ); 	
				A7139_ReadFIFO(DataRecv,MAX_DATA_LENGTH);
				LED2_REV();*/
				
				/*if(DataRecv[1]!=0x01)
					 LED3_REV();
				
				A7139_StrobeCmd(CMD_STBY);
				delay_ms(10);
				
			
		}*/
}
