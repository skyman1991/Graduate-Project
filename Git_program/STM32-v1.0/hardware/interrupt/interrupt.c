#include "common.h"
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
void Interrupt_Init(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);							//使能复用功能时钟
    
    //GPIOA.0 中断线以及中断初始化配置 上升沿触发 PA0  WK_UP
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource6); 
    EXTI_InitStructure.EXTI_Line=EXTI_Line6;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);																	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;						//使能按键KEY1,KEY0所在的外部中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;		//抢占优先级2 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;						//子优先级1 
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;									//使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);  	  														//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
    
    //A7139_StrobeCmd(CMD_PLL);
    //delay_us(2);
    //A7139_StrobeCmd(CMD_RX);
    //delay_us(2);
    
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
__asm void DisableInterrupt()
{
		cpsie I;
}
__asm void EnableInterrupt()
{
		cpsid I;
}
