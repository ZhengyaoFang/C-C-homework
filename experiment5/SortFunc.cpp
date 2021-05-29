/** =============�ĵ�˵��================
*
*   ���ļ�Ϊ��ĿҪ���㷨�ĺ��������ļ�
*
*=====================================**/
#include "SortFunc.h"


/**===========================
*
*           ��Ŀһ
*
*============================**/

/**
* ����˼��Ѱ���������λ��
* @param n����ţ��Ŀ��Ϊ����
* @param milk: ����Ϊn��������Ϊ��ţ�Ĳ�����
* @return middle:int�ͣ�����������λ��
*/
int FindMiddleMilk(int n,int milk[])
{
    //����ţ���������п�������
    QuickSort(0,n-1,milk);
//    for(int i=0;i<n;i++)
//        cout<<milk[i]<<endl;

    //�����������е���λ��
    return milk[n/2];
}


/**
*��������ݹ���ò���
*@param l: ��������[l,r]���
*@param r: ��������[l,r]�յ�
*@param milk:�����ŵ�����
*/
void QuickSort(int l,int r,int milk[])
{
    if(l<r)//�ж���l<rʱ������[l,r]��������
    {
        int m=FindM(l,r,milk);  //Ѱ���м����ಢͬʱ��������з���
        QuickSort(l,m-1,milk);  //���������ߵݹ���п�������
        QuickSort(m+1,r,milk);
    }
}


/**
*����Ѱ�����ಢ��С�������ֵ��������ߣ����������ֵ�������ұ�
*@param l: ��������[l,r]���
*@param r: ��������[l,r]�յ�
*@param milk:�����ŵ�����
*@return l:���źú������λ��
*/
int FindM(int l,int r,int milk[])
{
    //����ѡ������ߵ�Ԫ��
    int p=milk[l];

    //����λ��ָ��ֱ�Ϊ�����������м�ɨ�裬����ָ������ָ��������������ʱ�����
    while(l<r)
    {
        //��Ϊ����ѡ����ߵ�һ�����ʴ��Ҷ˿�ʼɨ�裬���ڵ�������ֵ�Թ���ֱ���ҵ�С������ֵԪ��
        //������δ������l��Ϊr��ָ��ͬʱl++,׼������һλ���ҽ���ɨ��
        while(l<r&&milk[r]>=p)   r--;
        if(l<r)
            milk[l++]=milk[r];

        //��ָ�����ҽ���ɨ�裬�������ڵ�������ֵ��rλ����ֵ��r--
        while(l<r&&milk[l]<p)   l++;
        if(l<r)
            milk[r--]=milk[l];
    }
    //����ѭ������ʱlΪ����ֵ����λ��
    milk[l]=p;
    return l;
}

/**
*����ֵ
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
*           ��Ŀ��
*
*============================**/


/**
*�ҵ�����k����
*@param k:�������ĸ���
*@param n:����Ԫ������
*@param arr������Ԫ��
*/
int *Maxk(int k,int n,int arr[])
{
    //��ʼ��ǰk������С����
    Init(k,arr);

    //�Դӵ�k+1������������κͶѶ��Ƚϣ����϶Ѷ����򽻻���PushDown
    for(int i=k;i<n;i++)
    {
        if(arr[0]<arr[i])
        {
            Temp(arr[0],arr[i]);
            PushDown(1,k,arr);
        }
    }

    //��ѡ�����k������������ź����������ǰk��λ����
    for(int i=k-1;i>=1;i--)
    {
        Temp(arr[i],arr[0]);
        PushDown(1,i,arr);
    }
    return arr;
}

/**
*��ʼ��������ǰk��������
*@param k:ǰk����
*@param arr������
*/
void Init(int k,int arr[])
{
    //��k/2��1���ν�������
    for(int i=k/2;i>=1;i--)
    {
        PushDown(i,k,arr);
    }
}

