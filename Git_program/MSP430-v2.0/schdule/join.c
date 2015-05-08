#include "common.h"
const float CODE ChannelList[]={0,470.001f,472.501f,475.001f,477.501f,480.001f,482.501f,485.001f,487.501f,
                           490.001f,492.501f,495.001f,497.501f,500.001f,502.501f,505.001f,507.501f};
uint8 StartChannel = CHANNEL_1;
uint8 EndChannel = CHANNEL_2;
ChannelTable ScanChannel[CHANNEL_NUM];
JoinRequestPacketStruct JoinRequestPacket;


uint8 Scan_Channel(uint8 startch,uint8 endch)
{
    uint8 i;
    uint8 datalength = 0;  
    int16 timeout = SCAN_TIME_OUT;
    uint8 data[MAX_PACK_LENGTH];
       
    if(endch > CHANNEL_NUM)
    {
        return 0;
    }
    for(i=startch;i<endch+1;i++)   //循环16次
    {
        A7139_SetFreq(ChannelList[i]);
        //A7139_SetFreq(470.001f);
        delay_us(1);
        A7139_Cal();                    //更改完频率后校准
        delay_us(1);
        RXMode();
        while(GIO1)
        {
            delay_1ms();
            if(timeout--==0)
                break;
        }
        if(timeout>0)
        {
            A7139_ReadFIFO(&datalength,1);
            A7139_ReadFIFO(data,MAX_PACK_LENGTH);
            ScanChannel[i-1].channel_num = i;
            ScanChannel[i-1].channel_rssi = A7139_GetRSSI();
            ScanChannel[i-1].channel_free = data[6];
            ScanChannel[i-1].cluster_id = data[1];
        }
        else
        {
            ScanChannel[i-1].channel_num = 0;
            ScanChannel[i-1].channel_rssi = 0;
            ScanChannel[i-1].channel_free = 0;
            ScanChannel[i-1].cluster_id = 0;
        }
        timeout = SCAN_TIME_OUT; 
    }
        
    return i;
}

void bubble(ChannelTable *a,uint8 n) 
{ 
    uint8 i,j;
    ChannelTable temp; 
    for(i=0;i<n-1;i++) 
    {
        if(a[i].channel_free>MAX_DEVICE_NUM)
            continue;
        else
        {
            for(j=i+1;j<n;j++) 
                if(a[i].channel_rssi<a[j].channel_rssi) 
                { 
                    temp=a[i];
                    a[i]=a[j]; 
                    a[j]=temp; 
                }
        }
    }
    
} 
void SortChannel()
{
    bubble(ScanChannel,CHANNEL_NUM);
    EndPointDevice.channel = ScanChannel[0].channel_num;
    EndPointDevice.backup_channel = ScanChannel[1].channel_num;
    EndPointDevice.cluster_id = ScanChannel[0].cluster_id;
    EndPointDevice.des_cluster_id = ScanChannel[0].cluster_id;
    A7139_SetFreq(ChannelList[EndPointDevice.channel]);
    delay_us(1);
    A7139_Cal();                    
    delay_us(1);
}
void CreatJoinRequest()
{
    JoinRequestPacket.length = JOINREQUEST_PACK_LENGTH;
    JoinRequestPacket.des_cluster_id = EndPointDevice.des_cluster_id;
    JoinRequestPacket.des_cluster_innernum = 0;
    JoinRequestPacket.phy_address = EndPointDevice.pyh_address;
    JoinRequestPacket.pack_type = JOINREQUEST_TYPE;
    JoinRequestPacket.ack_en = ACK_EN;
    
    DataSendBuffer[0] = JoinRequestPacket.length;
    DataSendBuffer[1] = JoinRequestPacket.phy_address>>24;
    DataSendBuffer[2] = JoinRequestPacket.phy_address>>16;
    DataSendBuffer[3] = JoinRequestPacket.phy_address>>8;
    DataSendBuffer[4] = JoinRequestPacket.phy_address;
    DataSendBuffer[5] = JoinRequestPacket.des_cluster_id;
    DataSendBuffer[6] = JoinRequestPacket.des_cluster_innernum;
    DataSendBuffer[7] = JoinRequestPacket.pack_type | JoinRequestPacket.ack_en;
}
void SendJoinRequest()
{
    CreatJoinRequest();  
    SendPack(DataSendBuffer,JOINREQUEST_PACK_LENGTH);
}
