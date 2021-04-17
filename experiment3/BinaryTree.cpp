#include <iostream>
#include<cstring>
#include<sstream>
#include<stdlib.h>
#include<fstream>

#include"BinaryTree.h"/**队列与树的结点结构体即类型定义于头文件中*/

using namespace std;


int TreeNodeId=0;                       //全局变量，创建结点时赋予结点次序并自增一



/**——————————————————————————————————————————*/
/**||                           队列的相关操作函数定义                             ||
/**——————————————————————————————————————————*/

/**在队列尾部添加一个元素的副本*/
void Queue::EnQueue(TreeNodePtr t)
{
    tail->next=new QueueNode(t,NULL);
    tail=tail->next;
    QueueSize++;
}

/**删除队列中第一个元素*/
void Queue::DeQueue()
{
    if(QueueSize==0){
        perror("error! the size of queue is zero when call DeQueue().");
        return;
    }
    QueueNodePtr p=Qhead->next;
    Qhead->next=p->next;
    QueueSize--;
    delete p;
}

/**如果队列为空，返回true*/
bool Queue::QueueEmpty()
{
    return QueueSize==0;
}

/**返回队列第一个元素的引用*/
TreeNodePtr Queue::GetHead()
{
    if(QueueSize!=0)
        return Qhead->next->node;

    //若队列为空则报错并返回空指针
    perror("error!the size of queue is zero when call front().");
    return NULL;
}
/**——————————————————————————————————————————*/
/**||                           二叉树的相关操作函数定义                           ||
/**——————————————————————————————————————————*/


/** TODO:  任务一：通过队列来实现层次遍历构建二叉树*/
TreeNodePtr BinaryTree::createTreeWithLevelOrder(int *data,int theTreeSize)
{
    int i=1;
    //如果树为空或第一个根节点为空则返回空指针
    if(theTreeSize==0||data[0]==-1)
        return NULL;

    Queue Q = Queue();
    TreeNodePtr firstTnode,newTnode;            //指向队列头结点树，创建新对象的引用

    Thead->lchild=new TreeNode(data[0]);
    Q.EnQueue(Thead->lchild);                   //初始化根节点入队，开始循环


    for(i=1;i<theTreeSize;i++)                  //对data迭代，每次迭代i+2，队出一个头结点，赋值两个子节点并入队（可能为空）
    {
        firstTnode=Q.GetHead();


        if(!Q.QueueEmpty()&&firstTnode==NULL)                    //若出队的结点为空，则相应位置的子节点必为空，
        {
            i=i+1;                              //则队出一个空结点，入队两个空结点，进入下一进程
            Q.DeQueue();
            Q.EnQueue(NULL);
            Q.EnQueue(NULL);
            continue;
        }


        if(!Q.QueueEmpty()&&i<theTreeSize&&data[i]!=-1)                         //若头结点不为空，则在判断不超出范围的条件下依次从data中顺序取两个值，
        {

            newTnode = new TreeNode(data[i]);   //若不为-1则创建结点加入树、队。否则直接入队空指针
            firstTnode->lchild=newTnode;
            Q.EnQueue(newTnode);
        }
        else
        {
            Q.EnQueue(NULL);
        }


        if(!Q.QueueEmpty()&&++i<theTreeSize&&data[i]!=-1)        //对右孩子结点的判断（若不超出范围）
        {

            newTnode=new TreeNode(data[i]);
            firstTnode->rchild=newTnode;
            Q.EnQueue(newTnode);
        }
        else{Q.EnQueue(NULL);}
        Q.DeQueue();
    }
    return Thead->lchild;
}
/**
 * =====================================================
 *  ||                   前序遍历                     ||
 * =====================================================
 */
 void BinaryTree::preOrderTraverse(TreeNodePtr root)
 {
     if(root!=NULL)
     {
         visit(root);                                   //visit是BinaryTree类型中的私有函数指针变量，在调用遍历函数时
         preOrderTraverse(root->lchild);                //将访问函数指针作为参数传入重载的公共遍历函数中，在该公共函数
         preOrderTraverse(root->rchild);                //中对私有visit变量赋值并调用该递归类型的重载的遍历函数
     }

 }