//��һ������������
void PushDown(int i,int k,int arr[])//ǰk�������
{
    int r=i;

    //�Է���Ҷ����������
    while(r<=k/2)
    {
        //����r�����û���Һ��ӣ���ֻ�����ӱȽϲ�����
        if(k%2==0&&r==k/2)      //˵�����һ���ڵ��Ϊ1
        {
            if(arr[r-1]>arr[k-1])
               {
                   Temp(arr[r-1],arr[k-1]);
               }
               r=k;
        }
        //���ӽ����С���������ӽڵ㽻��
        else if(arr[r-1]>arr[2*r-1]&&arr[2*r-1]<=arr[2*r])
        {
            Temp(arr[r-1],arr[2*r-1]);
            r=2*r;
        }
        //�Һ��ӽ����С��ڵ����Һ��ӽ�㽻��
        else if(arr[r-1]>arr[2*r]&&arr[2*r]<=arr[2*r-1])
        {
            Temp(arr[r-1],arr[2*r]);
            r=2*r+1;
        }
        //����Ҫ�������Ѿ�������ϣ�����ѭ��
        else
            r=k;
    }
}


/**===========================
*
*             ��Ŀ��
*
*============================**/

//���ݴ洢�ṹ����Ԫ��ķ�ʽ�洢
typedef struct{
    int start;
    int _end;
    int stu;
}time;

/**�����ڶ���Ԫ��Ŀ��ţ�˼·����Ŀ1һ�£�����ÿһ��ʱ��εĽ���ʱ��Խ�����ʱ�������Լ���Ӧ�Ŀ�ʼʱ������������������*/
//�ݹ���õĿ���
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
//���õ�API
void Msort(int *start,int *_end,int M)
{
    QuickSort(0,M-1,start,_end);
}
//Ѱ������
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
/**ע������˼·����Ŀһ˼·һ����û��ע���ˣ�������xggxjj������QAQ*/



/**
*Ѱ���غ�����ʱ��Σ�����̰�Ĳ���
*@param start���Ѿ�����õĿ�ʼʱ������
*@param end�� �Ѿ�����õĽ���ʱ������
*/
void findPeriod(int *start,int *_end,int M,int N)
{
    int p_end = 0;

    vector<time> save(0);//��ջ���洢��ǰ�ҵ����غϴ�������ʱ���

    //�Խ���ʱ�������ǰ����ɨ�裬ÿֵ��ͬ��һ����Ϊһ����Ԫ������ʱ��Ϊ��ֵ��
    //�ڸõ�Ԫ��Ѱ�ҿ�ʼʱ������Ϊ�õ�Ԫʱ��ε���ʼʱ�䣬������Ԫ����
    //��õ�Ԫ���ظ�����Ϊ����ʱ����ͬ��Ԫ�صĸ���+�õ�Ԫ֮��Ŀ�ʼʱ�������ڸõ�Ԫ����ʱ���ʱ��ε���Ŀ
    while(p_end<M)
    {
        //ÿ�ζ�p_end����ʱ����ͬ��һ�ν��б���ɨ��
        int cou=1;
        int m_start = start[p_end];
        while(p_end+1<M&&_end[p_end+1]==_end[p_end])
        {
            //ֵ��ͬ���ظ���Ŀ++���Ҹõ�Ԫ�Ŀ�ʼʱ��ѡ��ϴ���
            p_end++;
            cou++;
            if(start[p_end]>m_start)    m_start=start[p_end];
        }
        //ɨ������󣬿���ȷ����p_endΪ����ʱ���ʱ��ε�����ظ�����ʱ�Ŀ�ʼʱ��
        time p;
        p.start=m_start;
        p._end=_end[p_end];

        //��ȷ��p_end����ʱ����ʱ��εĿ�ʼʱ�����ʱ����ص��ĸ���
        int k=p_end;
        while(k+1<M)
        {
            //�������п�ʼ�ڸý���ʱ��֮ǰ��ʱ���������++
            if(start[k+1]<=_end[p_end])
            {
                cou++;
                if(start[k+1]>p.start)
                    p.start=start[k+1];
            }
            k++;
        }
        p.stu=cou;

        //�õ���endΪ����ʱ���ʱ��ε�����ص������Լ���Ӧ�Ŀ�ʼʱ�䣬��֮ǰ�����Ƚϣ�
        //���ظ���������֮ǰ�����ֵ�����֮ǰ�ļ�¼������ǰ����Ԫ�����ջ��
        if(save.size()==0||p.stu==save[0].stu)
            save.push_back(p);
        else if(p.stu>save[0].stu)
        {
            save.clear();
            save.push_back(p);
        }
        p_end++;

    }

    //���ջ��ʣ�µ�Ϊ�ظ�����������Ԫ�飬���������Ϊ��
    cout<<save[0].start<<" "<<save[0]._end;
    for(int i=1;i<save.size();i++)
        cout<<","<<save[i].start<<" "<<save[i]._end;
    cout<<endl;
    return;
}
