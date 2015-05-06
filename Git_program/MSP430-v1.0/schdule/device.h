#ifndef _DEVICE_h_
#define _DEVICE_h_

#define ROOT     1
#define DEVICE   2

#define    ACK_EN    1
#define    ACK_DIS   0

//packet type define
#define    BEACON_TYPE         1
#define    JOINREQUEST_TYPE    2

//event handler define
#define    BEACON_HANDLER         1
#define    JOINREQUEST_HANDLER    2

typedef struct{
    uint8 cluster_id;		        //簇ID
    uint8 cluster_innernum;		//簇内编号
    uint8 des_cluster_id;		//目的簇ID
    uint8 channel;			//当前信道
    uint8 backup_channel;		//备用信道
    uint8 pyh_address;			//物理地址
    uint8 device_type;                  //设备类型
    uint8 free_node;                    //当前中继空闲节点数
}EndPointDeviceStruct;

extern EndPointDeviceStruct EndPointDevice;
extern uint8 Unpack(uint8 *type);
extern void BeaconHandler(uint8 beacon[]);


extern uint8 DataRecv[MAX_PACK_LENGTH];
extern uint8 DataSend[MAX_PACK_LENGTH];

#endif