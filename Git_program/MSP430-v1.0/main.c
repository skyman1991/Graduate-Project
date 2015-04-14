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
    
    __disable_interrupt();
    halBoardInit();
    PostTask(Scan_Channel1);
    //__enable_interrupt();
    for(;;)
    {
        Run_TQ();
    }
    
    
    
    
    
    //A7139_StrobeCmd(CMD_TX);
//      while(1)
//      {
//       // A7139_StrobeCmd(CMD_PLL);
//        //delay_us(2);
//        A7139_WriteFIFO(test,64);
//        delay_us(2);
//        A7139_StrobeCmd(CMD_TX);
//        delay_us(2);
//        while(GIO2); 		
//        delay_ms(50); 
//        halLedToggle(1);
//        
//        /*A7139_WriteFIFO(test,DATA_LENGTH);
//        delay_ms(50); 
//        halLedToggle(1);*/
//      }
    //      A7139_StrobeCmd(CMD_RX);
          A7139_SetFreq(472.501f);
          A7139_SetPackLen(64);
          while(1){
            
              //A7139_StrobeCmd(CMD_PLL);
              //delay_us(2);
              A7139_StrobeCmd(CMD_RX);
              delay_us(2);
              while((GIO2==0)); 	
              A7139_ReadFIFO(DataRecv,64);
              //halUartWrite(bufRecv,DATA_LENGTH);             
              //A7139_StrobeCmd(CMD_STBY);
              halLedToggle(1);
            
              /*while((GIO2==1)); 	
              A7139_ReadFIFO(bufRecv,DATA_LENGTH);
              halLedToggle(1);
              delay_ms(10);*/
          }
}