#ifndef _DEVICE_h_
#define _DEVICE_h_

#define    SLOT_LENGTH     20000     //单位us
#define    BACKOFF_DIV     10
#define    BACKOFF_PERIOD  SLOT_LENGTH/BACKOFF_DIV
#define    WAKE_TIME       2000

#define    CCA   90     //载波监测阈值
#define    CSMA_BACKOFF_TIME 8
#define    CSMA_FAIL    1
#define    CSMA_SUCCESS 0

#define    BROADCAST    0xFF
#define    ROOT     1
#define    DEVICE   2

#define    ACK_EN    1
#define    ACK_DIS   0

//packet type define
#define    BEACON_TYPE              1
#define    JOINREQUEST_TYPE         2
#define    JOINREQUESTACK_TYPE      3
#define    JOINREQUESTACKOK_TYPE    4
#define    DATA_TYPE                5
#define    DATAACK_TYPE             6


//packet length
#define    BEACON_PACK_LENGTH            7
#define    JOINREQUEST_PACK_LENGTH       6  
#define    JOINREQUESTACK_PACK_LENGTH    8  
#define    JOINREQUESTACKOK_PACK_LENGTH  6  
#define    DATA_PACK_LENGTH              9  
#define    DATAACK_PACK_LENGTH           8

typedef struct{
    uint8 cluster_id;		        //簇ID
    uint8 cluster_innernum;		//簇内编号
    uint8 des_cluster_id;		//目的簇ID
    uint8 des_cluster_innernum;		//目的簇编号
    uint8 channel;			//当前信道
    uint8 backup_channel;		//备用信道
    uint16 pyh_address;			//物理地址
    uint8 device_type;                  //设备类型
    uint8 free_node;                    //当前中继空闲节点数
    uint8 connected;                    //入网状态
    uint8 csma_length;                  //CMSA时隙个数
    uint8 state;                        //当前状态
    uint8 time_stamp;                   //时间戳
    uint8 data_ack;                     //数据ack
}EndPointDeviceStruct;

extern EndPointDeviceStruct EndPointDevice;
extern uint8 Unpack(uint8 *type);
extern void BeaconHandler(uint8 beacon[]);
extern uint8 PackValid(void);
extern uint8 SendByCSMA(u8 *buff,uint8 length);


extern uint8 DataRecvBuffer[MAX_PACK_LENGTH];
extern uint8 DataSendBuffer[MAX_PACK_LENGTH];

#endif