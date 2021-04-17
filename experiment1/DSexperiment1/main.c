#include "Function.h"
#include "Robust.h"

/**系统操作窗口*/
int main()
{
    /*变量声明*/
    int stu1,stu2;//班级人数
    int beforeCross1, beforeCross2;
    Head class1=NULL;
    Head class2=NULL;
    Position node;
    int Order;

    /*热情欢迎*/
    printf("Welcome to the Score Entry System!\n");
    printf("The milky tea tastes good!!!\n");

    /*流程指引*/

    //Step1:数据录入
    printf("First,please input the student number of the two classes(num1 num2):\n");

    //鲁棒性++
    GetInt(&stu1,&stu2);

    printf("Second,input studentname and grade(splite with space):\n");
    class1=GetClassLink(class1,stu1);
    class2=GetClassLink(class2,stu2);

    //检查
    printf("* part1:\nclass1:\n");
    outputStudentLinkedList(class1);
    printf("class2:\n");
    outputStudentLinkedList(class2);

    // 反转链表
    class1 = reverseLinkedList(class1);
    class2 = reverseLinkedList(class2);
    printf("* part2:\nclass1:\n");
    outputStudentLinkedList(class1);
    printf("class2:\n");
    outputStudentLinkedList(class2);

    printf("Wether to create the cross link?(yes:1,no:0)\n");
    GetOrder(&Order);
    if(Order==1)
    {   //生成交叉链表
        do{
            printf("Please input the num1,num2 that you want to cross in class1,class2:(num1 num2)\n");
            GetInt(&beforeCross1,&beforeCross2);
        }while(beforeCross1>stu1||beforeCross2>stu2);

        createCrossLink(class1, class2, beforeCross1, beforeCross2);

        // 打印相交结点
        node = findCrossBeginNode(class1, class2);
        printf("* part3:\n");
        printf("{ID:%s, Grade:%d}\n", node->StuID,node->Grade);

        //销毁相交链表
        destroyCrossLink(class1, class2, node);

        printf("\n");
    }
    printf("Finished!");
    return 0;
}
