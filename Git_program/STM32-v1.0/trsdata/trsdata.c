#include "trsdata.h"
#include "common.h"
u8 DataRecv[MAX_DATA_LENGTH];
u8 DataSend[MAX_DATA_LENGTH];
u16 BeaconTimeCount = 0;
u8 BeaconSendFlag = 0;
u16 node2_count = 0; 
u16 node3_count = 0; 
u16 node4_count = 0; 
u16 node2_error = 0; 
u16 node3_error = 0; 
u16 node4_error = 0; 
u16 node2_reset = 0; 
u16 node3_reset = 0; 
u16 node4_reset = 0;
void EXTI9_5_IRQHandler(void)
{
	EXTI->PR |= EXTI_Line6;
		/************3.6ms*************/
//	  LED2_OFF();
		A7139_ReadFIFO(DataRecv,32);
		delay_us(2);
		A7139_StrobeCmd(CMD_RX);
		delay_us(2);
		/*****************************/
		LED4_REV();
	
	  if(DataRecv[1] == 0x02)
		{
				node2_count=DataRecv[7]<<8;
			  node2_count|=DataRecv[8];
			  node2_reset = DataRecv[3];
			  if(DataRecv[6] != 0xAA)
				{
						node2_error++;
				}
		}
		if(DataRecv[1] == 0x03)
		{
				node3_count=DataRecv[9]<<8;
			  node3_count|=DataRecv[10];
				node3_reset = DataRecv[3];
			  if(DataRecv[6] != 0xAA)
				{
						node3_error++;
				}
		}
		if(DataRecv[1] == 0x04)
		{
				node4_count=DataRecv[11]<<8;
		  	node4_count|=DataRecv[12];
			  node4_reset = DataRecv[3];
			  if(DataRecv[6] != 0xAA)
				{
						node4_error++;
				}
		}
		
		//LED2_ON();

}
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
void TIM3_IRQHandler(void)   //1s
{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 
		LED3_REV();
	
		BeaconTimeCount++;
	  BeaconSendFlag = 1;
	
}
void TIM4_IRQHandler(void)   //100us
{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //清除TIMx更新中断标志 
}
