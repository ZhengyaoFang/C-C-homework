/** =============文档说明================
*
*   本文件为题目要求算法的函数定义文件
*
*=====================================**/
#include "SortFunc.h"


/**===========================
*
*           题目一
*
*============================**/

/**
* 快排思想寻找数组的中位数
* @param n：奶牛数目，为奇数
* @param milk: 长度为n的向量，为奶牛的产奶量
* @return middle:int型，产奶量的中位数
*/
int FindMiddleMilk(int n,int milk[])
{
    //对奶牛产奶量进行快速排序
    QuickSort(0,n-1,milk);
//    for(int i=0;i<n;i++)
//        cout<<milk[i]<<endl;

    //返回有序数列的中位数
    return milk[n/2];
}


/**
*快速排序递归调用部分
*@param l: 快排区间[l,r]起点
*@param r: 快排区间[l,r]终点
*@param milk:被快排的数组
*/
void QuickSort(int l,int r,int milk[])
{
    if(l<r)//判定当l<r时对区间[l,r]进行排序
    {
        int m=FindM(l,r,milk);  //寻找中间轴枢并同时将数组进行分类
        QuickSort(l,m-1,milk);  //对轴枢两边递归进行快速排序
        QuickSort(m+1,r,milk);
    }
}


/**
*快排寻找轴枢并将小于轴枢的值放于起左边，大于轴枢的值放于其右边
*@param l: 快排区间[l,r]起点
*@param r: 快排区间[l,r]终点
*@param milk:被快排的数组
*@return l:即排好后轴枢的位置
*/
int FindM(int l,int r,int milk[])
{
    //轴枢选择最左边的元素
    int p=milk[l];

    //左右位置指针分别为数组两端向中间扫描，当左指针与右指针相遇或擦肩而过时则结束
    while(l<r)
    {
        //因为轴枢选择左边第一个，故从右端开始扫描，大于等于轴枢值略过，直至找到小于轴枢值元素
        //若两者未相遇则l赋为r所指，同时l++,准备从下一位向右进行扫描
        while(l<r&&milk[r]>=p)   r--;
        if(l<r)
            milk[l++]=milk[r];

        //左指针向右进行扫描，遇到大于等于轴枢值则r位被赋值且r--
        while(l<r&&milk[l]<p)   l++;
        if(l<r)
            milk[r--]=milk[l];
    }
    //最终循环结束时l为轴枢值所在位置
    milk[l]=p;
    return l;
}

/**
*交换值
*/
void Temp(int &a,int &b)
{
    int temp;
    temp=a;
    a=b;
    b=temp;
}



/**===========================
*
*           题目二
*
*============================**/


/**
*找到最大的k个数
*@param k:最大的数的个数
*@param n:数据元素总数
*@param arr：数据元素
*/
int *Maxk(int k,int n,int arr[])
{
    //初始对前k个数建小顶堆
    Init(k,arr);

    //对从第k+1的数到最后依次和堆顶比较，若较堆顶大则交换并PushDown
    for(int i=k;i<n;i++)
    {
        if(arr[0]<arr[i])
        {
            Temp(arr[0],arr[i]);
            PushDown(1,k,arr);
        }
    }

    //对选择出的k个最大数有序排好输出至数组前k个位置上
    for(int i=k-1;i>=1;i--)
    {
        Temp(arr[i],arr[0]);
        PushDown(1,i,arr);
    }
    return arr;
}

/**
*初始化对数组前k个数建堆
*@param k:前k个数
*@param arr：数组
*/
void Init(int k,int arr[])
{
    //从k/2到1依次进行整理
    for(int i=k/2;i>=1;i--)
    {
        PushDown(i,k,arr);
    }
}

//对一个结点进行整理
void PushDown(int i,int k,int arr[])//前k个最大数
{
    int r=i;

    //对非子叶结点进行整理
    while(r<=k/2)
    {
        //若第r个结点没有右孩子，则只与左孩子比较并交换
        if(k%2==0&&r==k/2)      //说明最后一个节点度为1
        {
            if(arr[r-1]>arr[k-1])
               {
                   Temp(arr[r-1],arr[k-1]);
               }
               r=k;
        }
        //左孩子结点最小则结点与左孩子节点交换
        else if(arr[r-1]>arr[2*r-1]&&arr[2*r-1]<=arr[2*r])
        {
            Temp(arr[r-1],arr[2*r-1]);
            r=2*r;
        }
        //右孩子结点最小则节点与右孩子结点交换
        else if(arr[r-1]>arr[2*r]&&arr[2*r]<=arr[2*r-1])
        {
            Temp(arr[r-1],arr[2*r]);
            r=2*r+1;
        }
        //不需要交换则已经整理完毕，结束循环
        else
            r=k;
    }
}


