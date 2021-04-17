#include <stdio.h>
#include <stdlib.h>
#include "Robust.h"


/**************************通用**************************/
Status GetInt(int *a,int *b)
{
    //合法性检测
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


/**************************独用**************************/
