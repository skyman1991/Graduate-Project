/* Includes ------------------------------------------------------------------*/
#include "sys.h"
#include "common.h"
/*
 * 函数名：NVIC_Configuration
 * 描述  ：设置NVIC中断分组2:2位抢占优先级，2位响应优先级
 * 输入  ：无
 * 输出  ：无
 */
void NVIC_Configuration(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}
void sys_init(void)
{
		delay_init();	    	 			
		NVIC_Configuration(); 	 	
		uart_init();	 		
		LED_Init();			     			
		KEY_Init();	
		SPI3_Init();
		A7139_Init(470.001f);
	  TIM3_Int_Init(BECAON_PERIOD*10-1,7200-1);	//10Khz的计数频率，计数到1000为100ms 
	  //TIM4_Int_Init(99,71);  //最小时间单位 1us
		Interrupt_Init();
		Init_TQ();
		
}
