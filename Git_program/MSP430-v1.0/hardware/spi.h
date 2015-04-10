/* Includes ------------------------------------------------------------------*/
#ifndef __SPI_H
#define __SPI_H
#include <msp430.h>
#include "sys.h"
#include "types.h"
#include "sys.h"

extern void SPI1_Init(void);			 						//初始化SPI1口
extern void SPI2_Init(void);			 						//初始化SPI2口
extern void SPI1_SetSpeed(uint8 SpeedSet); 			//设置SPI1速度  		 
extern void SPI2_SetSpeed(uint8 SpeedSet); 			//设置SPI2速度   
uint8 SPI1_ReadWriteByte(uint8 TxData);			//SPI1总线读写一个字节
uint8 SPI2_ReadWriteByte(uint8 TxData);			//SPI2总线读写一个字节
extern void ByteSend(uint8 src);
extern uint8 ByteRead(void);
extern void MOSI_IN(void);
extern void MOSI_OUT(void);
extern void SPIx_WriteByte(uint8 dat);
extern void SPI3_Init(void);
extern void SPIx_WriteWord(uint16 wrd);
extern uint16 SPIx_ReadWord(void);
extern uint8 SPIx_ReadByte(void);
extern void GO_Init(void);


#define MOSI_DATA  ((P3IN & BIT1)>>1)
#define GIO2       ((P1IN & BIT5)>>5)
#define GIO1       ((P1IN & BIT2)>>2)

#define SCK_CLEAR  (P3OUT &= ~BIT3)
#define SCK_SET    (P3OUT |= BIT3)
#define MOSI_CLEAR (P3OUT &= ~BIT1)
#define MOSI_SET   (P3OUT |= BIT1)
#define SCS_CLEAR  (P3OUT &= ~BIT2)
#define SCS_SET    (P3OUT |= BIT2)

	 
#endif