/**===========================
*
*             题目三
*
*============================**/

//数据存储结构以三元组的方式存储
typedef struct{
    int start;
    int _end;
    int stu;
}time;

/**适用于对三元组的快排，思路与题目1一致，依据每一个时间段的结束时间对结束的时间数组以及对应的开始时间的数组进行升序排序*/
//递归调用的快排
void QuickSort(int l,int r,int *start,int *_end)
{
    int m;

    if(l<r)
    {
        m=FindPivot(l,r,start,_end);
        QuickSort(l,m-1,start,_end);
        QuickSort(m+1,r,start,_end);
    }
}
//调用的API
void Msort(int *start,int *_end,int M)
{
    QuickSort(0,M-1,start,_end);
}
//寻找轴枢
int FindPivot(int l,int r,int *start,int *_end)
{
    int p=_end[l],ps=start[l],pe=_end[l];
    while(l<r)
    {
        while(l<r&&_end[r]>=p)   r--;
        if(l<r)
        {
            Temp(_end[l],_end[r]);
            Temp(start[l++],start[r]);
        }
        while(l<r&&_end[l]<p)   l++;
        if(l<r)
        {
            Temp(_end[l],_end[r]);
            Temp(start[l],start[r--]);
        }
    }
    start[l]=ps;
    _end[l]=pe;
    return l;
}
/**注：由于思路与题目一思路一样就没有注释了，求助教xggxjj宽宏大量QAQ*/



/**
*寻找重合最多的时间段，采用贪心策略
*@param start：已经排序好的开始时间数组
*@param end： 已经排序好的结束时间数组
*/
void findPeriod(int *start,int *_end,int M,int N)
{
    int p_end = 0;

    vector<time> save(0);//用栈来存储当前找到的重合次数最多的时间段

    //对结束时间数组从前往后扫描，每值相同的一段作为一个单元，结束时间为该值；
    //在该单元中寻找开始时间最晚为该单元时间段的起始时间，存入三元组中
    //则该单元的重复次数为结束时间相同的元素的个数+该单元之后的开始时间早或等于该单元结束时间的时间段的数目
    while(p_end<M)
    {
        //每次对p_end结束时间相同的一段进行遍历扫描
        int cou=1;
        int m_start = start[p_end];
        while(p_end+1<M&&_end[p_end+1]==_end[p_end])
        {
            //值相同则重复数目++，且该单元的开始时间选择较大者
            p_end++;
            cou++;
            if(start[p_end]>m_start)    m_start=start[p_end];
        }
        //扫描结束后，可以确定以p_end为结束时间的时间段的最大重复次数时的开始时间
        time p;
        p.start=m_start;
        p._end=_end[p_end];

        //再确定p_end结束时间后的时间段的开始时间与该时间段重叠的个数
        int k=p_end;
        while(k+1<M)
        {
            //若后面有开始于该结束时间之前的时间段则人数++
            if(start[k+1]<=_end[p_end])
            {
                cou++;
                if(start[k+1]>p.start)
                    p.start=start[k+1];
            }
            k++;
        }
        p.stu=cou;

        //得到以end为结束时间的时间段的最大重叠次数以及对应的开始时间，与之前的作比较；
        //若重复次数大于之前的最大值则清空之前的记录并将当前的三元组存于栈中
        if(save.size()==0||p.stu==save[0].stu)
            save.push_back(p);
        else if(p.stu>save[0].stu)
        {
            save.clear();
            save.push_back(p);
        }
        p_end++;

    }

    //最后栈中剩下的为重复次数最多的三元组，依次输出即为答案
    cout<<save[0].start<<" "<<save[0]._end;
    for(int i=1;i<save.size();i++)
        cout<<","<<save[i].start<<" "<<save[i]._end;
    cout<<endl;
    return;
}
