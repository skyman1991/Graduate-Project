#include "common.h"
int16 AD_Value;
int AD_middle_value = 0;
uint8 Car_Flag = 0;                             //识别结果
uint8 Car_Flag_Memory = 0;                      //上一次识别结果
uint16 CODE Magnet_Value[COLLECT_WIDTH];             //传感器采集值
uint8 Start_Collect = 1;       //是否开启采集
uint16 collect_count = 0;
int Ave_Slop = 0;

void CollectData()
{
    Magnet_Value[collect_count++] = SampleChannel(0x02);
    if(collect_count>COLLECT_WIDTH)
    {
        collect_count = 0;
        Start_Collect = 0;
        PostTask(EVENT_IDENTIFY_CAR);
    }
    else
    {
        Start_Collect = 1;
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
    
//非低功耗模式测试先注释掉
//    if(Data_Change_Flag == 1)
//    {
//        Data_Change_Flag = 0;
//        A7139_Deep_Wake();
//        EN_INT;
//    }
}
void bubbledata(DataStruct *a,uint16 n) 
{ 
    uint16 i,j;
    DataStruct temp;
    for(i=0;i<n-1;i++) 
    {
        
        for(j=i+1;j<n;j++) 
            if(a[i].value<a[j].value) 
            { 
                temp=a[i];
                a[i]=a[j]; 
                a[j]=temp; 
            }
        
    }
    
}
void IdentifyCar()
{
    int i=0;
    //当前长度为5，长度变化需要修改此处。

    Ave_Slop = (int)((Magnet_Value[1]-Magnet_Value[0]))+
               (int)((Magnet_Value[2]-Magnet_Value[0]))/2+
               (int)((Magnet_Value[3]-Magnet_Value[0]))/3+
               (int)((Magnet_Value[4]-Magnet_Value[0]))/4;
    Ave_Slop = Ave_Slop/COLLECT_WIDTH;
    Start_Collect = 1;
    if(Ave_Slop>SLOP_THRESHLOD)
    {
        Car_Flag = 1;
        halLedSet(1);
    }
    else if(Ave_Slop<-SLOP_THRESHLOD)
    {
        Car_Flag = 1;
        halLedSet(1);
    }
    else
    {
        Car_Flag = 0;
        halLedClear(1);
    }
        

}