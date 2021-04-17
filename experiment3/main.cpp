#include <iostream>
#include"BinaryTree.h"
#include<fstream>

int main()
{
    int SIZE = 128;
    int MAX_NUM = 10;
    char buff[SIZE];
    char num[MAX_NUM];
    bool use_graphviz = false;

    /**
     * ===============================================================
     * ||                   End Configuration                       ||
     * ===============================================================
     */

    // printf("Read data...\n");
    ifstream fp("./test.txt");

    //检查文件打开是否成功
    if(!fp.is_open()){
        perror("error!fail to open the file.");
        return -1;
    }
    else{
        int i=0;
        // printf("success!\n");
        /**
         * ===============================================================
         * ||                   Read data here                          ||
         * ===============================================================
         */
        while (fp.getline(num, MAX_NUM) && fp.getline(buff, SIZE)) {
            char *nextline = strchr(buff, '\n');     //查找换行符
            if (nextline)                            //如果find不为空指针
                *nextline = '\0';                    //就把一个空字符放在这里
            nextline = strchr(buff, '\r');           //查找回车符
            if (nextline)                            //如果find不为空指针
                *nextline = '\0';                    //就把一个空字符放在这里
            printf("Case %d, data: %s, nodes number: %s", i, buff, num);
            int _size = atoi(num);
            int data[_size];
            getDigits(buff, data);
            /**
             * ===============================================================
             * ||       你的任务在这里，当然你也可以以任意方式修改函数的原型          ||
             * ===============================================================
             */
             //创建二叉树对象
            BinaryTree T = BinaryTree();

            /** 任务一 */
            T.createTreeWithLevelOrder(data,_size);
            printf("\nAnswer for task 1 is: \n");
            printf("preOrderTraverse is:");
            T.preOrderTraverse(output);     //传入visit函数指针作为访问函数
            printf("\n");
            printf("inOrderTraverse is:");
            T.inOrderTraverse(output);
            printf("\n");
            printf("postOrderTraverse is:");
            T.postOrderTraverse(output);
            printf("\n");

            /** 通过 graphviz 可视化，勿删，助教测试使用 */
            if (use_graphviz) {
                plot(T.Thead->lchild, i, _size, "tree");
            }

            /** 任务二 */
            int max_path_sum = T.maxPathSum();
            printf("Answer for task 2 is : %d \n", max_path_sum);

            /** 任务三 */
            int weight_sum = T.sumOfLeftLeaves();
            printf("Answer for task 3 is : %d \n", weight_sum);

            /** 任务四 */
            TreeNodePtr invert_tree_root ;
            invert_tree_root = T.invertTree();
            printf("inOrderTraverse for task 4 is:");
            T.inOrderTraverse(output);
            printf("\n\n");

            /** 通过 graphviz 可视化，勿删，助教测试使用 */
            if (use_graphviz) {
                plot(invert_tree_root, i, _size, "invert_tree");
            }

            //T对象在销毁时调用析构函数自动销毁
            invert_tree_root = NULL;
            i++;

        }
        /**
         * ===============================================================
         * ||                       End read                            ||
         * ===============================================================
         */
         fp.close();

        }

}
