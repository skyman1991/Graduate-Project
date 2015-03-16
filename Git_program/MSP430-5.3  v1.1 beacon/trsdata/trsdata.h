#ifndef _TRSDATA_h_
#define _TRSDATA_h_

#define NODE_NUM 1

#define S_ADDRESS         NODE_NUM
#define D_ADDRESS         0xFF
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
extern uint8 SendOnce;
extern uint32 StateError;
extern uint8  StateErrorTimes;
extern uint8  ResetEnable;
extern uint8 DataRecv[MAX_DATA_LENGTH];
extern uint8 DataSend[MAX_DATA_LENGTH];
extern uint8 BeaconSendFlag;
extern void DataQueue(void);
#endif