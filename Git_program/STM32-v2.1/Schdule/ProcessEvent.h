#ifndef _TASKQ_h_
#define _TASKQ_h_

#include "common.h"

#define    MAX_TASK_NUM    5
#define    TQ_SUCCESS      0
#define    TQ_FULL         1
#define    TQ_EMPTY        2

//event handler define
#define    EVENT_SCAN_CHANNEL             3
#define    EVENT_BEACON_SEND              4
#define    EVENT_BEACON_HANDLER           5
#define    EVENT_JOINREQUEST_SEND         6
#define    EVENT_JOINREQUEST_HANDLER      7
#define    EVENT_JOINREQUESTACK_HANDLER   8
#define    EVENT_JOINREQUESTACKOK_HANDLER 9
#define    EVENT_DATA_SEND                10
#define    EVENT_DATA_HANDLER             11
#define    EVENT_DATAACK_HANDLER          12
#define    EVENT_WAKE_A7139               13
#define    EVENT_CSMA_RESEND              14
#define    EVENT_COLLECT_DATA             15
#define    EVENT_IDENTIFY_CAR             16
#define    EVENT_UPLOAD_DATA							17
#define    EVENT_REJOIN_SEND							18
#define    EVENT_REJOIN_HANDLER           19

extern void Init_TQ(void);
extern uint8 PostTask(uint8 event);
extern uint8 Process_Event(void);

#endif
