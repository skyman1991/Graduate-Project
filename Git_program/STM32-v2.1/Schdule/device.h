#ifndef _DEVICE_h_
#define _DEVICE_h_

#define    ROOT     1
#define    BROADCAST    0xFF
#define    MAX_NODE_NUM  254

#define    ACK_EN     1
#define    ACK_DIS    0

//packet type define
#define    BEACON_TYPE         			1
#define    JOINREQUEST_TYPE    			2
#define    JOINREQUESTACK_TYPE    	3
#define    JOINREQUESTACKOK_TYPE    4

//packet length
#define    SCAN_PACK_LENGTH  7      //扫描阶段发送的包长度
#define    JOINREQUEST_PACK_LENGTH  8  //加入请求包长度
#define    JOINREQUESTACK_PACK_LENGTH  10  //加入请求响应包长度


typedef struct{
    uint8 cluster_id;		        				//簇ID
    uint8 cluster_innernum;							//簇内编号
    uint32 pyh_address;									//物理地址
    uint8 data;													//数据
	
}EndPointDeviceStruct;

typedef struct{
    uint8 cluster_id;		        				//簇ID
    uint8 cluster_innernum;							//簇内编号
    uint8 des_cluster_id;								//目的簇ID
    uint32 pyh_address;									//物理地址
    uint8 device_type;                  //设备类型
    uint8 free_node;                    //当前中继空闲节点数
    uint8 csma_length;                  //CMSA时隙个数
    uint8 state;                        //当前状态
		uint8 connected_devece_count;
		EndPointDeviceStruct endpoint_device[254];
}RootDeviceStruct;

extern uint8 DataSendBuffer[MAX_PACK_LENGTH];
extern uint8 DataRecvBuffer[MAX_PACK_LENGTH];
extern RootDeviceStruct RootDevice;

extern uint8 Unpack(uint8 *type);
#endif 
