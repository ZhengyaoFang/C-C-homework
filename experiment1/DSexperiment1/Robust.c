#include <stdio.h>
#include <stdlib.h>
#include "Robust.h"


/**************************ͨ��**************************/
Status GetInt(int *a,int *b)
{
    //�Ϸ��Լ��
    while((scanf("%d%d",a,b))!=2||(*a)<=0||(*b)<=0)
    {
        printf("Error!Please input again:");
        while(getchar()!='\n');
    }
    return OK;
}

Status GetOrder(int *a)
{
    while((scanf("%d",a))!=1||(*a)<0||(*a)>1)
    {
        printf("Error!Please input again:");
        while(getchar()!='\n');
    }
    return OK;
}


/**************************����**************************/
