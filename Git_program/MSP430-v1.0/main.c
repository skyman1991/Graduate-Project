/*
*
*
*不同节点程序修改trsdata.h中NODE_NUM即可
*/

#include "common.h"
uint8 test[128];
int time = 0;
int main(void)
{	 
  int i=0;
  for(i=0;i<128;i++)
    test[i] = i;
Reset:
  StateError = 0;

  __disable_interrupt();
  halBoardInit();
  __enable_interrupt();
  for(;;)
  {
    if(send_flag == 1)
    {
      __disable_interrupt();
      send_flag = 0;
      //收到数据后开始发送 0.3ms-1ms
      /************************/
      DataQueue();
      A7139_StrobeCmd(CMD_PLL);
      delay_us(1);
      A7139_WriteFIFO(DataSend,64);
      delay_us(1);
      A7139_StrobeCmd(CMD_TX);
      delay_us(1);
      /*******2.46ms*********/
      halLedClear(1);
      while(GIO1)
      {
          if(StateError++>400000)
            break;
      }//发送时间约为10.17ms
      //delay_ms(11);
      /**从接收中断到发送完成需要13.5ms***/
      A7139_StrobeCmd(CMD_SLEEP);
      delay_us(1);
#if(SLEEP_ENABLE)
      delay_ms((int)(BECAON_PERIOD-(FIRST_BEACON_ACK_TIME+BEACON_ACK_PERIOD*(NODE_NUM-2))));
      A7139_StrobeCmd(CMD_STBY);
      delay_ms(2);
#endif
      A7139_StrobeCmd(CMD_PLL);
      delay_us(1);
      A7139_StrobeCmd(CMD_RX);
      delay_us(1);
      
      StateError = 0;
      EN_EXITINT;
      __enable_interrupt();
      /*******719us**********/
    }   
    else if(ResetEnable == 1)
    {
        StateError++;
        
        //halLedSet(1);
        if(StateError>850000)
        {
          //StateError = 0;
          //halLedClear(1);
          StateErrorTimes++;
          goto Reset;
        }
    }
  }
  
  
  
  
  
  //A7139_StrobeCmd(CMD_TX);
//  while(1)
//  {
//    A7139_StrobeCmd(CMD_PLL);
//    delay_us(2);
//    A7139_WriteFIFO(test,32);
//    delay_us(2);
//    A7139_StrobeCmd(CMD_TX);
//    delay_us(2);
//    while(GIO2); 		
//    delay_ms(50); 
//    halLedToggle(1);
//    
//    /*A7139_WriteFIFO(test,DATA_LENGTH);
//    delay_ms(50); 
//    halLedToggle(1);*/
//  }
//      A7139_StrobeCmd(CMD_RX);
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
}