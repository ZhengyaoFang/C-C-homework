#include <iostream>
#include<cstring>
#include<sstream>
#include<stdlib.h>
#include<fstream>

#include"BinaryTree.h"/**���������Ľ��ṹ�弴���Ͷ�����ͷ�ļ���*/

using namespace std;


int TreeNodeId=0;                       //ȫ�ֱ������������ʱ�������������һ



/**������������������������������������������������������������������������������������*/
/**||                           ���е���ز�����������                             ||
/**������������������������������������������������������������������������������������*/

/**�ڶ���β�����һ��Ԫ�صĸ���*/
void Queue::EnQueue(TreeNodePtr t)
{
    tail->next=new QueueNode(t,NULL);
    tail=tail->next;
    QueueSize++;
}

/**ɾ�������е�һ��Ԫ��*/
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

/**�������Ϊ�գ�����true*/
bool Queue::QueueEmpty()
{
    return QueueSize==0;
}

/**���ض��е�һ��Ԫ�ص�����*/
TreeNodePtr Queue::GetHead()
{
    if(QueueSize!=0)
        return Qhead->next->node;

    //������Ϊ���򱨴����ؿ�ָ��
    perror("error!the size of queue is zero when call front().");
    return NULL;
}
/**������������������������������������������������������������������������������������*/
/**||                           ����������ز�����������                           ||
/**������������������������������������������������������������������������������������*/


