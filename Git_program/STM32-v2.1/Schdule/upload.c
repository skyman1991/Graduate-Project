#include "common.h"
/**
* ��ʼ���������
*/

UartDataStruct UploadTQ[UPLOAD_NODE_NUM];
uint8 current_upload_tsk;
uint8 last_upload_tsk;
uint8 Node_Inwaiting = 0;							//�����нڵ������

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
* �������
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
* �������
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
		if(Node_Inwaiting == 0)		//û��Ҫ���͵Ľڵ�
		{
				return;
		}
		
    Usart1_PutChar(0x7D);
    Usart1_PutChar(0x7E);								//��ͷ
		Usart1_PutChar(last_upload_tsk);			//����Ҫ���͵Ľڵ����
    node = PopUploadNode();
		//���Ͷ����ڴ��ڵ�ȫ���ڵ�
    while (!Empty_Node(&node))
    {
        Usart1_PutChar(node.address >> 8);
        Usart1_PutChar(node.address);
        Usart1_PutChar(node.data);
        node = PopUploadNode();
    }
		//Usart1_PutChar(0x7E);
		//Usart1_PutChar(0x7D);
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
		{
				if (time_out++ > 200)
				{
						delay_us(10);
						current_upload_tsk = 0;				//���û���յ�ȷ�ϣ�����ָ����ͷ�����·���
						return;
				}
		}
		if(USART1_Getchar()!='o')					//ȷ������λ'o'
		{
				current_upload_tsk = 0;				//���û���յ�ȷ�ϣ�����ָ����ͷ�����·���
				return;
		}
		//�����ͳɹ�����ն����нڵ���Ϣ������ͷ���ָ����ͷ
		Clear_Buffer(current_memory,last_memory);
		current_upload_tsk = 0;
		last_upload_tsk = 0;
		Node_Inwaiting = 0;
		

}