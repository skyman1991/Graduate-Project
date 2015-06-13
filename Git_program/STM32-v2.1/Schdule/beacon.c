#include "common.h"

BeaconPacketStruct BeaconPacket;
uint8 BeaconPacketFIFO[BEACON_PACK_LENGTH];

uint8 CreatBeacon()
{
		BeaconPacket.length = BEACON_PACK_LENGTH;				//beacon包成长度为5bytes
		BeaconPacket.cluster_id = ROOT;							//sink节点编号
		BeaconPacket.cluster_innernum = 0;							//簇内ID sink节点为0
		BeaconPacket.des_cluster_id = BROADCAST;						//广播包
	  BeaconPacket.des_cluster_innernum = BROADCAST;						//广播包
		BeaconPacket.pack_type = BEACON_TYPE;						//包类型是beacon
		BeaconPacket.ack_en = ACK_EN;									//不需要应答
		BeaconPacket.free_num = RootDevice.free_node;	//空闲节点数量
		//BeaconPacket.power = LOW_POWER;
		BeaconPacket.power = Power_Mode;
	
		DataSendBuffer[0] = BeaconPacket.length ;
    DataSendBuffer[1] = BeaconPacket.pack_type<<2|BeaconPacket.ack_en<<1|BeaconPacket.power;
    DataSendBuffer[2] = BeaconPacket.des_cluster_id;
    DataSendBuffer[3] = BeaconPacket.des_cluster_innernum;
    DataSendBuffer[4] = BeaconPacket.cluster_id;
    DataSendBuffer[5] = BeaconPacket.cluster_innernum;
    DataSendBuffer[6] = BeaconPacket.free_num;
		
		return 1;
}
uint8 PostBeacon(void)
{
		CreatBeacon();
		return PostTask(EVENT_BEACON_SEND);
}

void SendBeacon(void)
{
		TIME2_HIGH;
	  SendPack();
		LED1_REV();
		RXMode();
		TIME2_LOW;

}
