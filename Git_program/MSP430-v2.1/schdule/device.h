#ifndef _DEVICE_h_
#define _DEVICE_h_

#define    SLOT_LENGTH     5000     //单位us
#define    BACKOFF_DIV     5
#define    BACKOFF_PERIOD  SLOT_LENGTH/BACKOFF_DIV
#define    CCA   90     //载波监测阈值
#define    CSMA_BACKOFF_TIME 8
#define    CSMA_FAIL    1
#define    CSMA_SUCCESS 0

#define ROOT     1
#define DEVICE   2

#define    ACK_EN    1
#define    ACK_DIS   0

//packet type define
#define    BEACON_TYPE         1
#define    JOINREQUEST_TYPE    2
#define    JOINREQUESTACK_TYPE    3
#define    JOINREQUESTACKOK_TYPE    4

//packet length
#define    SCAN_PACK_LENGTH  7      //扫描阶段发送的包长度
#define    JOINREQUEST_PACK_LENGTH  8  //加入请求包长度
#define    JOINREQUESTACKOK_PACK_LENGTH  6  //加入请求包长度

typedef struct{
    uint8 cluster_id;		        //簇ID
    uint8 cluster_innernum;		//簇内编号
    uint8 des_cluster_id;		//目的簇ID
    uint8 channel;			//当前信道
    uint8 backup_channel;		//备用信道
    uint32 pyh_address;			//物理地址
    uint8 device_type;                  //设备类型
    uint8 free_node;                    //当前中继空闲节点数
    uint8 connected;                    //入网状态
    uint8 csma_length;                  //CMSA时隙个数
    uint8 state;                        //当前状态
}EndPointDeviceStruct;

extern EndPointDeviceStruct EndPointDevice;
extern uint8 Unpack(uint8 *type);
extern void BeaconHandler(uint8 beacon[]);


extern uint8 DataRecvBuffer[MAX_PACK_LENGTH];
extern uint8 DataSendBuffer[MAX_PACK_LENGTH];

#endif