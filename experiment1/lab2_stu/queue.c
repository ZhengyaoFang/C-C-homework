#include "queue.h"
#include <stdio.h>

/** ！！要求使用栈实现队列，因此只能使用stack.h中的函数。不允许直接访问stack的底层实现！！

/**
 * 初始化队列
 * @param Q 操作队列
 */
void InitQueue(Queue *Q)
{
    InitStack(&Q->stack1);
    InitStack(&Q->stack2);
}

/**
 * 清空队列 操作队列
 * @param Q
 */
void ClearQueue(Queue *Q)
{
    InitStack(&Q->stack1);
    InitStack(&Q->stack2);
}

/**
 *
 * @param Q 操作队列
 * @return 返回队列已使用长度
 */
int QueueLength(Queue Q)
{
    return StackLength(Q.stack1) + StackLength(Q.stack2);
}

/**
 * 判断队列是否为空
 * @param Q 操作队列
 * @return 如果为空返回1，否则返回0
 */
int QueueEmpty(Queue Q)
{
    //判断Q不为空指针
    if(Q!=NULL)
    {
        //判断Q长度是否为零
        if(QueueLength(Q)==0)
            return 1;
        return 0;
    }
    return -1；

}

/**
 * 入队操作，将元素插入队列，需要处理队列满的情况（队列元素数目最多为 MaxSize）
 * @param Q 操作队列
 * @param e 插入的元素
 * @return 如果插入成功返回1，否则返回0
 */
int EnQueue(Queue *Q, DataType e)
{
    /*
        认真思考，从哪个栈Push元素，时间复杂度如何？能否降低
    */
    //S2栈底为队首，S1栈底为队尾。将S1中元素都倒入S2中，再在S2栈顶（队尾）Push元素
    int a;
    //判断队列指针非空
    if(Q==NULL)
    {
        return 0;
    }
    //倒空S1进S2
    while(!StackEmpty(Q->stack1))
    {
        Pop(&(Q->stack1),&a);
        Push(&(Q->stack2),a);//注意
    }
    //判断S2不满
    if(StackLength(Q->stack2)!=MaxSize)
    {
        //将数据元素加入队尾（s2栈顶）
        Push(&(Q->stack2),e);
        return 1;
    }
    return 0;
}

/**
 * 出队操作，从队列中取出一个元素
 * @param Q 操作队列
 * @param e 接受出队元素
 * @return 如果成功取出返回1，否则返回0
 */
int DeQueue(Queue *Q, DataType *e)
{
    /*
        认真思考，从哪个栈Pop元素，时间复杂度如何？能否降低
    */
    //S2栈底为队首，S1栈底为队尾。将S2中元素都倒入S1中，再在S2栈顶（队首）Pop元素
    int a;
    //判断Q不为空指针
    if(Q==NULL)
    {
        return 0;
    }
    //判断队列非空
    if(QueueEmpty(*Q))
        return 0;
    //将S2中元素都倒入S1中
    while(!StackEmpty(Q->stack2))
    {
        Pop(&(Q->stack2),&a);
        Push(&(Q->stack1),a);//注意
    }
    //将S1栈顶（队首）元素Pop
    Pop(&(Q->stack1),&a);
    (*e)=a;
    return 1;
}

/**
 * 获取队列头（不删除元素）
 * @param Q 操作队列
 * @param e 接受队列头元素
 * @return 如果成功获取返回1，否则返回0
 */
int GetHead(Queue Q, DataType *e)
{
    int a;
    //判断Q指针存在且非空
    if(Q==NULL)
        return 0;
    if (QueueEmpty(Q))
        {return 0;}
    //清空栈2，使数据都进入栈1，S1栈顶及队首，对其进行操作
    while(!StackEmpty(Q.stack2))
    {
        Pop(&(Q.stack2),&a);
        Push(&(Q.stack1),a);//注意
    }
    //返回队首元素
    (*e) =  (Q.stack1).data[(Q.stack1).top];
    return 1;
}

/**
 * 获取队列的一个数组拷贝，顺序为从队列头到队列尾
 * @param Q 操作队列
 * @param seq 栈中元素的一个拷贝
 */
void QueueToArray(Queue Q, DataType *seq)
{

    int i=0;
    int a;
    //清空栈2进栈1
    while(!StackEmpty(Q.stack2))
    {
        Pop(&(Q.stack2),&a);

        Push(&(Q.stack1),a);//注意
    }

    //栈1不为空时，依次Pop栈1元素，存入数组，再Push进栈2存储
    while(StackLength(Q.stack1)!=0)
    {
        Pop(&(Q.stack1),&a);
        seq[i++] = a;
        Push(&(Q.stack2),a);
    }
}
