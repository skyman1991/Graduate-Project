/* Includes ------------------------------------------------------------------*/  
#include "common.h"

/*
 * 函数名：LED_Init
 * 描述  ：初始化PC3和PD6为输出口.并使能这两个口的时钟,LED IO初始化
 * 输入  ：无
 * 输出  ：无
 */	    
void LED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOA, ENABLE);//使能PC,PD端口时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;								//端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO口速度为50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);	  				     		//根据设定参数初始化PD.12
	GPIO_SetBits(GPIOD,GPIO_Pin_0);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;								//端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO口速度为50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);	  				     		//根据设定参数初始化PC.3
	GPIO_SetBits(GPIOD,GPIO_Pin_1);														//PC.3输出高 	

	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ;								//端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO口速度为50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);	  				     		//根据设定参数初始化PD.12
	GPIO_SetBits(GPIOD,GPIO_Pin_2);													//PD.12输出高 


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;								//端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO口速度为50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);	  				     		//根据设定参数初始化PD.12
	GPIO_SetBits(GPIOD,GPIO_Pin_3);													//PD.12输出高 


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;								//端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO口速度为50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);	  				     		//根据设定参数初始化PD.12
	GPIO_SetBits(GPIOD,GPIO_Pin_4);													//PD.12输出高 	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 ;								//端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO口速度为50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);	  				     		//根据设定参数初始化PD.12
	GPIO_SetBits(GPIOD,GPIO_Pin_5);													//PD.12输出高

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;								//端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO口速度为50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);	  				     		//根据设定参数初始化PD.12
	GPIO_SetBits(GPIOD,GPIO_Pin_6);													//PD.12输出高 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;								//端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 			//推挽输出
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				     		//根据设定参数初始化PD.12

	
	
	
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ;								//端口配置, 推挽输出
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//推挽输出
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO口速度为50MHz
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				     		//根据设定参数初始化PD.12
// 	GPIO_SetBits(GPIOA,GPIO_Pin_9);													//PD.12输出高 
// 	
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 ;								//端口配置, 推挽输出
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			//推挽输出
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO口速度为50MHz
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				     		//根据设定参数初始化PD.12
// 	GPIO_SetBits(GPIOA,GPIO_Pin_10);													//PD.12输出高 

}
