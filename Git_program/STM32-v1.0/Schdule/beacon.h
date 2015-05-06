#ifndef _BEACON_h_
#define _BEACON_h_

#define    BEACON_PACK_LENGTH    7
#define    BECAON_PERIOD 500     //单位：ms

typedef struct {
    uint8 length;     					// 包长度
		uint8 pack_type:6;					//包类型
		uint8 ack_en:1;							//是否需要应答
		uint8 :1;										//保留
		uint8 cluster_id;				  	//簇ID
		uint8 cluster_innernum;	  	//簇内编号
		uint8 des_cluster_id;				//目的簇ID
	  uint8 des_cluster_innernum;	//目的簇内编号
	  uint8 free_num:8;						//空闲负载数
}BeaconPacketStruct;

extern uint8 PostBeacon(void);
extern void SendBeacon(void);
extern uint8 CreatBeacon(void);

#endif
