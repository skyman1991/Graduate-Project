#ifndef _INTERRUPT_h_
#define _INTERRUPT_h_
#include "common.h"

extern void Interrupt_Init(void);
extern void DisableInterrupt(void);
extern void EnableInterrupt(void);

extern u8 DataRecv[MAX_PACK_LENGTH];
extern u8 DataSend[MAX_PACK_LENGTH];

extern u8 BeaconSendFlag;
#endif
