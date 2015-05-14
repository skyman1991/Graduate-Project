#ifndef _INTERRUPT_h_
#define _INTERRUPT_h_
#include "common.h"

#define   EN_TIMER1    {TA1CCTL0 = CCIE;TA1CTL|=TACLR;}
#define   DIS_TIMER1   TA1CCTL0 &= ~CCIE
#define   EN_TIMER0    {TA0CCTL0 = CCIE;TA0CTL|=TACLR;}
#define   DIS_TIMER0   TA0CCTL0 &= ~CCIE

extern void Interrupt_Init(void);

extern int Frame_Time;
#endif