/**
 * =====================================================
 *  ||                   中序遍历                     ||
 * =====================================================
 */
 void BinaryTree::inOrderTraverse(TreeNodePtr root)
 {
     if(root)
     {
         inOrderTraverse(root->lchild);
         visit(root);
         inOrderTraverse(root->rchild);
     }
 }
 /**
 * =====================================================
 *  ||                   后序遍历                     ||
 * =====================================================
 */
 void BinaryTree::postOrderTraverse(TreeNodePtr root)
 {
     if(root)
     {
         postOrderTraverse(root->lchild);
         postOrderTraverse(root->rchild);
         visit(root);
     }
 }



 /** TODO: 任务二：深度优先遍历求取二叉树的最大路径和*/
 int BinaryTree::maxPathSum(TreeNodePtr root)
 {
     if(!root)
        return 0;           //若root为空则返回0
     return root->val+max(maxPathSum(root->lchild),maxPathSum(root->rchild));       //返回当前结点权值及左右子树较大权值之和
 }

 /** TODO: 任务三：通过递归求取该二叉树的所有左子叶权重之和*/
 int BinaryTree::sumOfLeftLeaves(TreeNodePtr root)
 {
     if(!root)
        return 0;       //若root为空则返回0
     if(root->lchild!=NULL&&root->lchild->lchild==NULL&&root->lchild->rchild==NULL) //如果当前结点的左孩子是叶子节点
     {
         return root->lchild->val+sumOfLeftLeaves(root->rchild);                    //则返回左孩子权值和右子树的左子叶权重和之和
     }
     return sumOfLeftLeaves(root->lchild)+sumOfLeftLeaves(root->rchild);            //否则返回左子树和右子树的左叶子权重之和
 }


 /** TODO: 任务四：通过递归求取该树的镜像*/
 TreeNodePtr BinaryTree::invertTree(TreeNodePtr root)
 {
     if(root!=NULL)                                 //若root不为空则
     {
         TreeNodePtr temp;
         temp=root->lchild;
         root->lchild=invertTree(root->lchild);     //对其左、右子树分别取镜像
         root->rchild=invertTree(root->rchild);
         root->lchild=root->rchild;                 //交换当前结点的左右子树
         root->rchild=temp;
     }
     return root;

 }

/**——————————————————————————————————————————*/
/**||                                  可视化                                     ||
/**——————————————————————————————————————————*/
/**创建dot可视化文件*/
void createDotFile(char *filename,TreeNodePtr root,int MaxSize)
{
    ofstream fp(filename);   //文件指针
    if(!fp.is_open())
    {
        cout<<"File cannot open!"<<endl;
        exit(0);
    }
    fp<<"digraph G {\n"<<endl; //开头
    //利用层次遍历构造
    Queue Q=Queue();
    Q.EnQueue(root);
    int id=1;
    while(!Q.QueueEmpty()){
        TreeNodePtr curr = Q.GetHead();
        Q.DeQueue();
        if(curr==NULL) continue;
        fp<<curr->id<<" [shape=circle,label=\""<<curr->val<<"\"];\n"<<endl;
        if(curr->lchild!=NULL){//如果有左孩子，左孩子入队
            Q.EnQueue(curr->lchild);
            fp<<curr->id<<"->"<<curr->lchild->id<<";\n"<<endl;
        }
        id++;
        fp<<"_n"<<id<<" [shape=circle, label=\"#\", style=invis];\n"<<endl;
        fp<<curr->id<<"->_n"<<id<<" [style=invis, weight=10];\n"<<endl;
        if(curr->rchild!=NULL)
        {
            Q.EnQueue(curr->rchild);
            fp<<curr->id<<"->"<<curr->rchild->id<<";\n"<<endl;
        }
        id++;

    }
    fp<<"}\n"<<endl;//结尾
    fp.close();
}

/**绘制二叉树图片*/
void plot(TreeNodePtr tree_root,int i,int _size,char *name)
{
    char tree_filename[50],paint_tree[100];
    sprintf(tree_filename, "./%s_%d.dot", name, i);
    createDotFile(tree_filename, tree_root, _size);
    sprintf(paint_tree, "dot -Tpng %s -o ./%s_%d.png", tree_filename, name, i);
    // puts(paint_tree);
    system(paint_tree);

}

/**——————————————————————————————————————————*/
/**||                                  visit访问函数                              ||
/**——————————————————————————————————————————*/
/**对当前结点打印输出*/
void output(TreeNodePtr t)
{
    if(t==NULL)
        return;
    printf("%d ",t->val);
}
/**删除当前结点*/
void del(TreeNodePtr t)
{
    if(t!=NULL)
        delete t;
}

/**——————————————————————————————————————————*/
/**||                                  辅助函数                                   ||
/**——————————————————————————————————————————*/

/**将输入转换为数组*/
void getDigits(char *buff,int *data)
{
    int len=strlen(buff);
    int index=0;
    for(int i=0;i<len;i++)
    {
        int num=0;
        if(buff[i]=='#')
        {
            num=-1;
            i++;        //因为有空格所以自增1
        }
        else
        {
            while(buff[i]!=' '&&buff[i]!='\0')
            {
                num=num*10 +(buff[i++]-'0');
            }
        }
        data[index++]=num;
    }
}
