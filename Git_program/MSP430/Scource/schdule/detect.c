#include "common.h"
int16 AD_Value;
int AD_middle_value = 0;
uint8 Car_Flag = 0;                             //识别结果
uint8 Car_Flag_Memory = 0;                      //上一次识别结果
uint16 Magnet_Value[COLLECT_WIDTH];             //传感器采集值
uint8  Start_Collect = 1;       //是否开启采集
uint16 collect_count = 0;
void CollectData()
{
    Magnet_Value[collect_count++] = SampleChannel(0x02);
    if(collect_count>COLLECT_WIDTH)
    {
        collect_count = 0;
        Start_Collect = 0;
    }
    else
    {
        Start_Collect = 1;
        PostTask(EVENT_IDENTIFY_CAR);
    }
//    AD_Value=SampleChannel(0x02);
//    if(AD_middle_value-AD_Value>50)
//    {
//        halLedSet(1);//NKJFK-GPHP7-G8C3J-P6JXR-HQRJR
//        Car_Flag = 1;
//    }
//    else if(AD_Value-AD_middle_value>50)
//    {
//        halLedSet(1);//NKJFK-GPHP7-G8C3J-P6JXR-HQRJR
//        Car_Flag = 1;
//    }
//    else
//    {
//        halLedClear(1);
//        Car_Flag = 0;
//    }
//    if(Car_Flag_Memory!=Car_Flag)
//    {
//        Data_Change_Flag = 1;
//        PostTask(EVENT_DATA_SEND);
//    }
//    else
//    {
//        Data_Change_Flag = 0;
//    }
//    Car_Flag_Memory = Car_Flag;
    
    if(Data_Change_Flag == 1)
    {
        Data_Change_Flag = 0;
        A7139_Deep_Wake();
        EN_INT;
    }
}
void IdentifyCar()
{

}