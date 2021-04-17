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

    //����ļ����Ƿ�ɹ�
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
            char *nextline = strchr(buff, '\n');     //���һ��з�
            if (nextline)                            //���find��Ϊ��ָ��
                *nextline = '\0';                    //�Ͱ�һ�����ַ���������
            nextline = strchr(buff, '\r');           //���һس���
            if (nextline)                            //���find��Ϊ��ָ��
                *nextline = '\0';                    //�Ͱ�һ�����ַ���������
            printf("Case %d, data: %s, nodes number: %s", i, buff, num);
            int _size = atoi(num);
            int data[_size];
            getDigits(buff, data);
            /**
             * ===============================================================
             * ||       ��������������Ȼ��Ҳ���������ⷽʽ�޸ĺ�����ԭ��          ||
             * ===============================================================
             */
             //��������������
            BinaryTree T = BinaryTree();

            /** ����һ */
            T.createTreeWithLevelOrder(data,_size);
            printf("\nAnswer for task 1 is: \n");
            printf("preOrderTraverse is:");
            T.preOrderTraverse(output);     //����visit����ָ����Ϊ���ʺ���
            printf("\n");
            printf("inOrderTraverse is:");
            T.inOrderTraverse(output);
            printf("\n");
            printf("postOrderTraverse is:");
            T.postOrderTraverse(output);
            printf("\n");

            /** ͨ�� graphviz ���ӻ�����ɾ�����̲���ʹ�� */
            if (use_graphviz) {
                plot(T.Thead->lchild, i, _size, "tree");
            }

            /** ����� */
            int max_path_sum = T.maxPathSum();
            printf("Answer for task 2 is : %d \n", max_path_sum);

            /** ������ */
            int weight_sum = T.sumOfLeftLeaves();
            printf("Answer for task 3 is : %d \n", weight_sum);

            /** ������ */
            TreeNodePtr invert_tree_root ;
            invert_tree_root = T.invertTree();
            printf("inOrderTraverse for task 4 is:");
            T.inOrderTraverse(output);
            printf("\n\n");

            /** ͨ�� graphviz ���ӻ�����ɾ�����̲���ʹ�� */
            if (use_graphviz) {
                plot(invert_tree_root, i, _size, "invert_tree");
            }

            //T����������ʱ�������������Զ�����
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
