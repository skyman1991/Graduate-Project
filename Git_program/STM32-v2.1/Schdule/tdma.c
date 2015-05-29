#include "common.h"
DataACKPacketStruct DataACKPacket;
void CreateDataACK(uint8 src_cluster_id,uint8 src_cluster_innernum)
{
		DataACKPacket.pack_length = DATAACK_PACK_LENGTH;
	  DataACKPacket.pack_type = DATAACK_TYPE;
	  DataACKPacket.ack_en = ACK_DIS;
	  DataACKPacket.des_cluster_id = src_cluster_id;
	  DataACKPacket.des_cluster_innernum = src_cluster_innernum;
	  DataACKPacket.src_cluster_id = RootDevice.cluster_id;
	  DataACKPacket.src_cluster_innernum = RootDevice.cluster_innernum;
	  DataACKPacket.time_stamp = Frame_Time;
	
		DataSendBuffer[0] = DataACKPacket.pack_length;
		DataSendBuffer[1] = DataACKPacket.pack_type<<2|DataACKPacket.ack_en<<1;
		DataSendBuffer[2] = DataACKPacket.des_cluster_id;
		DataSendBuffer[3] = DataACKPacket.des_cluster_innernum;
		DataSendBuffer[4] = DataACKPacket.src_cluster_id;
		DataSendBuffer[5] = DataACKPacket.src_cluster_innernum;
		DataSendBuffer[6] = DataACKPacket.time_stamp>>8;
		DataSendBuffer[7] = DataACKPacket.time_stamp;
		DataSendBuffer[8] = 0;
		DataSendBuffer[9] = 0;
		DataSendBuffer[10] = 0;
		DataSendBuffer[11] = 0;
}
void DataHandler(void)
{
		uint8 inner_num = 0;
		uint8 ab_slot_num = 0;
		uint8 src_cluster_id = 0;
	  uint8 src_cluster_innernum = 0;
	  src_cluster_id = DataRecvBuffer[4];
	  src_cluster_innernum = DataRecvBuffer[5];
	  ab_slot_num = DataRecvBuffer[6]<<8|DataRecvBuffer[7];
		inner_num = DataRecvBuffer[5];
		//if(ab_slot_num>=RootDevice.endpoint_device[inner_num].ab_slot_num)
		{
				RootDevice.endpoint_device[inner_num].ab_slot_num = ab_slot_num;
				RootDevice.endpoint_device[inner_num].data = DataRecvBuffer[8];
				CreateDataACK(src_cluster_id,src_cluster_innernum);
				
				SendPack();
				RXMode();

		}
}
