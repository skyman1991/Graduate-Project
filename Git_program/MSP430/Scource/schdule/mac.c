#include "common.h"
EndPointDeviceStruct EndPointDevice;
uint8   DataRecvBuffer[MAX_PACK_LENGTH];
uint8   DataSendBuffer[MAX_PACK_LENGTH];

uint16  CSMA_BackOff_Random = 0;
uint8   CSMA_BackOff_Count = 0;

uint8   Power_Mode = 2;  //1:每个时隙不发送时休眠   2：数据变化时唤醒发送，其他时间休眠
uint8   Data_Change_Flag = 0;//数据发生变化时  该位置一

uint8 Unpack(uint8 *type)
{
    type++;
    return (*type&0xFC)>>2;
}

void CSMABackOff()
{
    uint32 back_off_time = 0;
//    uint32 wait_time = 0;
//    uint32 q,w;
//    //wait_time = ((MAX_DEVICE_NUM - EndPointDevice.free_node)*SLOT_LENGTH)/10;
//    q=MAX_DEVICE_NUM - EndPointDevice.free_node;
//    w=q*SLOT_LENGTH;
//    wait_time=w/100;
//    
//    while(Frame_Time<=wait_time);      //等待到达CSMA时隙 超帧内时间<=负载数*时隙长度
//    
    CSMA_BackOff_Random = (rand()*TAR)%(EndPointDevice.csma_length*BACKOFF_DIV);        //退避时间   随机数*TIMERA计数%csma时隙个数/10
    back_off_time = BACKOFF_PERIOD*CSMA_BackOff_Random;
    delayus(back_off_time);
}

uint8 SendByCSMA(u8 *buff,uint8 length)
{
    uint8 cca_value = 0;
    uint32 wait_time = 0;
    uint32 q,w;
    //wait_time = ((MAX_DEVICE_NUM - EndPointDevice.free_node)*SLOT_LENGTH)/10;
    q=MAX_DEVICE_NUM - EndPointDevice.free_node;
    w=q*SLOT_LENGTH;
    wait_time=w/100;
    
    while(Frame_Time<=wait_time);      //等待到达CSMA时隙 超帧内时间<=负载数*时隙长度
    //TIME1_LOW;
    CSMABackOff();
    //TIME1_HIGH;
    cca_value = (A7139_GetRSSI()+A7139_GetRSSI())/2;
            
    if(cca_value<CCA)
    {
        SendPack();
        RXMode();
    }
    else
    {
        CSMABackOff();
        CSMA_BackOff_Count++;
    }

    if(CSMA_BackOff_Count>CSMA_BACKOFF_TIME)
        return CSMA_FAIL;
    else
        return CSMA_SUCCESS;

}

void BeaconHandler(uint8 beacon[])
{
    EndPointDevice.free_node = beacon[6];
    EndPointDevice.csma_length = (MAX_DEVICE_NUM - EndPointDevice.free_node)/3+1;
    EndPointDevice.power = beacon[1]&0x01;
    if(EndPointDevice.connected == 0)                   //未连接，发送加入请求
    {
        PostTask(EVENT_JOINREQUEST_SEND);
    }
    else                                                //已连接，执行TDMA过程
    {
        //TIME1_HIGH;
        if(EndPointDevice.power == 0)
        {
            A7139_Sleep();
        }
        
        PostTask(EVENT_DATA_SEND);
    }
}

uint8 PackValid(void)
{
    uint16 phy_address = 0;
    phy_address = DataRecvBuffer[2]<<8|DataRecvBuffer[3];
    if((DataRecvBuffer[2]==EndPointDevice.cluster_id&&DataRecvBuffer[3]==EndPointDevice.cluster_innernum)||
       (DataRecvBuffer[2]==BROADCAST&&DataRecvBuffer[3]==BROADCAST)||
       (phy_address==EndPointDevice.pyh_address)||
       (DataRecvBuffer[2]==EndPointDevice.cluster_id && DataRecvBuffer[3]==BROADCAST))
        return 1;
    else
        return 0;
}