/** TODO:  ����һ��ͨ��������ʵ�ֲ�α�������������*/
TreeNodePtr BinaryTree::createTreeWithLevelOrder(int *data,int theTreeSize)
{
    int i=1;
    //�����Ϊ�ջ��һ�����ڵ�Ϊ���򷵻ؿ�ָ��
    if(theTreeSize==0||data[0]==-1)
        return NULL;

    Queue Q = Queue();
    TreeNodePtr firstTnode,newTnode;            //ָ�����ͷ������������¶��������

    Thead->lchild=new TreeNode(data[0]);
    Q.EnQueue(Thead->lchild);                   //��ʼ�����ڵ���ӣ���ʼѭ��


    for(i=1;i<theTreeSize;i++)                  //��data������ÿ�ε���i+2���ӳ�һ��ͷ��㣬��ֵ�����ӽڵ㲢��ӣ�����Ϊ�գ�
    {
        firstTnode=Q.GetHead();


        if(!Q.QueueEmpty()&&firstTnode==NULL)                    //�����ӵĽ��Ϊ�գ�����Ӧλ�õ��ӽڵ��Ϊ�գ�
        {
            i=i+1;                              //��ӳ�һ���ս�㣬��������ս�㣬������һ����
            Q.DeQueue();
            Q.EnQueue(NULL);
            Q.EnQueue(NULL);
            continue;
        }


        if(!Q.QueueEmpty()&&i<theTreeSize&&data[i]!=-1)                         //��ͷ��㲻Ϊ�գ������жϲ�������Χ�����������δ�data��˳��ȡ����ֵ��
        {

            newTnode = new TreeNode(data[i]);   //����Ϊ-1�򴴽������������ӡ�����ֱ����ӿ�ָ��
            firstTnode->lchild=newTnode;
            Q.EnQueue(newTnode);
        }
        else
        {
            Q.EnQueue(NULL);
        }


        if(!Q.QueueEmpty()&&++i<theTreeSize&&data[i]!=-1)        //���Һ��ӽ����жϣ�����������Χ��
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
 *  ||                   ǰ�����                     ||
 * =====================================================
 */
 void BinaryTree::preOrderTraverse(TreeNodePtr root)
 {
     if(root!=NULL)
     {
         visit(root);                                   //visit��BinaryTree�����е�˽�к���ָ��������ڵ��ñ�������ʱ
         preOrderTraverse(root->lchild);                //�����ʺ���ָ����Ϊ�����������صĹ������������У��ڸù�������
         preOrderTraverse(root->rchild);                //�ж�˽��visit������ֵ�����øõݹ����͵����صı�������
     }

 }

/**
 * =====================================================
 *  ||                   �������                     ||
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
 *  ||                   �������                     ||
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



 /** TODO: �������������ȱ�����ȡ�����������·����*/
 int BinaryTree::maxPathSum(TreeNodePtr root)
 {
     if(!root)
        return 0;           //��rootΪ���򷵻�0
     return root->val+max(maxPathSum(root->lchild),maxPathSum(root->rchild));       //���ص�ǰ���Ȩֵ�����������ϴ�Ȩֵ֮��
 }

 /** TODO: ��������ͨ���ݹ���ȡ�ö���������������ҶȨ��֮��*/
 int BinaryTree::sumOfLeftLeaves(TreeNodePtr root)
 {
     if(!root)
        return 0;       //��rootΪ���򷵻�0
     if(root->lchild!=NULL&&root->lchild->lchild==NULL&&root->lchild->rchild==NULL) //�����ǰ����������Ҷ�ӽڵ�
     {
         return root->lchild->val+sumOfLeftLeaves(root->rchild);                    //�򷵻�����Ȩֵ��������������ҶȨ�غ�֮��
     }
     return sumOfLeftLeaves(root->lchild)+sumOfLeftLeaves(root->rchild);            //���򷵻�������������������Ҷ��Ȩ��֮��
 }


 /** TODO: �����ģ�ͨ���ݹ���ȡ�����ľ���*/
 TreeNodePtr BinaryTree::invertTree(TreeNodePtr root)
 {
     if(root!=NULL)                                 //��root��Ϊ����
     {
         TreeNodePtr temp;
         temp=root->lchild;
         root->lchild=invertTree(root->lchild);     //�������������ֱ�ȡ����
         root->rchild=invertTree(root->rchild);
         root->lchild=root->rchild;                 //������ǰ������������
         root->rchild=temp;
     }
     return root;

 }

/**������������������������������������������������������������������������������������*/
/**||                                  ���ӻ�                                     ||
/**������������������������������������������������������������������������������������*/
/**����dot���ӻ��ļ�*/
void createDotFile(char *filename,TreeNodePtr root,int MaxSize)
{
    ofstream fp(filename);   //�ļ�ָ��
    if(!fp.is_open())
    {
        cout<<"File cannot open!"<<endl;
        exit(0);
    }
    fp<<"digraph G {\n"<<endl; //��ͷ
    //���ò�α�������
    Queue Q=Queue();
    Q.EnQueue(root);
    int id=1;
    while(!Q.QueueEmpty()){
        TreeNodePtr curr = Q.GetHead();
        Q.DeQueue();
        if(curr==NULL) continue;
        fp<<curr->id<<" [shape=circle,label=\""<<curr->val<<"\"];\n"<<endl;
        if(curr->lchild!=NULL){//��������ӣ��������
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
    fp<<"}\n"<<endl;//��β
    fp.close();
}

/**���ƶ�����ͼƬ*/
void plot(TreeNodePtr tree_root,int i,int _size,char *name)
{
    char tree_filename[50],paint_tree[100];
    sprintf(tree_filename, "./%s_%d.dot", name, i);
    createDotFile(tree_filename, tree_root, _size);
    sprintf(paint_tree, "dot -Tpng %s -o ./%s_%d.png", tree_filename, name, i);
    // puts(paint_tree);
    system(paint_tree);

}

/**������������������������������������������������������������������������������������*/
/**||                                  visit���ʺ���                              ||
/**������������������������������������������������������������������������������������*/
/**�Ե�ǰ����ӡ���*/
void output(TreeNodePtr t)
{
    if(t==NULL)
        return;
    printf("%d ",t->val);
}
/**ɾ����ǰ���*/
void del(TreeNodePtr t)
{
    if(t!=NULL)
        delete t;
}

/**������������������������������������������������������������������������������������*/
/**||                                  ��������                                   ||
/**������������������������������������������������������������������������������������*/

/**������ת��Ϊ����*/
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
            i++;        //��Ϊ�пո���������1
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
