#ifndef _DEVICE_h_
#define _DEVICE_h_
/****************����beacon������Ҫ���µ��Ĳ���*************/
#define    BEACON_PERIOD     5000
#define    BEFOR_BEACON_WAKE BEACON_PERIOD-150   //��beaconǰ1.5msʱ����оƬ

/**********************************************************/
#define    SLOT_LENGTH     20000     //��λus
#define    BACKOFF_DIV     10
#define    BACKOFF_PERIOD  SLOT_LENGTH/BACKOFF_DIV
#define    WAKE_TIME         4000    //SLEEP������Ҫ2ms

#define    DATAACK_TIMEOUT 300      //ack���ճ�ʱ�������Ƿ����csma�ط��׶�

#define    SLEEP_EN        1

#define    CCA   90     //�ز������ֵ
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
    uint8 cluster_id;		        //��ID
    uint8 cluster_innernum;		//���ڱ��
    uint8 des_cluster_id;		//Ŀ�Ĵ�ID
    uint8 des_cluster_innernum;		//Ŀ�Ĵر��
    uint8 channel;			//��ǰ�ŵ�
    uint8 backup_channel;		//�����ŵ�
    uint16 pyh_address;			//������ַ
    uint8 device_type;                  //�豸����
    uint8 free_node;                    //��ǰ�м̿��нڵ���
    uint8 connected;                    //����״̬
    uint8 csma_length;                  //CMSAʱ϶����
    uint8 state;                        //��ǰ״̬
    uint8 time_stamp;                   //ʱ���
    uint8 data_ack;                     //����ack
    uint8 power;			//�Ƿ����͹���
}EndPointDeviceStruct;

extern EndPointDeviceStruct EndPointDevice;
extern uint8 Unpack(uint8 *type);
extern void BeaconHandler(uint8 beacon[]);
extern uint8 PackValid(void);
extern uint8 SendByCSMA(u8 *buff,uint8 length);



extern uint8 DataRecvBuffer[MAX_PACK_LENGTH];
extern uint8 DataSendBuffer[MAX_PACK_LENGTH];
extern uint8 Power_Mode;


#endif