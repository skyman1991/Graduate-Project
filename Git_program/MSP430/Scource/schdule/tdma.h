#ifndef _TDMA_h_
#define _TDMA_h_
#include "common.h"

typedef struct{
    uint8  pack_length;                  //包长度
    uint8  pack_type:6;                 //包类型
    uint8  ack_en:1;                    //是否需要应答
    uint8  :1;                          //保留
    uint8  des_cluster_id;              //目的簇ID
    uint8  des_cluster_innernum;        //目的簇内编号
    uint8  src_cluster_id;              //源簇ID
    uint8  src_cluster_innernum;        //源簇内编号
    uint16 ab_slot_num;                 //绝对时隙号
    uint8  data;                        //数据
}DataPacketStruct;

extern DataPacketStruct DataPacket;

extern void DataSend(void);
extern void DataACKHandler();
extern void CSMADataResend();
#endif