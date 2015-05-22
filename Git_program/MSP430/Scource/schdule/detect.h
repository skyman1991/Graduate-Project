#ifndef _DETECT_h_
#define _DETECT_h_
#include "common.h"

#define COLLECT_EN  1           //是否开启数据采集
#define COLLECT_PERIOD  1000   //采集周期  单位：100us
#define COLLECT_WIDTH   300    //按30S计算，每秒采集10次


extern void CollectData();
extern void IdentifyCar();

extern uint8 Data_Change_Flag;
extern int AD_middle_value;
extern int16 AD_Value;
extern uint8 Car_Flag;
extern uint16 Magnet_Value[COLLECT_WIDTH];
extern uint8  Start_Collect;
#endif 
