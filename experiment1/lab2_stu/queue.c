#include "queue.h"
#include <stdio.h>

/** ����Ҫ��ʹ��ջʵ�ֶ��У����ֻ��ʹ��stack.h�еĺ�����������ֱ�ӷ���stack�ĵײ�ʵ�֣���

/**
 * ��ʼ������
 * @param Q ��������
 */
void InitQueue(Queue *Q)
{
    InitStack(&Q->stack1);
    InitStack(&Q->stack2);
}

/**
 * ��ն��� ��������
 * @param Q
 */
void ClearQueue(Queue *Q)
{
    InitStack(&Q->stack1);
    InitStack(&Q->stack2);
}

/**
 *
 * @param Q ��������
 * @return ���ض�����ʹ�ó���
 */
int QueueLength(Queue Q)
{
    return StackLength(Q.stack1) + StackLength(Q.stack2);
}

/**
 * �ж϶����Ƿ�Ϊ��
 * @param Q ��������
 * @return ���Ϊ�շ���1�����򷵻�0
 */
int QueueEmpty(Queue Q)
{
    //�ж�Q��Ϊ��ָ��
    if(Q!=NULL)
    {
        //�ж�Q�����Ƿ�Ϊ��
        if(QueueLength(Q)==0)
            return 1;
        return 0;
    }
    return -1��

}

/**
 * ��Ӳ�������Ԫ�ز�����У���Ҫ��������������������Ԫ����Ŀ���Ϊ MaxSize��
 * @param Q ��������
 * @param e �����Ԫ��
 * @return �������ɹ�����1�����򷵻�0
 */
int EnQueue(Queue *Q, DataType e)
{
    /*
        ����˼�������ĸ�ջPushԪ�أ�ʱ�临�Ӷ���Σ��ܷ񽵵�
    */
    //S2ջ��Ϊ���ף�S1ջ��Ϊ��β����S1��Ԫ�ض�����S2�У�����S2ջ������β��PushԪ��
    int a;
    //�ж϶���ָ��ǿ�
    if(Q==NULL)
    {
        return 0;
    }
    //����S1��S2
    while(!StackEmpty(Q->stack1))
    {
        Pop(&(Q->stack1),&a);
        Push(&(Q->stack2),a);//ע��
    }
    //�ж�S2����
    if(StackLength(Q->stack2)!=MaxSize)
    {
        //������Ԫ�ؼ����β��s2ջ����
        Push(&(Q->stack2),e);
        return 1;
    }
    return 0;
}

/**
 * ���Ӳ������Ӷ�����ȡ��һ��Ԫ��
 * @param Q ��������
 * @param e ���ܳ���Ԫ��
 * @return ����ɹ�ȡ������1�����򷵻�0
 */
int DeQueue(Queue *Q, DataType *e)
{
    /*
        ����˼�������ĸ�ջPopԪ�أ�ʱ�临�Ӷ���Σ��ܷ񽵵�
    */
    //S2ջ��Ϊ���ף�S1ջ��Ϊ��β����S2��Ԫ�ض�����S1�У�����S2ջ�������ף�PopԪ��
    int a;
    //�ж�Q��Ϊ��ָ��
    if(Q==NULL)
    {
        return 0;
    }
    //�ж϶��зǿ�
    if(QueueEmpty(*Q))
        return 0;
    //��S2��Ԫ�ض�����S1��
    while(!StackEmpty(Q->stack2))
    {
        Pop(&(Q->stack2),&a);
        Push(&(Q->stack1),a);//ע��
    }
    //��S1ջ�������ף�Ԫ��Pop
    Pop(&(Q->stack1),&a);
    (*e)=a;
    return 1;
}

/**
 * ��ȡ����ͷ����ɾ��Ԫ�أ�
 * @param Q ��������
 * @param e ���ܶ���ͷԪ��
 * @return ����ɹ���ȡ����1�����򷵻�0
 */
int GetHead(Queue Q, DataType *e)
{
    int a;
    //�ж�Qָ������ҷǿ�
    if(Q==NULL)
        return 0;
    if (QueueEmpty(Q))
        {return 0;}
    //���ջ2��ʹ���ݶ�����ջ1��S1ջ�������ף�������в���
    while(!StackEmpty(Q.stack2))
    {
        Pop(&(Q.stack2),&a);
        Push(&(Q.stack1),a);//ע��
    }
    //���ض���Ԫ��
    (*e) =  (Q.stack1).data[(Q.stack1).top];
    return 1;
}

/**
 * ��ȡ���е�һ�����鿽����˳��Ϊ�Ӷ���ͷ������β
 * @param Q ��������
 * @param seq ջ��Ԫ�ص�һ������
 */
void QueueToArray(Queue Q, DataType *seq)
{

    int i=0;
    int a;
    //���ջ2��ջ1
    while(!StackEmpty(Q.stack2))
    {
        Pop(&(Q.stack2),&a);

        Push(&(Q.stack1),a);//ע��
    }

    //ջ1��Ϊ��ʱ������Popջ1Ԫ�أ��������飬��Push��ջ2�洢
    while(StackLength(Q.stack1)!=0)
    {
        Pop(&(Q.stack1),&a);
        seq[i++] = a;
        Push(&(Q.stack2),a);
    }
}
