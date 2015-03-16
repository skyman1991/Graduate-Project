#include "common.h"

int    send_flag = 0;
uint8  DataRecv[MAX_DATA_LENGTH];
uint8  DataSend[MAX_DATA_LENGTH];
uint16 TDMA_time = 0;
uint8  SendOnce = 0;
uint32 StateError = 0;
uint8  StateErrorTimes = 0;
uint8  ResetEnable = 0;

int node2 = 0;
int node3 = 0;
#pragma vector=PORT1_VECTOR
__interrupt void port1_ISR(void)
{
  
  if(P1IFG & pinGIO2.pin_bm)
  {
        /*************************/
        //halLedClear(1);
        ResetEnable = 1;
        P1IFG &= ~pinGIO2.pin_bm;                           // P1.4 IFG cleared
        A7139_ReadFIFO(DataRecv,MAX_DATA_LENGTH);
        delay_us(2);
        A7139_StrobeCmd(CMD_RX);
        delay_us(2);
        if((DataRecv[1] == SINK_ADDRESS)&&(DataRecv[0] == CMD_BEACON))
        {
          EN_TIMER;
          DIS_EXITINT;
          TDMA_time = 0;
          halLedSet(1);
    #if(SLEEP_ENABLE)
          if(S_ADDRESS != 2)
          {
            A7139_StrobeCmd(CMD_SLEEP);
            delay_us(1);
          }
    #endif
        } 
  
    //halLedToggle(1);
    /********2.4ms*************/   
  }
  
}
int once = 0;
void DataQueue(void)
{
  DataSend[0] = PAK_TYPE;
  DataSend[1] = S_ADDRESS;    //Ô´
  DataSend[2] = D_ADDRESS;    //Ä¿µÄ
  //DataSend[3] = BeaconTimeCount>>8;
  //DataSend[4] = BeaconTimeCount;
  //DataSend[5] = once++;
  DataSend[6] = 0xAA;
  DataSend[3] = StateErrorTimes;
  if(NODE_NUM ==2)
  {
    DataSend[7] = once>>8;
    DataSend[8] = once;
  }
  else if(NODE_NUM == 3)
  {
    DataSend[9] = once>>8;
    DataSend[10] = once;
  }
  else if(NODE_NUM == 4)
  {
    DataSend[11] = once>>8;
    DataSend[12] = once;
  }
  once++;
}
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer_A (void)
{
  TA1CCTL0 &= ~CCIFG;
  //halLedToggle(1);
  if(TDMA_time == (NODE_NUM-2)*TDMA_GAP_K+TDMA_GAP_D)
  //if(TDMA_time == 150)
  {
    send_flag = 1;
    DataRecv[1] = 0;
    DataRecv[2] = 0;
    DIS_TIMER;
  }
#if(SLEEP_ENABLE)
  if(TDMA_time == (NODE_NUM-2)*TDMA_GAP_K-30+TDMA_GAP_D)
  {
      A7139_StrobeCmd(CMD_STBY);
      delay_us(1);
  }
#endif
  TDMA_time++;
}