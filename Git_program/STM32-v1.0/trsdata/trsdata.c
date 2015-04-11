#include "trsdata.h"
#include "common.h"
u8 DataRecv[MAX_DATA_LENGTH];
u8 DataSend[MAX_DATA_LENGTH];


void DataQueue(void)
{
	  int i = 0;
	  for(i=0;i<64;i++)
	    DataSend[i]=i;
	  DataSend[0] = CMD_BEACON;
	  DataSend[1] = S_ADDRESS;
	  DataSend[2] = D_ADDRESS;
	  DataSend[3] = BeaconTimeCount>>8;
	  DataSend[4] = BeaconTimeCount;
	  DataSend[5] = 64;
	  DataSend[6] = 0xAA;
}

