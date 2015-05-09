#include "common.h"
EndPointDeviceStruct EndPointDevice;
uint8   DataRecvBuffer[MAX_PACK_LENGTH];
uint8   DataSendBuffer[MAX_PACK_LENGTH];

uint16  CSMA_BackOff_Random = 0;
uint8   CSMA_BackOff_Count = 0;
uint8 Unpack(uint8 *type)
{
    type++;
    return (*type&0xFC)>>2;
}
void CSMABackOff()
{
    uint16 back_off_time = 0;
    
    while(Frame_Time*10<=(MAX_DEVICE_NUM - EndPointDevice.free_node)*SLOT_LENGTH);      //等待到达CSMA时隙 超帧内时间<=负载数*时隙长度
    CSMA_BackOff_Random = (rand()*TAR)%(EndPointDevice.csma_length*BACKOFF_DIV);        //退避时间   随机数*TIMERA计数%csma时隙个数/5 
    back_off_time = BACKOFF_PERIOD*CSMA_BackOff_Random;
    delayus(back_off_time);
}
    uint8 cca_value = 0;
uint8 SendByCSMA(u8 *buff,uint8 length)
{

    CSMABackOff();
    
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
    
    if(EndPointDevice.connected == 0)
    {
        CreatJoinRequest();
        SendByCSMA(DataSendBuffer,JOINREQUEST_PACK_LENGTH);
    }
}
