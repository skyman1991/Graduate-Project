#ifndef _TASKQ_h_
#define _TASKQ_h_

#include "common.h"

#define    MAX_TASK_NUM    5
#define    TQ_SUCCESS      0
#define    TQ_FULL         1
#define    TQ_EMPTY        2
#define    EVENT_SCAN_CHANNEL    3
#define    EVENT_SEND_BEACON     4

extern void Init_TQ(void);
extern uint8 PostTask(uint8 event);
extern uint8 Process_Event(void);

#endif
