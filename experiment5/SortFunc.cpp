/** =============文档说明================
*
*   本文件为题目要求算法的函数定义文件
*
*=====================================**/
#include "SortFunc.h"


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

void QuickSort(int l,int r,int milk[])
{
    if(l<r)//判定当l<r时对区间[l,r]进行排序
    {
        int m=FindM(l,r,milk);
        QuickSort(l,m-1,milk);
        QuickSort(m+1,r,milk);
    }
}

int FindM(int l,int r,int milk[])
{
    int p=milk[l];
    while(l<r)
    {
        while(l<r&&milk[r]>=p)   r--;
        if(l<r)
            milk[l++]=milk[r];
        while(l<r&&milk[l]<p)   l++;
        if(l<r)
            milk[r--]=milk[l];
    }
    milk[l]=p;
    return l;
}

void Temp(int &a,int &b)
{
    int temp;
    temp=a;
    a=b;
    b=temp;
}



/**===========================
*
*   题目二
*
*============================**/

int *Maxk(int k,int n,int arr[])
{
    //初始建堆
    Init(k,arr);
    /*
    for(int i=k-1;i>=1;i--)
    {
        Temp(arr[i],arr[0]);
        PushDown(0,i-1);
    }
    */
    for(int i=k;i<n;i++)
    {
        if(arr[0]<arr[i])
        {
            Temp(arr[0],arr[i]);
            PushDown(1,k,arr);
        }
    }
    for(int i=k-1;i>=1;i--)
    {
        Temp(arr[i],arr[0]);
        PushDown(1,i,arr);
    }
    return arr;
}

void Init(int k,int arr[])
{
    for(int i=k/2;i>=1;i--)
    {
        PushDown(i,k,arr);
    }
}

//对一个结点进行整理
void PushDown(int i,int k,int arr[])//前k个最大数
{
    int r=i;
    while(r<=k/2)
    {
        if(k%2==0&&r==k/2)      //说明最后一个节点度为1
        {
            if(arr[r-1]>arr[k-1])
               {
                   Temp(arr[r-1],arr[k-1]);
               }
               r=k;
        }
        else if(arr[r-1]>arr[2*r-1]&&arr[2*r-1]<=arr[2*r])
        {
            Temp(arr[r-1],arr[2*r-1]);
            r=2*r;
        }
        else if(arr[r-1]>arr[2*r]&&arr[2*r]<=arr[2*r-1])
        {
            Temp(arr[r-1],arr[2*r]);
            r=2*r+1;
        }
        else
            r=k;
    }
}


/**===========================
*
*      题目三
*
*============================**/

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

void Msort(int *start,int *_end,int M)
{
    QuickSort(0,M-1,start,_end);
}



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

typedef struct{
    int start;
    int _end;
    int stu;
}time;



void findPeriod(int *start,int *_end,int M,int N)
{
    int p_end = 0;

    vector<time> save(0);

    while(p_end<M)
    {
        int cou=1;
        int m_start = start[p_end];
        while(p_end+1<M&&_end[p_end+1]==_end[p_end])
        {
            p_end++;
            cou++;
            if(start[p_end]>m_start)    m_start=start[p_end];
        }
        time p;
        p.start=m_start;
        p._end=_end[p_end];

        int k=p_end;
        while(k+1<M)
        {
            if(start[k+1]<=_end[p_end])
            {
                cou++;
                if(start[k+1]>p.start)
                    p.start=start[k+1];
            }
            k++;
        }
        p.stu=cou;

        if(save.size()==0||p.stu==save[0].stu)
            save.push_back(p);
        else if(p.stu>save[0].stu)
        {
            save.clear();
            save.push_back(p);
        }
        p_end++;

    }
    cout<<save[0].start<<" "<<save[0]._end;
    for(int i=1;i<save.size();i++)
        cout<<","<<save[i].start<<" "<<save[i]._end;
    cout<<endl;
    return;
}
