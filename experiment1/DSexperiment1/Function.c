#include "Function.h"


/* �����ཻ���� */
void createCrossLink(StudentLinkedListNode* a, StudentLinkedListNode* b, int beforeCross1, int beforeCross2){
    // a��b�������ɽ��ֵ��ͬ
    // beforeCross1Ϊ������a�еĸ������ӵ�beforeCross1 + 1����㿪ʼ�ཻ
    // beforeCross2Ϊ������b�еĸ������ӵ�beforeCross2 + 1����㿪ʼ�ཻ
    // �ཻ�����ǽ�b�е�ǰһ���ָ��a�е��׸��ཻ���
    StudentLinkedListNode *p, *q;
    while(beforeCross1--)a=a->next;
    while(--beforeCross2)b=b->next;
    p = b->next;
    b->next = a;
    //����Ұָ����
    while(p){
        q = p->next;
        free(p);
        p = q;
    }
}

/*���ٽ�������*/
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

/* ��ӡ�����ڵ� */
void printLinkedListNode(StudentLinkedListNode * node){
    printf("{ID:%s, Grade:%d}", node->StuID, node->Grade);
    if(node->next!=NULL){
        printf("->");
    }else{
        printf("\n");
    }

}


/** ����ñ�ĳɼ���� */
void outputStudentLinkedList(StudentLinkedListNode* head){
	while(head!=NULL)
    {
        printLinkedListNode(head);
        head = head->next;
    }//����ÿ���ڵ㣬��Ϊ�������
}


/** �½�һ������node������ */
StudentLinkedListNode* studentLinkedListCreate(char student_id[], int grade) {
	StudentLinkedListNode *p = NULL;

	//���붯̬�ڴ�
	p = (StudentLinkedListNode*)malloc(sizeof(StudentLinkedListNode));

	//��ʼ����ֵ
	strcpy(p->StuID, student_id);
	p->Grade = grade;
	p->next = NULL;
	return p;
}


/** ���ս������ѧ���ĳɼ����,����������ͷָ�� */
Head studentLinkedListAdd(StudentLinkedListNode* head, StudentLinkedListNode* node) {

	//ͷ�巨
	node->next=head;
	return node;
}


/** ��ת���� */
Head reverseLinkedList(StudentLinkedListNode*head){

	//�����������ͷ
	Head newhead=NULL;
	Position q=NULL;

	//һ�α���������ͷ�巨�����������õ���ת����
	while(head!=NULL)//
    {
        q=head;
        head=head->next;
        newhead = studentLinkedListAdd(newhead,q);//ͷ�巨
    }
    return newhead;
}




/** �ҵ��ཻ�ĵ�һ����� */
Position findCrossBeginNode(StudentLinkedListNode* class1, StudentLinkedListNode* class2) {
	Position p=NULL;
	Position q=NULL;

	int i,j,counter;//i,j�ֱ����������ĳ���

	//�ֱ����һ�Σ��õ�����ĳ��ȡ����������ڷ���-1��
	i = LinkLen(class1);
	j = LinkLen(class2);

	//�ж��Ƿ�Ϊ�ձ����򱨴����ؿ�ָ��
	if(i==-1||j==-1)
    {
        printf("Error!The link doesn't exit!");
        return NULL;
    }

	//pָ��ϳ���qָ��϶�
	p = (i > j) ? class1 : class2;
	q = (i > j) ? class2 : class1;

	//����ָ��˼�룬ʹָ���������㡰���롱
	for (counter = 0; counter < abs(i - j); counter++)
	{
	    if(p!=NULL)//³����++
            p = p->next;
	}

	//�����룬��һ�α���ֱ����ַ��ȣ�����
	while (p&&q&&p != q)    //��ֹ�޽�����ʱ����³����++
	{
		p = p->next;
		q = q->next;
	}

    return q;//��û�н�����ʱ���ؿ�ָ��

}

/**�ж�������*/
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

/****************************�����װ����**************************************/
//�洢������������Ϸ��ļ��
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

