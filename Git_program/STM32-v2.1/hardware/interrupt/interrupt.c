#include "common.h"
int time_out = 0;

/*******************************************************************************
* Function Name  : Interrupt_Init
* Description    : This function init external interrupt for radio receive.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Interrupt_Init(void)
{
		EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);							//使能复用功能时钟

		//GPIOA.0 中断线以及中断初始化配置 上升沿触发 PA0  WK_UP
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource6); 
		EXTI_InitStructure.EXTI_Line=EXTI_Line6;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);																	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;						//使能按键KEY1,KEY0所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;						//子优先级1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;									//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  														//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	  A7139_StrobeCmd(CMD_PLL);
		delay_us(2);
		A7139_StrobeCmd(CMD_RX);
		delay_us(2);
		
		
		//GPIOA.0 中断线以及中断初始化配置 上升沿触发 PA0  WK_UP
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource3); 
		EXTI_InitStructure.EXTI_Line=EXTI_Line3;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);																	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;						//使能按键KEY1,KEY0所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;		//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;						//子优先级1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;									//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
		

}
/*******************************************************************************
* Function Name  : TIM3_IRQHandler
* Description    : This function handles period interrupt every 1S.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint8 TIM3_Count = 0;
void TIM3_IRQHandler(void)   //500ms
{
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 
    TIM3_Count++;
		if(TIM3_Count<5)
		{	
				PostTask(EVENT_REJOIN_SEND);
		}
		else
		{
				TIM3_Count = 10;
				PostBeacon();
				PostTask(EVENT_UPLOAD_DATA);
		}
		
		Frame_Time = 0;
		//BeaconSendFlag = 1;
		time_out++;
		if(time_out > TIMEOUT)
		{
				A7139_StrobeCmd(CMD_STBY);
				delay_us(1);
				A7139_StrobeCmd(CMD_PLL);
				delay_us(1);
				A7139_StrobeCmd(CMD_RX);
				delay_us(1);
			  time_out = 0;
				printf("restart \r\n");
		}	

}
/*******************************************************************************
* Function Name  : TIM4_IRQHandler
* Description    : This function handles period interrupt every 100us.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM4_IRQHandler(void)   //100us
{
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //清除TIMx更新中断标志 
	  Frame_Time++;
}
/*******************************************************************************
* Function Name  : EXTI9_5_IRQHandler
* Description    : This function handles radio receive.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint8 rssisee = 0;
void EXTI9_5_IRQHandler(void)
{
    EXTI->PR |= EXTI_Line6;
		
    A7139_ReadFIFO(DataRecvBuffer,MAX_PACK_LENGTH);
		
    RXMode();
		time_out = 0;
		if(PackValid())
		{
				LED2_REV();
			  
				switch (Unpack(DataRecvBuffer))
				{
						case JOINREQUEST_TYPE:
							PostTask(EVENT_JOINREQUEST_HANDLER);
							break;
						case JOINREQUESTACKOK_TYPE:
							PostTask(EVENT_JOINREQUESTACKOK_HANDLER);
							break;
						case DATA_TYPE:
							PostTask(EVENT_DATA_HANDLER);
							break;
				}
		}
		
   
}
uint8 mode = 0;
void EXTI3_IRQHandler(void)
{
		EXTI->PR |= EXTI_Line3;
		/*if(mode==254)
			mode = 0;
		mode++;
		if(mode%2==0)
		{
				Power_Mode = 1;
				LED5_ON();
		}
		else
		{
				Power_Mode = 0;
				LED5_OFF();
		}*/
			
}
void DisableInterrupt()
{
		__disable_irq(); 
}
void EnableInterrupt()
{
		__enable_irq(); 
}
