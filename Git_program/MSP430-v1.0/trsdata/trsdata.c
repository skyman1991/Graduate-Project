#include "common.h"



int node2 = 0;
int node3 = 0;

int once = 0;
void DataQueue(void)
{
    DataSend[0] = PAK_TYPE;
    DataSend[1] = S_ADDRESS;    //Ô´
    DataSend[2] = D_ADDRESS;    //Ä¿µÄ
    //DataSend[3] = BeaconTimeCount>>8;
    //DataSend[4] = BeaconTimeCount;
    //DataSend[5] = once++;
    DataSend[6] = 0xAA;
    DataSend[3] = StateErrorTimes;
    if(NODE_NUM ==2)
    {
        DataSend[7] = once>>8;
        DataSend[8] = once;
    }
    else if(NODE_NUM == 3)
    {
        DataSend[9] = once>>8;
        DataSend[10] = once;
    }
    else if(NODE_NUM == 4)
    {
        DataSend[11] = once>>8;
        DataSend[12] = once;
    }
    once++;
}
