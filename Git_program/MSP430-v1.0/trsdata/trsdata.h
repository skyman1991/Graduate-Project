#ifndef _TRSDATA_h_
#define _TRSDATA_h_

#define NODE_NUM  5       //节点从2开始  1为源节点
#define BECAON_PERIOD 200

#define SLEEP_ENABLE 0    //睡眠模式只在BECAON_PERIOD为500的时候测试过
#if(CONFIG_DATA_RATE == 250)
#define FIRST_BEACON_ACK_TIME  40   //第一个回复时间
#define BEACON_ACK_PERIOD      17
#define TDMA_GAP_K             120
#define TDMA_GAP_D             5
//最小间隔  10ms

#endif



#define S_ADDRESS         NODE_NUM
#define D_ADDRESS         0x01
#define SINK_ADDRESS      0x01
#define PAK_TYPE          CMD_BEACON_ACK
#define CMD_BEACON        0x01
#define CMD_BEACON_ACK    0x02
#define BROADCASE         0XFF

#define   EN_EXITINT   P1IE |= pinGIO2.pin_bm
#define   DIS_EXITINT  P1IE &= ~pinGIO2.pin_bm
#define   EN_TIMER    TA1CCTL0 = CCIE
#define   DIS_TIMER   TA1CCTL0 &= ~CCIE
extern int send_flag;
extern uint8  SendOnce;
extern uint16  TDMA_time;
extern Uint16 AD_curvalue;
extern uint32 StateError;
extern Uint16 AD_avevalue;
extern uint8  StateErrorTimes;
extern uint8  ResetEnable;
extern uint8  AD_flag;
extern uint8 DataRecv[MAX_DATA_LENGTH];
extern uint8 DataSend[MAX_DATA_LENGTH];
extern void Sensor_status_Value(void);
extern void DataQueue(void);
#endif