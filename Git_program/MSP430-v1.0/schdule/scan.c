#include "common.h"
#include "scan.h"
const float CODE ChannelList[]={0,470.001f,472.501f,475.001f,477.501f,480.001f,482.501f,485.001f,487.501f,
                           490.001f,492.501f,495.001f,497.501f,500.001f,502.501f,505.001f,507.501f};
uint8 StartChannel = CHANNEL_1;
uint8 EndChannel = CHANNEL_16;
ChannelTable SortedChannel[CHANNEL_NUM];
ChannelTable ScanChannel[CHANNEL_NUM];
  
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
    for(i=startch;i<endch+2;i++)   //循环16次
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
            A7139_ReadFIFO(data,datalength);
            ScanChannel[i-1].channel_num = i;
            ScanChannel[i-1].channel_rssi = A7139_GetRSSI();
            ScanChannel[i-1].channel_free = data[6];
        }
        else
        {
            ScanChannel[i-1].channel_num = 0;
            ScanChannel[i-1].channel_rssi = 0;
            ScanChannel[i-1].channel_free = 0;
        }
        timeout = SCAN_TIME_OUT; 
    }
    return i;
}
