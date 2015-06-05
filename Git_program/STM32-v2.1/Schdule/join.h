#ifndef _SCAN_h_
#define _SCAN_h_
#include "common.h"

typedef struct{
		uint8  length;											//包长度
		uint8  pack_type:6;									//包类型
		uint8  ack_en:1;                    //是否需要应答
    uint8  accept:1;                		//是否接受入网    
		uint16 des_phy_address;             //目的地址
		uint8  src_cluster_id;              //源簇ID
    uint8  src_cluster_innernum;        //源簇内编号
		uint8  cluster_id;              		//分配簇ID
    uint8  cluster_innernum;       		  //分配簇内编号
}JoinRequestACKPacketStruct;

typedef struct{
    uint8  length;                      //包长度
		uint8  pack_type:6;                 //包类型
    uint8  ack_en:1;                    //是否需要应答
    uint8  :1;                          //保留
    uint8  des_cluster_id;              //目的簇ID
    uint8  des_cluster_innernum;        //目的簇内编号
		uint8  src_cluster_id;							//源簇ID
		uint8  src_cluster_innernum; 				//源簇内编号
    uint16 des_phy_address;                 //目的物理地址
}ReJoinPacketStruct;

extern void JoinRequestHandler(void);
extern void JoinRequestACKOKHandler(void);
extern void SendReJoin(void);

#endif
