#include "common.h"
JoinRequestACKPacketStruct JoinRequestACKPacket;
uint32 new_node_pyh_address = 0;
void CreateJoinRequectACK(uint8 joinstatus,uint8 accept,uint8 id,uint32 des_address)
{
		JoinRequestACKPacket.length = JOINREQUESTACK_PACK_LENGTH;
		JoinRequestACKPacket.pack_type = JOINREQUESTACK_TYPE;
	  JoinRequestACKPacket.ack_en = ACK_EN;
	  if((accept==1)&&(joinstatus==0))									//接收入网，新加入节点
		{
				JoinRequestACKPacket.accept = 1;
				JoinRequestACKPacket.cluster_id = ROOT;
				JoinRequestACKPacket.cluster_innernum = id;
		}
		else if((accept==1)&&(joinstatus==1))							//接收入网，已加入节点
		{
				JoinRequestACKPacket.accept = 1;
				JoinRequestACKPacket.cluster_id = ROOT;
				JoinRequestACKPacket.cluster_innernum = id;
				JoinRequestACKPacket.ack_en = ACK_DIS;
		}
		else
		{
				JoinRequestACKPacket.accept = 0;
				JoinRequestACKPacket.cluster_id = ROOT;
				JoinRequestACKPacket.cluster_innernum = 0;
		}
		JoinRequestACKPacket.src_cluster_id = RootDevice.cluster_id;
		JoinRequestACKPacket.src_cluster_innernum = 0;
		JoinRequestACKPacket.des_phy_address = des_address;
		
		DataSendBuffer[0] = JoinRequestACKPacket.length;
		DataSendBuffer[1] = JoinRequestACKPacket.pack_type<<2|JoinRequestACKPacket.ack_en<<1|JoinRequestACKPacket.accept;
		DataSendBuffer[2] = JoinRequestACKPacket.src_cluster_id;
		DataSendBuffer[3] = JoinRequestACKPacket.src_cluster_innernum;
		DataSendBuffer[4] = JoinRequestACKPacket.des_phy_address>>24;
		DataSendBuffer[5] = JoinRequestACKPacket.des_phy_address>>16;
		DataSendBuffer[6] = JoinRequestACKPacket.des_phy_address>>8;
		DataSendBuffer[7] = JoinRequestACKPacket.des_phy_address;
		DataSendBuffer[8] = JoinRequestACKPacket.cluster_id;
		DataSendBuffer[9] = JoinRequestACKPacket.cluster_innernum;
}

void JoinRequestHandler()
{
		
	  uint8 i=0;
		uint8 joinstatus = 0;
	  uint8 accept = 0;
		uint8 current_node_num = RootDevice.connected_devece_count;
		new_node_pyh_address = DataRecvBuffer[2]<<24|DataRecvBuffer[3]<<16|DataRecvBuffer[4]<<8|DataRecvBuffer[5];
	  for(i=0;i<RootDevice.connected_devece_count;i++)
		{
				if(RootDevice.endpoint_device[i].pyh_address == new_node_pyh_address)	//该设备已经入网
				{
						joinstatus = 1;
						accept = 1;
						CreateJoinRequectACK(joinstatus,accept,i+1,new_node_pyh_address);
						SendPack();
						RXMode();
						return ;
				}
		}
		if(RootDevice.connected_devece_count<=MAX_NODE_NUM)		//还有资源，可以加入
		{
				accept = 1;
			  current_node_num++;
				CreateJoinRequectACK(joinstatus,accept,current_node_num,new_node_pyh_address);
				SendPack();
				RXMode();
		}
}
void JoinRequestACKOKHandler()
{
		RootDevice.endpoint_device[RootDevice.connected_devece_count].cluster_id = DataRecvBuffer[2];
		RootDevice.endpoint_device[RootDevice.connected_devece_count].cluster_innernum = DataRecvBuffer[3];
	  RootDevice.endpoint_device[RootDevice.connected_devece_count].pyh_address = new_node_pyh_address;
		RootDevice.connected_devece_count++;
		RootDevice.free_node = MAX_NODE_NUM-RootDevice.connected_devece_count;
}

