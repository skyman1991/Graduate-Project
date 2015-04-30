// #include "trsdata.h"
// #include "common.h"
// u8 DataRecv[MAX_DATA_LENGTH];
// u8 DataSend[MAX_DATA_LENGTH];
// u16 BeaconTimeCount = 0;
// u8 BeaconSendFlag = 0;
// u8 uart_data[8];
// void EXTI9_5_IRQHandler(void)
// {
// 	EXTI->PR |= EXTI_Line6;
// 		/************3.6ms*************/
// 	  
// 		A7139_ReadFIFO(DataRecv,32);
// 		delay_us(2);
// 		A7139_StrobeCmd(CMD_RX);
// 		delay_us(2);
// 		uart_data[0] = 1;
// 		uart_data[2] = 2;
// 		uart_data[4] = 3;
// 		uart_data[6] = 4;
// 		/*****************************/
//  		if(DataRecv[1] == 0x02)
//  		{
// 				LED1_REV();
// 			  
// 			  uart_data[1] = DataRecv[8];
//  		}
// 		else if(DataRecv[1] == 0x03)
//  		{
// 				LED2_REV();
// 			 
// 			  uart_data[3] = DataRecv[10];
//  		}
// 		else if(DataRecv[1] == 0x04)
//  		{
// 				LED3_REV();
// 				
// 			  uart_data[5] = DataRecv[12];
//  		}
// 		else if(DataRecv[1] == 0x05)
//  		{
// 				
// 			  LED4_REV();
// 				
// 			  uart_data[7] = DataRecv[14];
//  		}
// 		else
// 		{
// 				LED5_REV();
// 		}
// // 		if(DataRecv[1] == 0x03)
// // 		{
// // 				node3_count=DataRecv[9]<<8;
// // 			  node3_count|=DataRecv[10];
// // 				node3_reset = DataRecv[3];
// // 			  if(node3_count==1)
// // 			  {
// //            LED2_ON();
// //         } 
// // 				else LED2_OFF();
// // 			if(DataRecv[6] != 0xAA)
// // 				{
// // 						node3_error++;
// // 				}
// // 		}
// // 		if(DataRecv[1] == 0x04)
// // 		{
// // 				node4_count=DataRecv[11]<<8;
// // 		  	node4_count|=DataRecv[12];
// // 			  node4_reset = DataRecv[3];
// // 			  if(node4_count==1)
// // 			  {
// //            LED3_ON();
// //         } 
// // 				else LED3_OFF();
// // 			  if(DataRecv[6] != 0xAA)
// // 				{
// // 						node4_error++;
// // 				}
// // 		} 
// // 		if(DataRecv[1] == 0x05)
// // 		{
// // 				node5_count=DataRecv[13]<<8;
// // 		  	node5_count|=DataRecv[14];
// // 			  node5_reset = DataRecv[3];
// // 			  if(node5_count==1)
// // 			  {
// //            LED4_ON();
// //         } 
// // 				else LED4_OFF();
// // 			  if(DataRecv[6] != 0xAA)
// // 				{
// // 						node5_error++;
// // 				}
// // 		}
// // 		if(DataRecv[1] == 0x06)
// // 		{
// // 				node6_count=DataRecv[15]<<8;
// // 		  	node6_count|=DataRecv[16];
// // 			  node6_reset = DataRecv[3];
// // 			  if(node6_count==1)
// // 			  {
// //            LED5_ON();
// //         } 
// // 				else LED5_OFF();
// // 			  if(DataRecv[6] != 0xAA)
// // 				{
// // 						node6_error++;
// // 				}
// // 		}
// // 		//LED2_ON();

// }
// void DataQueue(void)
// {
// 	  int i = 0;

// 	  //LED1_OFF();LED2_OFF();LED3_OFF();LED4_OFF();
// 	  DataSend[0] = CMD_BEACON;
// 	  DataSend[1] = S_ADDRESS;
//  	  DataSend[2] = 255;
// // // 	  DataSend[3] = BeaconTimeCount>>8;
// // // 	  DataSend[4] = BeaconTimeCount;
// 	  DataSend[5] = 64;
// 	  DataSend[6] = 0xAA;
// }
// void TIM3_IRQHandler(void)   //1s
// {
// 		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 
// 		//LED3_REV();
// 	
// 		BeaconTimeCount++;
// 	  BeaconSendFlag = 1;
// 	
// }
// void TIM4_IRQHandler(void)   //100us
// {
// 		TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //清除TIMx更新中断标志 
// }
