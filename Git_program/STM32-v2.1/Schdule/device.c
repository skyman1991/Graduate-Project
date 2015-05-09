#include "common.h"
uint8 DataSendBuffer[MAX_PACK_LENGTH];
uint8 DataRecvBuffer[MAX_PACK_LENGTH];
RootDeviceStruct RootDevice;
uint8 Unpack(uint8 *type)
{
    type++;
    return (*type&0xFC)>>2;
}
