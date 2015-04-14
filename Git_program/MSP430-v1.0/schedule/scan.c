#include "common.h"
#include "scan.h"
float ChannelList[]={470.001f,472.501f,475.001f,477.501f,480.001f,482.501f,485.001f,487.501f,
                     490.001f,492.501f,495.001f,497.501f,500.001f,502.501f,505.001f,507.501f};
uint8 StartChannel = CHANNEL_1;
uint8 EndChannel = CHANNEL_16;
ChannelTable SortedChannel;
ChannelTable Scan_Channel(uint8 startch,uint8 endch)
{
    ChannelTable detectedchannel;
    int i;
    uint8 data[SCAN_PACK_LENGTH];
    for(i=startch;i<=endch;i++)
    {
        //A7139_SetFreq(ChannelList[i]);
        //A7139_Receive_Once(data,SCAN_PACK_LENGTH);
    }
        
    return detectedchannel;
}
int tet[100];
void Scan_Channel1()
{

    int i;
    uint8 data[SCAN_PACK_LENGTH];
    for(i=0;i<=100;i++)
    {
        //A7139_SetFreq(ChannelList[i]);
        //A7139_Receive_Once(data,SCAN_PACK_LENGTH);
        tet[i]=i;
        
    }
}