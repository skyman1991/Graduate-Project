/***********************************************************************************
    Filename: hal_uart.c

    Copyright 2007 Texas Instruments, Inc.
***********************************************************************************/

#include "common.h"


//----------------------------------------------------------------------------------
//  void halUartInit(uint8 baudrate, uint8 options)
//----------------------------------------------------------------------------------
void halUartInit(uint8 baudrate, uint8 options)
{
    // For the moment, this UART implementation only
    // supports communication settings 115200 8N1
    // i.e. ignore baudrate and options arguments.

  P3SEL = 0x30;                             // P3.4,5 = USCI_A0 TXD/RXD
  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  UCA0BR0 = 0x82;                            // 8MHz 9600
  UCA0BR1 = 0x6;                              // 8MHz 9600
  UCA0MCTL = UCBRS0;                        // Modulation UCBRSx = 1
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
//  IE2      |= UCA0RXIE; // Enable USCI_A0 RX interrupt

  
//    UCA0CTL1 |= UCSWRST;               // Keep USCI in reset state
//    UCA0CTL1 |= UCSSEL_2;              // SMCLK
//    UCA0BR0  = 0x22;                   // 4MHz 115200
//    UCA0BR1  = 0x00;                   // 4MHz 115200
//    UCA0MCTL = 0x08;                   // 4Mhz Modulation
//    
//    // Set up pins used by peripheral unit (USCI_A0)
//    P2SEL |= BIT4;    // P2.4 = TXD
//
//    UCA0CTL1 &= ~UCSWRST;              // Initialize USCI state machine
}

//----------------------------------------------------------------------------------
//  void halUartWrite(const uint8* buf, uint16 length)
//----------------------------------------------------------------------------------
void halUartWrite(const uint8* buf, uint16 length)
{
    uint16 i;
    for(i = 0; i < length; i++)
    {
        while (!(IFG2 & UCA0TXIFG));   // Wait for TX buffer ready to receive new byte
        UCA0TXBUF = buf[i];            // Output character
    }
}

//----------------------------------------------------------------------------------
//  void halUartRead(uint8* buf, uint16 length)
//----------------------------------------------------------------------------------
void halUartRead(uint8* buf, uint16 length)
{
}

/*
#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR (void)
{
  static uint16 len = 0;
  static uint8 xbee[100];
  static uint16 length;
  
  xbee[len] = UCA0RXBUF;
  

  
  if(len == 2)//第一二位为长度
  {
      length = (((uint16)xbee[1])<<8) + (uint16)xbee[2];
  }
  len++;
  
  //xbee数据只有这个长度，这时候应该截取有用的数据直接转发  
  //如果数据处理有问题在这个开个队列
  if(len == length + 4)
  {                     
      
      for(uint16 i = 17 ;i < length +3 ;i ++ ){//将数据直接转发
          while (!(IFG2 & UCA0TXIFG));  
          UCA0TXBUF = xbee[i]; 
      }
      len = 0;
      length = 100;
  }

}
*/
//3位数字 uint8以下的转换 直接输出ASCII嘛，仅用于串口输出
uint8* inttostring(uint8 ints)
{
    uint8 static string[3];
    string[0] = '0' + ints/100;
    string[1] = '0' + (ints - (ints/100)*100)/10;
    string[2] = '0' + (ints%10);
    return string;
}
uint8* inttostring_16(uint16 ints)
{
    uint8 static string[5];
    string[0] = '0' + ints/10000;
    string[1] = '0' + (ints/1000)%10;
    string[2] = '0' + (ints/100)%10;
    string[3] = '0' + (ints/10)%10;
    string[4] = '0' + (ints%10);
    return string;
}