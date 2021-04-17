#ifndef BinaryTree
#define BinarryTree


#include <iostream>
#include<cstring>
#include<sstream>
#include<fstream>

using namespace std;

typedef int Status;
typedef int ID;
typedef int VAL;
extern int TreeNodeId;


typedef struct TreeNode{
    ID id;
    VAL val;
    struct TreeNode *lchild,*rchild; //��������ָ��

    //���صĹ��캯��
    TreeNode(VAL theVal)
    {
        //������ʼ��
        id=TreeNodeId++;
        val=theVal;
        lchild=rchild=NULL;
    }
    TreeNode(VAL theVal,struct TreeNode *left,struct TreeNode *right)
    {
        //������ָ��ĳ�ʼ��
        id=TreeNodeId++;
        val=theVal;
        lchild=left;
        rchild=right;
    }
    TreeNode()
    {
        id=-1;
        val=-999;
        lchild=rchild=NULL;
    }

}TreeNode,*TreeNodePtr;

typedef struct QueueNode{   //���еĽ��ֵ�����������ָ��
    TreeNode *node;
    struct QueueNode *next;

    //���صĹ��캯��������ʱʵ�ֳ�ʼ��

    QueueNode(TreeNodePtr theNode,struct QueueNode* theNext)
    {
        node=theNode;
        next=theNext;

    }
}QueueNode,*QueueNodePtr;

class BinaryTree;
class Queue;

void createDotFile(char *filename,TreeNodePtr root,int MaxSize);
void plot(TreeNodePtr tree_root,int i,int _size,char *name);
void output(TreeNodePtr t);
void getDigits(char *buff,int *data);
void del(TreeNodePtr t);

class BinaryTree{
public:
    int TreeSize;
    TreeNodePtr Thead;
    BinaryTree()
    {
        TreeSize=0;
        Thead=new TreeNode();
        Thead->rchild=Thead;
    }
    ~BinaryTree()
    {
        postOrderTraverse(del);
    }

    //��ҵ��������������
    TreeNodePtr createTreeWithLevelOrder(int *data,int theTreeSize);


    //����
    void preOrderTraverse(void(*theVisit)(TreeNodePtr t))//���������ʺ�����ָ��
    {
        //���ʺ���ָ�븳ֵ
        visit=theVisit;
        //�����ع���˽�б���
        preOrderTraverse(Thead->lchild);
    }
    void inOrderTraverse(void(*theVisit)(TreeNodePtr t))
    {
        visit=theVisit;
        inOrderTraverse(Thead->lchild);
    }
    void postOrderTraverse(void(*theVisit)(TreeNodePtr t))
    {
        visit=theVisit;
        postOrderTraverse(Thead->lchild);
    }

    //���������ȡ���·����
    int maxPathSum(TreeNodePtr root);
    int maxPathSum()
    {
        return maxPathSum(Thead->lchild);
    }

    //�ݹ�������Ҷ��Ȩ�غ�
    int sumOfLeftLeaves()
    {
        return sumOfLeftLeaves(Thead->lchild);
    }

    //������

    TreeNodePtr invertTree()
    {
        return invertTree(Thead->lchild);
    }

private:
    void (*visit)(TreeNodePtr t);//���ʺ��������Ķ���
    TreeNodePtr invertTree(TreeNodePtr root);
    int sumOfLeftLeaves(TreeNodePtr root);
    void destroyTree(TreeNodePtr root)
    {
        if(!root) return;
        if(root->lchild)
        {
            destroyTree(root->lchild);
            root->lchild=NULL;
        }
        if(root->rchild)
        {
            destroyTree(root->rchild);
            root->rchild=NULL;
        }
        delete root;
    }

    //������˳��������
    void preOrderTraverse(TreeNodePtr root);
    void inOrderTraverse(TreeNodePtr root);
    void postOrderTraverse(TreeNodePtr root);
};

class Queue{
public:
    QueueNodePtr Qhead,tail;
    int QueueSize;
    //���캯����ʼ��
    Queue()
    {
        QueueSize=0;
        TreeNodePtr dummyTreeNode=new TreeNode(-1);
        Qhead=new QueueNode(dummyTreeNode,NULL);
        tail=Qhead;
    }
    //��������
    ~Queue()
    {
        while(Qhead->next!=NULL)
        {
            QueueNodePtr p;
            p=Qhead->next;
            Qhead->next=p->next;
            delete p;
        }
        delete Qhead;
    }


    //��������
    void EnQueue(TreeNodePtr t);
    void DeQueue();
    bool QueueEmpty();
    TreeNodePtr GetHead();//���ظö����е�һ��Ԫ�ص�����
};




#endif // BinaryTree
