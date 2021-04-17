#include "Function.h"


/* 创建相交链表 */
void createCrossLink(StudentLinkedListNode* a, StudentLinkedListNode* b, int beforeCross1, int beforeCross2){
    // a和b后面若干结点值相同
    // beforeCross1为跳过的a中的个数，从第beforeCross1 + 1个结点开始相交
    // beforeCross2为跳过的b中的个数，从第beforeCross2 + 1个结点开始相交
    // 相交方法是将b中的前一结点指向a中的首个相交结点
    StudentLinkedListNode *p, *q;
    while(beforeCross1--)a=a->next;
    while(--beforeCross2)b=b->next;
    p = b->next;
    b->next = a;
    //销毁野指针结点
    while(p){
        q = p->next;
        free(p);
        p = q;
    }
}

/*销毁交叉链表*/
void destroyCrossLink(StudentLinkedListNode* a, StudentLinkedListNode* b, StudentLinkedListNode* crossNode){
    StudentLinkedListNode* p = crossNode->next, *q;
    while(p){
        q = p->next;
        free(p);
        p = q;
    }
    while(a != crossNode){
        q = a->next;
        free(a);
        a = q;
    }
    while(b != crossNode){
        q = b->next;
        free(b);
        b = q;
    }
    free(crossNode);
}

/* 打印单个节点 */
void printLinkedListNode(StudentLinkedListNode * node){
    printf("{ID:%s, Grade:%d}", node->StuID, node->Grade);
    if(node->next!=NULL){
        printf("->");
    }else{
        printf("\n");
    }

}


/** 输出该表的成绩情况 */
void outputStudentLinkedList(StudentLinkedListNode* head){
	while(head!=NULL)
    {
        printLinkedListNode(head);
        head = head->next;
    }//遍历每个节点，不为空则输出
}


/** 新建一个链表node并返回 */
StudentLinkedListNode* studentLinkedListCreate(char student_id[], int grade) {
	StudentLinkedListNode *p = NULL;

	//申请动态内存
	p = (StudentLinkedListNode*)malloc(sizeof(StudentLinkedListNode));

	//初始化赋值
	strcpy(p->StuID, student_id);
	p->Grade = grade;
	p->next = NULL;
	return p;
}


/** 按照降序插入学生的成绩情况,并返回链表头指针 */
Head studentLinkedListAdd(StudentLinkedListNode* head, StudentLinkedListNode* node) {

	//头插法
	node->next=head;
	return node;
}


/** 反转链表 */
Head reverseLinkedList(StudentLinkedListNode*head){

	//声明新链表表头
	Head newhead=NULL;
	Position q=NULL;

	//一次遍历旧链表，头插法插入新链表，得到反转链表
	while(head!=NULL)//
    {
        q=head;
        head=head->next;
        newhead = studentLinkedListAdd(newhead,q);//头插法
    }
    return newhead;
}




/** 找到相交的第一个结点 */
Position findCrossBeginNode(StudentLinkedListNode* class1, StudentLinkedListNode* class2) {
	Position p=NULL;
	Position q=NULL;

	int i,j,counter;//i,j分别接受两链表的长度

	//分别遍历一次，得到链表的长度。若链表不存在返回-1；
	i = LinkLen(class1);
	j = LinkLen(class2);

	//判断是否为空表，是则报错并返回空指针
	if(i==-1||j==-1)
    {
        printf("Error!The link doesn't exit!");
        return NULL;
    }

	//p指向较长，q指向较短
	p = (i > j) ? class1 : class2;
	q = (i > j) ? class2 : class1;

	//快慢指针思想，使指针遍历的起点“对齐”
	for (counter = 0; counter < abs(i - j); counter++)
	{
	    if(p!=NULL)//鲁棒性++
            p = p->next;
	}

	//起点对齐，再一次遍历直至地址相等，返回
	while (p&&q&&p != q)    //防止无交叉结点时报错，鲁棒性++
	{
		p = p->next;
		q = q->next;
	}

    return q;//当没有交叉结点时返回空指针

}

/**判断链表长度*/
int LinkLen(StudentLinkedListNode *head)
{
	int i = 0;
	StudentLinkedListNode *p=head;
	if (head == NULL)
	{
		return -1;
	}
	while (p->next != NULL)
	{
		i++;
		p = p->next;
	}
	return i;
}

/****************************程序封装函数**************************************/
//存储链表并进行输入合法的检测
Head GetClassLink(Head class,int stu)
{

    int i,grade;
    char student_id[11];
    Head node;
    for(i=0;i<stu;i++)
    {
        while(scanf("%s%d", student_id, &grade)!=2||grade<=0||grade>100)
        {
            printf("Error!Please input again:");
            while(getchar()!='\n');
        }
        node = studentLinkedListCreate(student_id, grade);
        class = studentLinkedListAdd(class, node);
    }
    return class;
}

