#ifndef _INTERRUPT_h_
#define _INTERRUPT_h_
#include "common.h"
extern void Interrupt_Init(void);
extern __asm void DisableInterrupt(void);
extern __asm void EnableInterrupt(void);
#endif
