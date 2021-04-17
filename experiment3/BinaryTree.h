#ifndef BinaryTree
#define BinarryTree


#include <iostream>
#include<cstring>
#include<sstream>
#include<fstream>

using namespace std;

/**——————————————类型的重命名及全局变量的声明———————————————*/
typedef int Status;
typedef int ID;
typedef int VAL;
extern int TreeNodeId;          //extern防止重定义



/**====================================================================
*  ||                                                                ||
*  ||                         结点的结构体定义                       ||
*  ||                                                                ||
**====================================================================*/

/**树结点结构体定义*/
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
    TreeNode()//用于创建空树时设置头结点
    {
        id=-1;
        val=-999;
        lchild=rchild=NULL;
    }

}TreeNode,*TreeNodePtr;

/**队列结点的结构体定义*/
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

/**————————————————辅助函数的声明————————————————————*/
void createDotFile(char *filename,TreeNodePtr root,int MaxSize);        //可视化写dot文件
void plot(TreeNodePtr tree_root,int i,int _size,char *name);           //调用dot文件
void getDigits(char *buff,int *data);                                   //输入字符串转为数组
void output(TreeNodePtr t);                                             //visit访问函数1：输出结点信息
void del(TreeNodePtr t);                                                //visit访问函数2：删除节点释放空间

/**====================================================================
*  ||                                                                ||
*  ||                         队列与树类的定义                       ||
*  ||                                                                ||
**====================================================================*/
class BinaryTree;
class Queue;


/**——————————————树的类的定义——————————————*/
class BinaryTree{
public:

    //变量定义
    int TreeSize;
    TreeNodePtr Thead;

    //构造函数，创建对象时初始化头结点，
    BinaryTree()
    {
        TreeSize=0;
        Thead=new TreeNode();
        Thead->rchild=Thead;
    }

    //析构函数，销毁树
    ~BinaryTree()
    {
        postOrderTraverse(del);     //后序遍历树，访问方法del为删除该结点
    }

    //——————————————作业中任务函数的声明——————————//
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
    int maxPathSum(TreeNodePtr root);

    //销毁树，因有析构函数而无必要
    /**void destroyTree(TreeNodePtr root)
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
    }*/

    //重载的遍历的顺序函数声明（用于递归）
    void preOrderTraverse(TreeNodePtr root);
    void inOrderTraverse(TreeNodePtr root);
    void postOrderTraverse(TreeNodePtr root);
};


/**————————————队列类型的定义————————————————*/
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
