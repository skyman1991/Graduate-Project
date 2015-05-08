/* Includes ------------------------------------------------------------------*/
#include "spi.h"
#include "common.h"

	
void MOSI_IN(void)
{
	/*GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//设置成上拉输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);				//初始化GPIO*/
	GPIOA->CRL&=0xFFFF0FFF;
	GPIOA->CRL|=0x00008000;
	//GPIOA->ODR|=1<<6;
	
}
void MOSI_OUT(void)
{
	/*GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);				//初始化GPIO*/
	
	GPIOA->CRL&=0xFFFF0FFF;
	GPIOA->CRL|=0x00003000;
}
void SPI3_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	
 	GPIO_Init(GPIOA, &GPIO_InitStructure);				
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);				
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	
 	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
  /*GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);*/
		
	
	SCS = 1;
	SCK = 0;
	
}



/*
 * 函数名：SPI1_Init
 * 描述  ：SPI1模块的初始化代码，配置成主机模式，访问SD Card/W25X16/24L01/JF24C	
 * 输入  ：无
 * 输出  ：无
 */						  
void SPI1_Init(void)
{	    
 	GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;
	 
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA|RCC_APB2Periph_SPI1, ENABLE );//PORTB，SPI2时钟使能 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //PA5.6.7复用推挽  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

 	GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_4); //PA5.6.7上拉
			
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;		//设置SPI工作模式:设置为主SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//设置SPI的数据大小:SPI发送接收8位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//选择了串行时钟的稳态:时钟悬空高
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//数据捕获于第二个时钟沿
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//定义波特率预分频的值:波特率预分频值为16
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式
	SPI_Init(SPI1, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
 
	SPI_Cmd(SPI1, ENABLE); //使能SPI外设
	
	SPI2_ReadWriteByte(0xff);//启动传输	
}

/*
 * 函数名：SPI2_Init
 * 描述  ：SPI2模块的初始化代码，配置成主机模式，访问SD Card/W25X16/24L01/JF24C	
 * 输入  ：无
 * 输出  ：无
 */	
void SPI2_Init(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;

	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );//PORTB时钟使能 
	RCC_APB1PeriphClockCmd(	RCC_APB1Periph_SPI2,  ENABLE );//SPI2时钟使能 	
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //PB13/14/15复用推挽输出 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

 	GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);  //PB13/14/15上拉

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//设置SPI工作模式:设置为主SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//设置SPI的数据大小:SPI发送接收8位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//选择了串行时钟的稳态:时钟悬空高
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//数据捕获于第二个时钟沿
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;		//定义波特率预分频的值:波特率预分频值为16
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式
	SPI_Init(SPI2, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
 
	SPI_Cmd(SPI2, ENABLE); //使能SPI外设
	
	SPI2_ReadWriteByte(0xff);//启动传输	 

}

/*
 * 函数名：SPI2_SetSpeed
 * 描述  ：SPI2速度设置函数	
 * 输入  ：SpeedSet:
					 SPI_BaudRatePrescaler_2   2分频   
					 SPI_BaudRatePrescaler_8   8分频   
					 SPI_BaudRatePrescaler_16  16分频  
					 SPI_BaudRatePrescaler_256 256分频 
 * 输出  ：无
 */	
void SPI2_SetSpeed(u8 SpeedSet)
{
	SPI2->CR1&=0XFFC7; 
	SPI2->CR1|=SpeedSet;
	SPI_Cmd(SPI2,ENABLE); 
} 

/*
 * 函数名：SPI1_SetSpeed
 * 描述  ：SPI1速度设置函数	
 * 输入  ：SpeedSet:
					 SPI_BaudRatePrescaler_2   2分频   
					 SPI_BaudRatePrescaler_8   8分频   
					 SPI_BaudRatePrescaler_16  16分频  
					 SPI_BaudRatePrescaler_256 256分频 
 * 输出  ：无
 */	
void SPI1_SetSpeed(u8 SpeedSet)
{
	SPI1->CR1&=0XFFC7; 
	SPI1->CR1|=SpeedSet;
	SPI_Cmd(SPI1,ENABLE); 
} 

/*
 * 函数名：SPI2_ReadWriteByte
 * 描述  ：SPIx 读写一个字节
 * 输入  ：TxData:要写入的字节
 * 输出  ：返回值:读取到的字节
 */	
u8 SPI2_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) //检查指定的SPI标志位设置与否:发送缓存空标志位
	{
		retry++;
		if(retry>200)return 0;
	}			  
	SPI_I2S_SendData(SPI2, TxData); //通过外设SPIx发送一个数据
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET); //检查指定的SPI标志位设置与否:接受缓存非空标志位
	{
		retry++;
		if(retry>200)return 0;
	}	  						    
	return SPI_I2S_ReceiveData(SPI2); //返回通过SPIx最近接收的数据					    
}

/*
 * 函数名：SPI1_ReadWriteByte
 * 描述  ：SPIx 读写一个字节
 * 输入  ：TxData:要写入的字节
 * 输出  ：返回值:读取到的字节
 */
u8 SPI1_ReadWriteByte(u8 TxData)
{				   			 
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) //检查指定的SPI标志位设置与否:发送缓存空标志位
	{
		retry++;
		if(retry>200)return 0;
	}			  
	SPI_I2S_SendData(SPI1, TxData); //通过外设SPIx发送一个数据
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET) //检查指定的SPI标志位设置与否:接受缓存非空标志位
	{
		retry++;
		if(retry>200)return 0;
	}	  						    
	return SPI_I2S_ReceiveData(SPI1); //返回通过SPIx最近接收的数据					    
}

void SPIx_WriteByte(u8 dat)
{
    u8 i;
    for(i=0; i<8; i++)
    {
        if(dat & 0x80)
            MOSI = 1;
        else
            MOSI = 0;
        delay_us(1);
        SCK = 1;
        delay_us(1);
        SCK  =0;
        dat=dat<<1;
				delay_us(1);
    }
}
void SPIx_WriteWord(u16 wrd)
{
    u8 i;
	  MOSI = 0;
    for(i=0; i<16; i++)
    {
        if(wrd & 0x8000)
            MOSI = 1;
        else
            MOSI = 0;
				delay_us(1);
        SCK = 1;
        delay_us(1);
        SCK = 0;
        wrd=wrd<<1;
				delay_us(1);
    }
}
u16 SPIx_ReadWord(void)
{
	u8  i;
	u16 tmp=0;
	MOSI = 0;
	MOSI_IN();	
	for(i=0; i<16; i++)
	{
        if(MOSI_DATA)
            tmp = 0x01|(tmp << 1);
        else
            tmp = tmp << 1;
				delay_us(1);
        SCK = 1;
        delay_us(1);
        SCK = 0;
				//tmp = tmp << 1;
				delay_us(1);
     }
	MOSI_OUT();
     return tmp;
}
u8 SPIx_ReadByte(void)
{
	u8 i,tmp=0;
	MOSI_IN();
	for(i=0; i<8; i++)
	{
        if(MOSI_DATA)
            tmp = 0x01|(tmp << 1);
        else
            tmp = tmp << 1;
				delay_us(1);
        SCK=1;
        delay_us(1);
        SCK = 0;
				//tmp = tmp << 1;
				delay_us(1);
     }
	MOSI_OUT();
	return tmp;
}

