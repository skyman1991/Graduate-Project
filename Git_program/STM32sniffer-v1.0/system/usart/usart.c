/* Includes ------------------------------------------------------------------*/
#include "sys.h"
#include "usart.h"	  
 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_UCOS
#include "includes.h"					//ucos 使用	  
#endif  
 
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); 
    USART_SendData(USART1,(uint8_t)ch);   
	return ch;
}
#endif 
 

/*
 * 函数名：uart_init
 * 描述  ：初始化IO 串口1 
 * 输入  ：bound:波特率
 * 输出  ：无
 */	
void uart_init(){
	USART_InitTypeDef USART_InitStructure;
  GPIO_InitTypeDef  GPIO_InitStructure;             
  NVIC_InitTypeDef 	NVIC_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	USART_InitStructure.USART_BaudRate = 115200; 
  USART_InitStructure.USART_WordLength = USART_WordLength_8b; 
  USART_InitStructure.USART_StopBits = USART_StopBits_1;    
  USART_InitStructure.USART_Parity = USART_Parity_No ;      
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;   
  
  USART_Init(USART1, &USART_InitStructure);  
  USART_Cmd(USART1, ENABLE);  

	USART_ITConfig(USART1 , USART_IT_RXNE, ENABLE);
//******************************************************************************
//  串口1所使用管脚输出输入定义
//******************************************************************************
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;         //IO口的第12脚
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //IO口速度
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   //IO口复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);            //初始化串口2输出IO口


  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;            //IO口的第2脚
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //IO口速度
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//IO口悬空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);               //初始化串口2输入IO
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitStructure.NVIC_IRQChannel	=	USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	=	3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority	=	2;
  NVIC_InitStructure.NVIC_IRQChannelCmd	=	ENABLE;
  NVIC_Init(&NVIC_InitStructure);

}
void Usart1_PutChar(uint8_t ch)
{
    USART_SendData(USART1,  ch);

    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
    {}   
}
void Usart1_PutData(uint8_t *buffer,uint8_t count)
{
		int i;
		for (i = 0; i < count; i++)
    {
				Usart1_PutChar(buffer[i]);
    }
		//printf("n");
}
/*
 * 函数名：USART1_IRQHandler
 * 描述  ：串口1中断服务程序
 * 输入  ：无
 * 输出  ：无
 */	
void USART1_IRQHandler(void)
{

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)//接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
	}
} 


