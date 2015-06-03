#include "common.h"
uint8 DataSendBuffer[MAX_PACK_LENGTH];
uint8 DataRecvBuffer[MAX_PACK_LENGTH];
RootDeviceStruct RootDevice;
uint16 Frame_Time = 0;
uint8 Power_Mode = 1;
uint8 Unpack(uint8 *type)
{
    type++;
    return (*type&0xFC)>>2;
}
uint8 PackValid(void)
{
		if((DataRecvBuffer[2]==RootDevice.cluster_id&&
				DataRecvBuffer[3]==RootDevice.cluster_innernum)||
		   (DataRecvBuffer[2]==BROADCAST&&
		    DataRecvBuffer[3]==BROADCAST))
				return 1;
		else
				return 0;
}
