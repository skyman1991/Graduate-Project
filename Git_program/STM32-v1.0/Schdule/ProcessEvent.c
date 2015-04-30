#include "common.h"
uint8 TQ[MAX_TASK_NUM];
unsigned int current_tsk;
unsigned int last_tsk;
/**
* 初始化任务队列
*/
void Init_TQ(void)
{
    int i;
    for (i=0; i<MAX_TASK_NUM; i++)
    {
        TQ[i] = 0;
    }
    current_tsk = 0;
    last_tsk = 0;
}

/**
* 任务进队
*/
uint8 PostTask(uint8 event)
{
    if (TQ[last_tsk] == 0)
    {
        TQ[last_tsk] = event;
        last_tsk = (last_tsk + 1) % MAX_TASK_NUM;
        return TQ_SUCCESS;
    }
    else
    {
        //printf("TQ is FULL!\n");
        return TQ_FULL;		
    }
}

/**
* 任务出队
*/
uint8 Pop_T(void)
{
    uint8 event;
    if (TQ[current_tsk] != 0)
    {
        event = TQ[current_tsk];
        TQ[current_tsk] = 0;
        current_tsk = (current_tsk + 1) % MAX_TASK_NUM;
        return event;
    }
    else
    {
        //printf("TQ is EMPTY!\n");
        return TQ_EMPTY;
    }
}
uint8 Process_Event()
{
    uint8 current_event;
    current_event = Pop_T();
    switch(current_event)
    {
			case EVENT_SEND_BEACON:
				SendBeacon();
			break;
    }
    return current_event;
}
