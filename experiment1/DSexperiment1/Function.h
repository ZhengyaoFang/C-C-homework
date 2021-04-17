#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

/*��ǿ����Ŀɶ��ԣ�Head����ͷָ�룬Position����ĳ���*/
#define Position StudentLinkedListNode*
#define Head StudentLinkedListNode*

//���ṹ�嶨��
typedef struct node{
    char StuID[11];
    int Grade;
    struct node *next;
}StudentLinkedListNode;

//��������
int LinkLen(StudentLinkedListNode *head);
void createCrossLink(StudentLinkedListNode* a, StudentLinkedListNode* b, int beforeCross1, int beforeCross2);
void destroyCrossLink(StudentLinkedListNode* a, StudentLinkedListNode* b, StudentLinkedListNode* crossNode);
void printLinkedListNode(StudentLinkedListNode * node);
void outputStudentLinkedList(StudentLinkedListNode* head);
StudentLinkedListNode* studentLinkedListCreate(char student_id[], int grade);
Head studentLinkedListAdd(StudentLinkedListNode* head, StudentLinkedListNode* node);
Head reverseLinkedList(StudentLinkedListNode*head);
Position findCrossBeginNode(StudentLinkedListNode* class1, StudentLinkedListNode* class2);
int LinkLen(StudentLinkedListNode *head);
Head GetClassLink(Head class,int stu);
