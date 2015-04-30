#include "common.h"

//int    send_flag = 0;
//uint8  DataRecv[MAX_DATA_LENGTH];
//uint8  DataSend[MAX_DATA_LENGTH];
//uint16 TDMA_time = 0;
//uint8  SendOnce = 0;
//uint32 StateError = 0;
//uint8  StateErrorTimes = 0;
//uint8  ResetEnable = 0;
////uint16 s=0;

//int node2 = 0;
//int node3 = 0;
//#pragma vector=PORT1_VECTOR
//__interrupt void port1_ISR(void)
//{
//  
//  if(P1IFG & pinGIO2.pin_bm)
//  {
//        /*************************/
//        //halLedClear(1);
//        ResetEnable = 1;
//        P1IFG &= ~pinGIO2.pin_bm;                           // P1.4 IFG cleared
//        A7139_ReadFIFO(DataRecv,MAX_DATA_LENGTH);
//        delay_us(2);
//        A7139_StrobeCmd(CMD_RX);
//        delay_us(2);
//        if((DataRecv[1] == SINK_ADDRESS)&&(DataRecv[0] == CMD_BEACON))
//        {
//          EN_TIMER;
//          DIS_EXITINT;
//          TDMA_time = 0;
//          //send_flag = 1;
//          //halLedSet(1);
//          DataRecv[1] = 0;
//          DataRecv[2] = 0;
//        } 
//  
//    //halLedToggle(1);
//    /********2.4ms*************/   
//  }
//  
//}
//
//void Sensor_status_Value(void)
//{
//
//
//    AD_actvalue=SampleChannel(0x02);
//    if(ad_cal_value-AD_actvalue>50)
//    {
//        halLedSet(1);//NKJFK-GPHP7-G8C3J-P6JXR-HQRJR
//        AD_flag = 1;
//        AD_avevalue=1;
//    }
//    else if(AD_actvalue-ad_cal_value>50)
//    {
//        halLedSet(1);//NKJFK-GPHP7-G8C3J-P6JXR-HQRJR
//        AD_flag = 1;
//        AD_avevalue=1;
//    }
//    else
//    {
//        halLedClear(1);
//        AD_avevalue=0;
//    }
//        
////    AD_delatvalue=AD_actvalue-AD_curvalue;
////      if(AD_delatvalue<0)
////      {
////        AD_delatvalue=-AD_delatvalue;
////      }
////      if(AD_delatvalue>300)
////      {
////          halLedSet(1);//NKJFK-GPHP7-G8C3J-P6JXR-HQRJR
////          AD_flag = 1;
////          AD_avevalue=1;
////          
////          //count++;
////      }
////      else
////      {
////        halLedClear(1);
////        AD_avevalue=0;
////        //AD_flag = 0; 
////      }  
//}
//int once = 0;
//void DataQueue(void)
//{
//  DataSend[0] = PAK_TYPE;
//  DataSend[1] = S_ADDRESS;    //Ô´
//  DataSend[2] = D_ADDRESS;    //Ä¿µÄ
//  //DataSend[3] = BeaconTimeCount>>8;
//  //DataSend[4] = BeaconTimeCount;
//  //DataSend[5] = once++;
//  DataSend[6] = 0xAA;
//  DataSend[3] = StateErrorTimes;
//    if(NODE_NUM ==2)
//  {
//    DataSend[7] = AD_avevalue>>8;   
//    DataSend[8] = AD_avevalue;
//  }
//    else if(NODE_NUM == 3)
//  {
//      DataSend[9] = AD_avevalue>>8;
//      DataSend[10] = AD_avevalue;
//  }
//    else if(NODE_NUM == 4)
//  {
//    DataSend[11] = AD_avevalue>>8;
//    DataSend[12] = AD_avevalue;
//  }
//  else if(NODE_NUM == 5)
//  {
//    DataSend[13] = AD_avevalue>>8;
//    DataSend[14] = AD_avevalue;
//  }
//  else if(NODE_NUM == 6)
//  {
//    DataSend[15] = AD_avevalue>>8;
//    DataSend[16] = AD_avevalue;
//  }
//  else if(NODE_NUM == 7)
//  {
//    DataSend[17] = AD_avevalue>>8;
//    DataSend[18] = AD_avevalue;
//  }
//    
//  once++;
//}
//#pragma vector=TIMER1_A0_VECTOR
//__interrupt void Timer_A (void)
//{
//  TA1CCTL0 &= ~CCIFG;
//  //halLedToggle(1);
//  if(TDMA_time == (NODE_NUM-2)*TDMA_GAP_K+TDMA_GAP_D)
//  //if(TDMA_time == 150)
//  {
//    send_flag = 1;
//    DataRecv[1] = 0;
//    DataRecv[2] = 0;
//    DIS_TIMER;
//  }
//  TDMA_time++;
//}