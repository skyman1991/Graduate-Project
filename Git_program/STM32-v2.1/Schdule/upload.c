#include "common.h"
/**
* 初始化任务队列
*/

UartDataStruct UploadTQ[UPLOAD_NODE_NUM];
uint8 current_upload_tsk;
uint8 last_upload_tsk;
uint8 Node_Inwaiting = 0;							//队列中节点的数量
uint16 Pop_Count = 0;

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
				Node_Inwaiting++;							
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
        //Clear_Node(&UploadTQ[current_upload_tsk]);
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
void Clear_Buffer(uint8 current,uint8 last)
{
		int i=0;
		for(i=current;i<last;i++)
		{
				Clear_Node(&UploadTQ[i]);
		}
}
uint8 rec;
void Upload_Data()
{
    uint16 time_out = 0;
		uint8 current_memory = current_upload_tsk;
		uint8 last_memory = last_upload_tsk;
	
    UartDataStruct node;
		if(Node_Inwaiting == 0)		//没有要发送的节点
		{
				return;
		}
		
    Usart1_PutChar(0x7D);
    Usart1_PutChar(0x7E);								//包头
		Usart1_PutChar(last_upload_tsk);			//本次要发送的节点个数
    node = PopUploadNode();
		Pop_Count = 0;
		//发送队列内存在的全部节点
    while (!Empty_Node(&node))
    {
        Usart1_PutChar(node.address >> 8);
        Usart1_PutChar(node.address);
        Usart1_PutChar(node.data);
        node = PopUploadNode();
			  Pop_Count++;
				if(Pop_Count>UPLOAD_NODE_NUM)
				{
						//队列已经满了，还没有发出去
						return;
				}
    }
		//Usart1_PutChar(0x7E);
		//Usart1_PutChar(0x7D);
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
		{
				if (time_out++ > 200)
				{
						delay_us(10);
						current_upload_tsk = 0;				//如果没有收到确认，发送指针置头，重新发送
						return;
				}
		}
		if(USART1_Getchar()!='o')					//确认数据位'o'
		{
				current_upload_tsk = 0;				//如果没有收到确认，发送指针置头，重新发送
				return;
		}
		//若发送成功，清空队列中节点信息，插入和发送指针置头
		Clear_Buffer(current_memory,last_memory);
		current_upload_tsk = 0;
		last_upload_tsk = 0;
		Node_Inwaiting = 0;
}
