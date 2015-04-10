/* Includes ------------------------------------------------------------------*/
#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"	 

#define KEY0  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)
#define KEY1  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6)
#define KEY2  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) 


#define KEY_DOWN	1
#define KEY_RIGHT	2
#define KEY_UP 		3

void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8);  	//按键扫描函数					    
#endif
