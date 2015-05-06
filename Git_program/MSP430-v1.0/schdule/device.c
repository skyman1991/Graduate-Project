#include "common.h"
EndPointDeviceStruct EndPointDevice;
uint8   DataRecv[MAX_PACK_LENGTH];
uint8   DataSend[MAX_PACK_LENGTH];

uint8 Unpack(uint8 *type)
{
    type++;
    return (*type&0xFC)>>2;
}
void BeaconHandler(uint8 beacon[])
{
    EndPointDevice.free_node = beacon[6];
}
