#include "common.h"
DataPacketStruct DataPacket;
void CreatSendData()
{
    uint8 data = 0x54;
    DataPacket.pack_length = DATA_PACK_LENGTH;
    DataPacket.pack_type = DATA_TYPE;
    DataPacket.ack_en = ACK_EN;
    DataPacket.des_cluster_id = EndPointDevice.des_cluster_id;
    DataPacket.des_cluster_innernum = EndPointDevice.des_cluster_innernum;
    DataPacket.src_cluster_id = EndPointDevice.cluster_id;
    DataPacket.src_cluster_innernum = EndPointDevice.cluster_innernum;
    DataPacket.ab_slot_num = Frame_Time;
    DataPacket.data = data;
    
    DataSendBuffer[0] = DataPacket.pack_length;
    DataSendBuffer[1] = DataPacket.pack_type<<2|DataPacket.ack_en<<1;
    DataSendBuffer[2] = DataPacket.des_cluster_id;
    DataSendBuffer[3] = DataPacket.des_cluster_innernum;
    DataSendBuffer[4] = DataPacket.src_cluster_id;
    DataSendBuffer[5] = DataPacket.src_cluster_innernum;
    DataSendBuffer[6] = DataPacket.ab_slot_num>>8;
    DataSendBuffer[7] = DataPacket.ab_slot_num;
    DataSendBuffer[8] = DataPacket.data;;
    DataSendBuffer[9] = 0;
    DataSendBuffer[10] = 0;
    DataSendBuffer[11] = 0;
}
    
void DataSend(void)
{
    uint32 before_slot_wake = WAKE_TIME;               //防止第一个节点为负
    before_slot_wake = (EndPointDevice.cluster_innernum-1)*SLOT_LENGTH-WAKE_TIME+5000;     //在这个时间点唤醒芯片
    while(Frame_Time*100<before_slot_wake);
    A7139_Wake();
    CreatSendData();
    TIME1_HIGH;
    SendPack();
    RXMode();
    TIME1_LOW;
}
void DataACKHandler()
{
    EndPointDevice.time_stamp = DataSendBuffer[6]<<8|DataSendBuffer[7];
    EndPointDevice.data_ack = 1;
    
}