/* Includes ------------------------------------------------------------------*/
#include "key.h"
#include "common.h"

/*
 * 函数名：KEY_Init
 * 描述  ：按键初始化函数
 * 输入  ：无
 * 输出  ：无
 */	 
void KEY_Init(void) 														//IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD,ENABLE);//使能PORTA,PORTC,PORTD时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//设置成上拉输入
 	GPIO_Init(GPIOC, &GPIO_InitStructure);				//初始化GPIO

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//设置成上拉输入
 	GPIO_Init(GPIOD, &GPIO_InitStructure);				//初始化GPIO
	
	//初始化 WK_UP-->GPIOA.0	下拉输入
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	//PA0设置成输入，默认下拉	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);				//初始化GPIOA.0
}

/*
 * 函数名：KEY_Init
 * 描述  ：按键处理函数
					 0，没有任何按键按下
					 1，KEY0按下
					 2，KEY1按下
					 3，KEY2按下 WK_UP
					 注意此函数有响应优先级,KEY2>KEY0>KEY1
 * 输入  ：mode:0,不支持连续按;1,支持连续按;
 * 输出  ：返回按键值
 */	 
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;														//按键按松开标志
	if(mode)key_up=1;  														//支持连按		  
	if(key_up&&(KEY0==0||KEY1==0||KEY2==1))
	{
		delay_ms(10);																//去抖动 
		key_up=0;
		if(KEY2==1)return KEY_UP;
		else if(KEY0==0)return KEY_DOWN;
		else if(KEY1==0)return KEY_RIGHT;
	}else if(KEY2==0&&KEY0==1&&KEY1==1)key_up=1; 	// 无按键按下
 	return 0;																			
}
