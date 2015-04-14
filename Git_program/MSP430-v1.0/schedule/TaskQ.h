#ifndef _TASKQ_h_
#define _TASKQ_h_

#include "common.h"

#define    MAX_TASK_NUM    5
#define    TQ_SUCCESS      0
#define    TQ_FULL         1
#define    TQ_EMPTY        2

extern void Init_TQ(void);
extern int PostTask(void (*T)());
extern void Run_TQ(void);

#endif