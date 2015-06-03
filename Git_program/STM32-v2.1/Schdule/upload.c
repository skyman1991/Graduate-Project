#include "common.h"
/**
* 初始化任务队列
*/

UartDataStruct UploadTQ[UPLOAD_NODE_NUM];
unsigned int current_upload_tsk;
unsigned int last_upload_tsk;

void Clear_Node(UartDataStruct *node)
{
		node->address = 0;
		node->data = 0;
}
void Init_Upload_TQ(void)
{
    int i;
    for (i=0; i<UPLOAD_NODE_NUM; i++)
    {
        Clear_Node(&UploadTQ[i]);
    }
    current_upload_tsk = 0;
    last_upload_tsk = 0;
}
uint8 Empty_Node(UartDataStruct *node)
{
		if(node->address == 0&&node->data==0)
			return 1;
		else
			return 0;
}

/**
* 任务进队
*/

uint8 PostUploadNode(UartDataStruct *node)
{
		if (Empty_Node(&UploadTQ[last_upload_tsk]))
    {
        UploadTQ[last_upload_tsk] = *node;
        last_upload_tsk = (last_upload_tsk + 1) % UPLOAD_NODE_NUM;
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
UartDataStruct PopUploadNode(void)
{
    UartDataStruct node;
    if (!Empty_Node(&UploadTQ[current_upload_tsk]))
    {
        node = UploadTQ[current_upload_tsk];
			  Clear_Node(&UploadTQ[current_upload_tsk]);
        current_upload_tsk = (current_upload_tsk + 1) % UPLOAD_NODE_NUM;
        return node;
    }
    else
    {
        //printf("TQ is EMPTY!\n");
				Clear_Node(&node);
        return node;
    }
}
uint8 rec;
void Upload_Data()
{
		UartDataStruct node;
		Usart1_PutChar(0x7D);
		Usart1_PutChar(0x7E);
		node = PopUploadNode();
		while(!Empty_Node(&node))
		{
				Usart1_PutChar(node.address>>8);
				Usart1_PutChar(node.address);
				Usart1_PutChar(node.data);
				node = PopUploadNode();
		}
		Usart1_PutChar(0x7E);
		Usart1_PutChar(0x7D);

}
