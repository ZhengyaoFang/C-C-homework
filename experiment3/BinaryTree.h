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
    struct TreeNode *lchild,*rchild; //左右子树指针

    //重载的构造函数
    TreeNode(VAL theVal)
    {
        //变量初始化
        id=TreeNodeId++;
        val=theVal;
        lchild=rchild=NULL;
    }
    TreeNode(VAL theVal,struct TreeNode *left,struct TreeNode *right)
    {
        //变量与指针的初始化
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

typedef struct QueueNode{   //队列的结点值类型是树结点指针
    TreeNode *node;
    struct QueueNode *next;

    //重载的构造函数在声明时实现初始化

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

    //作业中任务函数的声明
    TreeNodePtr createTreeWithLevelOrder(int *data,int theTreeSize);


    //遍历
    void preOrderTraverse(void(*theVisit)(TreeNodePtr t))//参数：访问函数的指针
    {
        //访问函数指针赋值
        visit=theVisit;
        //调用重构的私有遍历
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

    //深度优先求取最大路径和
    int maxPathSum(TreeNodePtr root);
    int maxPathSum()
    {
        return maxPathSum(Thead->lchild);
    }

    //递归求左子叶的权重和
    int sumOfLeftLeaves()
    {
        return sumOfLeftLeaves(Thead->lchild);
    }

    //求镜像树

    TreeNodePtr invertTree()
    {
        return invertTree(Thead->lchild);
    }

private:
    void (*visit)(TreeNodePtr t);//访问函数变量的定义
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

    //遍历的顺序函数声明
    void preOrderTraverse(TreeNodePtr root);
    void inOrderTraverse(TreeNodePtr root);
    void postOrderTraverse(TreeNodePtr root);
};

class Queue{
public:
    QueueNodePtr Qhead,tail;
    int QueueSize;
    //构造函数初始化
    Queue()
    {
        QueueSize=0;
        TreeNodePtr dummyTreeNode=new TreeNode(-1);
        Qhead=new QueueNode(dummyTreeNode,NULL);
        tail=Qhead;
    }
    //析构函数
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


    //函数声明
    void EnQueue(TreeNodePtr t);
    void DeQueue();
    bool QueueEmpty();
    TreeNodePtr GetHead();//返回该队列中第一个元素的引用
};




#endif // BinaryTree
