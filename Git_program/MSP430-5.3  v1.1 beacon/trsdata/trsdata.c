#include "common.h"

int    send_flag = 0;
uint8  DataRecv[MAX_DATA_LENGTH];
uint8  DataSend[MAX_DATA_LENGTH];
uint16 TDMA_time = 0;
uint8  SendOnce = 0;
uint32 StateError = 0;
uint8  StateErrorTimes = 0;
uint8  ResetEnable = 0;
uint8 BeaconSendFlag = 0;
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
    /*if((DataRecv[1] == SINK_ADDRESS)&&(DataRecv[0] == CMD_BEACON))
    {
      EN_TIMER;
      DIS_EXITINT;
      TDMA_time = 0;
      halLedSet(1);
    }*/   
    //halLedToggle(1);
    /********2.4ms*************/

  }
  
  
  
//  if(P1IFG & pinGIO2.pin_bm)
//  {
//    P1IFG &= ~pinGIO2.pin_bm;  
//        A7139_ReadFIFO(DataRecv,MAX_DATA_LENGTH);
//    delay_us(2);
//    A7139_StrobeCmd(CMD_RX);
//    delay_us(2);
//    if((DataRecv[1] == 3))
//    {
//        node3++;
//    }
//    else  if((DataRecv[1] == 2))
//    {
//        node2++;
//    }
//  }
}
int once = 0;
void DataQueue(void)
{
  int i = 0;
  for(i=0;i<64;i++)
    DataSend[i]=i;
  DataSend[0] = CMD_BEACON;
  DataSend[1] = S_ADDRESS;
  DataSend[2] = D_ADDRESS;
  //DataSend[3] = BeaconTimeCount>>8;
  //DataSend[4] = BeaconTimeCount;
  DataSend[5] = 64;
  DataSend[6] = 0xAA;
}
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer_A (void)
{
  TA1CCTL0 &= ~CCIFG;
  halLedToggle(1);
  
  BeaconSendFlag = 1;
}