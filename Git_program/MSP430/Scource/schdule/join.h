#ifndef _JOIN_h_
#define _JOIN_h_
#include "common.h"
extern const float ChannelList[];

#define    CHANNEL_1     1
#define    CHANNEL_2     2
#define    CHANNEL_3     3
#define    CHANNEL_4     4
#define    CHANNEL_5     5
#define    CHANNEL_6     6
#define    CHANNEL_7     7
#define    CHANNEL_8     8
#define    CHANNEL_9     9
#define    CHANNEL_10    10
#define    CHANNEL_11    11
#define    CHANNEL_12    12
#define    CHANNEL_13    13
#define    CHANNEL_14    14
#define    CHANNEL_15    15
#define    CHANNEL_16    16
#define    CHANNEL_NUM   16



#define    SCAN_TIME_OUT     700  //扫描超时时间  单位ms

typedef struct {
    uint8 channel_num;     // 信道编号
    uint8 channel_rssi;    // 信道信号强度
    uint8 channel_free;   // Sink空闲节点数
    uint8 cluster_id;     // 簇ID
}ChannelTable;

typedef struct{
    uint8  length;                      //包长度
    uint8  des_cluster_id;              //目的簇ID
    uint8  des_cluster_innernum;        //目的簇内编号
    uint16 phy_address;                 //物理地址
    uint8  pack_type:6;                 //包类型
    uint8  ack_en:1;                    //是否需要应答
    uint8  :1;                          //保留
}JoinRequestPacketStruct;

typedef struct{
    uint8  length;                      //包长度
    uint8  pack_type:6;                 //包类型
    uint8  ack_en:1;                    //是否需要应答
    uint8  :1;                          //保留
    uint8  src_cluster_id;              //源簇ID
    uint8  src_cluster_innernum;        //源簇内编号
    uint8  des_cluster_id;              //目的簇ID
    uint8  des_cluster_innernum;        //目的簇内编号

}JoinRequestACKOKPacketStruct;

extern uint8 StartChannel;
extern uint8 EndChannel;

extern ChannelTable SortedChannel[CHANNEL_NUM];
extern ChannelTable ScanChannel[CHANNEL_NUM];

extern uint8 Scan_Channel(uint8 startch,uint8 endch);
extern void SortChannel();
extern void CreatJoinRequest();
extern void JoinRequestACKHandler();
extern void SendJoinRequest();
extern void ReJoinHandler();
extern uint8 ReJoinFlag;
#endif