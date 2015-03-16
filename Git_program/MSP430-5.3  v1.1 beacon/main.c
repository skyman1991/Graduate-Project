
/* Includes ------------------------------------------------------------------*/
#include "common.h"

uint8 test[64];
int time = 0;
int main(void)
{	 
int i=0;
  StateError = 0;
  for(i=0;i<64;i++)
    test[i] = i;
  __disable_interrupt();
  halBoardInit();
  __enable_interrupt();
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
      
    }
  }
}
  
  
  
  
  
  //A7139_StrobeCmd(CMD_TX);
//  while(1)
//  {
//    A7139_StrobeCmd(CMD_PLL);
//    delay_us(2);
//    A7139_WriteFIFO(test,MAX_DATA_LENGTH);
//    delay_us(2);
//    A7139_StrobeCmd(CMD_TX);
//    delay_us(2);
//    while(GIO2); 		
//    delay_ms(1000); 
//    halLedToggle(1);
//    
//    /*A7139_WriteFIFO(test,DATA_LENGTH);
//    delay_ms(50); 
//    halLedToggle(1);*/
//  }
  //    //A7139_StrobeCmd(CMD_RX);
//      while(1){
//        
//          A7139_StrobeCmd(CMD_PLL);
//          delay_us(2);
//          A7139_StrobeCmd(CMD_RX);
//          delay_us(2);
//          while((GIO2==1)); 	
//          A7139_ReadFIFO(DataRecv,MAX_DATA_LENGTH);
//          //halUartWrite(bufRecv,DATA_LENGTH);             
//          //A7139_StrobeCmd(CMD_STBY);
//          delay_ms(10);
//          halLedToggle(1);
//        
//          /*while((GIO2==1)); 	
//          A7139_ReadFIFO(bufRecv,DATA_LENGTH);
//          halLedToggle(1);
//          delay_ms(10);*/
//      }
//}