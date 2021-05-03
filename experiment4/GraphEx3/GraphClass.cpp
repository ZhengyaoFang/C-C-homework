#include <iostream>
#include<string.h>
#include "GraphClass.h"
#include "Robust.h"


using namespace std;



/**
*���캯����ʼ��
*/
Mgraph::Mgraph(int theVexnum,int theArcnum)
{
    this->vexnum=theVexnum;
    this->arcnum=theArcnum;
    Diamester=0;
    Radius=0;
    ClusCoefficient=0;
    ConnectedComponent=0;



    //��ʼ�����ͱ�
    for(int i=0;i<vexnum;i++)
        this->vertices[i].val=i;  //��ʼ������Ȩֵ��Ϊ����

}


/**
*  ����question2�Ĺ��캯��
*/
Mgraph::Mgraph(int theVexnum)
{
    this->vexnum=theVexnum;
    this->arcnum=0;
    Diamester=0;
    Radius=0;
    ClusCoefficient=0;
    ConnectedComponent=0;
}


/**
*  ������Ϣ��ͼ����ӵ㣬���¶�Ӧ���ڽӾ�����Ϣ
*  @param start_idx:�ߵ����
*  @param end_idx:�ߵ��յ�
*  @param weight���ߵ�Ȩ��/����
*  @param road���ñ��ڵڼ�������
*/
void Mgraph::AddNode(int start_idx,int end_idx,int weight,int road)
{
    //���ڽӾ����Ӧ��ӱߵ���Ϣ
    AdjMatrix[start_idx][end_idx].val = weight;
    AdjMatrix[end_idx][start_idx].val = weight;
    AdjMatrix[start_idx][end_idx].exist=true;
    AdjMatrix[end_idx][start_idx].exist=true;
    AdjMatrix[end_idx][start_idx].Road=road;
    AdjMatrix[start_idx][end_idx].Road=road;

    //�ڶ���������Ӧ���������Ϣ
    vertices[start_idx].degree++;
    vertices[end_idx].degree++;
    vertices[start_idx].val=start_idx;
    vertices[end_idx].val=end_idx;
    vertices[start_idx].Road.push_back(road);   //��ջ����ʽ��¼�ö��㶼����Щ·����

    //����ӵ��м�¼���ȵĵ�
    if(vertices[start_idx].degree>vertices[MaxConnectedStation].degree)
        MaxConnectedStation=start_idx;
    if(vertices[end_idx].degree>vertices[MaxConnectedStation].degree)
        MaxConnectedStation=end_idx;
}


/**
*  ���ÿ������ľ���ϵ��������ͼ�ľ���ϵ��
*  @return void
*/
void Mgraph::GetClusCoefficient()
{
    double sum=0;

    for(int i=0;i<vexnum;i++)
    {
        int friends=vertices[i].degree;
        int AllArc;
        int existArc=0;

         //��ÿ�����㣬�����������ж������Ԫ��������Ϊ0��ֱ�ӷ��ؿ�ֹͣ�ж�
        if(friends==0||friends==1)
            vertices[i].NodeClusCoefficient=0;


        else{
            AllArc=friends*(friends-1)/2;

            //���ڽӾ���������ѭ���Ըõ����е��ڽӵ��ж��໥���Ƿ��б�
            for(int n1=0;n1<vexnum;n1++)
            {
                if(AdjMatrix[i][n1].exist)
                {
                    for(int n2=n1+1;n2<vexnum;n2++)
                    {
                        if(AdjMatrix[i][n2].exist&&AdjMatrix[n1][n2].exist)
                            existArc+=1;    //���������++
                    }
                }
            }

            //���ݹ�ʽ������������ϵ������Ϣ�洢�ڸ����Ա������
            vertices[i].NodeClusCoefficient=((double)existArc)/AllArc;
        }//else

        //����ͼ�ľ���ϵ��
        sum+=vertices[i].NodeClusCoefficient;
    }
    ClusCoefficient=sum/vexnum;
}

/**
* �����ͨ��֧�ĸ���
*/
void Mgraph::GetConnectedComponent()
{

    //���÷��ʱ����������ͼ�Ķ������ν���dfs��������¼�����ѭ����ִ�д��������м�����֮ǰ��dfs��û�з��ʣ�
    ConnectedComponent=0;
    bool visited[MAX_VER_NUM];

    //����=�������Ϊ0����ͨ��֧�ĸ���Ϊ0
    if(vexnum==0)
    {
        return;
    }

    //���ʱ�־��ʼ��
    for(int i=0;i<vexnum;i++)
        visited[i]=false;

    //���ζ�û�з��ʹ��Ķ������dfs������������������ͨ��֧��
    for(int i=0;i<vexnum;i++)
    {
        if(!visited[i])
        {
            ConnectedComponent++;
            DFS(i,visited);//�Զ������������ȱ���
        }
    }

}

/**Dijkstra��1����ȡ��������֮������·��
*  @param n1:�Ӷ���n1����
*  @param n2:������n2
*  @param P[]:��¼���·����ÿһ���������һ������
*  @return D[n2]:��n1��n2�����·���ĳ��ȡ�ʧ���򷵻�-1.
*/
int Mgraph::Dijkstra(int n1,int n2,int P[])
{
    if(n1==n2)      //³���ԣ���ֹ����ͬһ�����
    {
        cerr<<"Error!Can not find the way on the one vertex!!"<<endl;
    }
    else if(ConnectedComponent!=1)//��ͼ����ͨ
    {
        //cerr<<"Error!The Graph is not connected!!"<<endl;     //Ϊ�˷������Ҫ�󣬴�����ʾ�����
    }
    else if(n1>vexnum-1&&n2>vexnum-1)   //�������ų��������������жϴ���
    {
        cerr<<"Error!No vertex like this!"<<endl;
    }
    else
    {
        //Dijkstra�㷨


        int D[MAX_VER_NUM]; //��¼n1ΪԴ�ĵ�Դ���·
        bool S[MAX_VER_NUM];//�Ƿ�����ȷ�����·���ļ�����

        //��ʼ��DΪ���㵽n1���ڽӾ����е�·�����ȣ�S��n1���δ�����ʣ�·������Ϊn1
        for(int i=0;i<vexnum;i++)
        {
            D[i]=AdjMatrix[n1][i].val;
            S[i]=false;
            P[i]=n1;
        }
        S[n1]=true;

        //����vexnum-1��������в���
        for(int i=0;i<vexnum-1;i++)
        {
            int mincost=INFINITY1;
            int node=n1;

            //��δ�����ʵĽ���м�ѡ·����С��һ��
            for(int j=0;j<vexnum;j++)
            {
                if(!S[j]&&mincost>D[j])
                {
                    mincost=D[j];
                    node=j;
                }
            }

            //���ý������ѷ��ʽ���У�����·��P��������������֮�����Ľ���жϴ�n1����
            //·�������ý����ת��·���Ƿ��С�����������ø�������·��
            S[node]=true;
            for(int k=0;k<vexnum;k++)
            {
                if(!S[k]&&D[k]>D[node]+AdjMatrix[node][k].val)
                    {
                        D[k]=D[node]+AdjMatrix[node][k].val;
                        P[k]=node;
                    }
            }
        }

        return D[n2];

    }
    return -1;
}


/**
*   Dijkstra��2�������㷨���������������������ʽ��������ں˵��ã�1��
*   @param node1:·�����Ķ�����
*   @param node2��·���յ�Ķ�����
*   @param return void
*/
void Mgraph::Dijkstra(int node1,int node2)
{
    int distance,P[MAX_VER_NUM];

    //����Dijkstra�㷨��ȡ���뼰·��
    distance=Dijkstra(node1,node2,P);

    //��ʽ����ӡ���
    cout<<"the shortest path between "<<node1<<" and "<<node2<<":"<<distance<<endl;
    cout<<"Path:";
    //�ݹ��ӡ·��
    PutOutWay(P,node1,node2);
    cout<<endl;
}


/**
*   �����ڵ���ͼ��Ѱ����վ����̾����Dijkstra�㷨
*   @param s1:����վ������㣩
*   @param s2:����վ�����յ㣩
*   @return void
*/
void Mgraph::FindWay(string &s1,string &s2)
{
    int node1,node2;

    //������վ�������Ӧ���ƥ�䷽�����
    node1=FindNodeNum(s1);
    node2=FindNodeNum(s2);

    //Dijkstra�㷨������ȡ���·���뼰·��
    int P[MAX_VER_NUM];
    int distance;
    distance=Dijkstra(node1,node2,P);
    cout<<"��Ҫ����ʱ�䣺"<<distance<<endl;
    cout<<"����·�ߣ�";

    //��ӡ���·���ĵ���·��
    PutOutStation(P,node1,node2);
}


/**
*   ��ȱ���������ȡ��ͨ��֧�ĸ���
*   @param v:�Խ��v������ȱ���
*   @param visited[]:���ʱ��
*   @return void
*/
void Mgraph::DFS(int v,bool visited[])
{
    visited[v]=true;

    //�Զ���v���ڽӶ���ݹ������ȱ���
    for(int i=0;i<vexnum;i++)
    {
        if(v!=i&&AdjMatrix[v][i].exist&&!visited[i])
            DFS(i,visited);
    }
}

/**
*   ��ʼ�����floyed�����¼����������С����,�õ���Floyed����洢��Mgraph���Ա������
*   @return void
*/
void Mgraph::GetFloyedMatrix()
{
    //�ж�ͼ�Ƿ���ͨ������return
    if(ConnectedComponent!=1)
    {
        //���ݸ�ʽ�����������ʾ��
        //cerr<<"Error!Can not get the FloyedMatrix for the Graph is not connected!"<<endl;
        return;
    }
    else
    {
        //��ʼ��Floyed����Ϊ�ڽӾ���
        for(int i=0;i<vexnum;i++)
        {
            for(int j=0;j<vexnum;j++)
            {
                FloydMatrix[i][j]=AdjMatrix[i][j].val;
            }
        }

        //Floyed�㷨�����ν�����������Ϊ��������ר�����������Ƿ�
        //����������ת�ĵ����ת�µõ���С��·��
        for(int i=0;i<vexnum;i++)
        {
            for(int j=0;j<vexnum;j++)
            {
                if(j==i) continue;
                for(int k=0;k<vexnum;k++)
                {
                    //�������õ���ת��·�����������·Ϊ�����õ���ת��·�����ȸ��¾���
                    if(k!=j&&k!=i&&FloydMatrix[i][j]!=INFINITY1&&FloydMatrix[i][k]!=INFINITY1&&FloydMatrix[j][i]+FloydMatrix[i][k]<FloydMatrix[j][k])
                    {
                        FloydMatrix[j][k]=FloydMatrix[k][j]=FloydMatrix[j][i]+FloydMatrix[i][k];
                    }
                }
            }
        }


    }
}

/**
*   ��ʼ�����ͼ��ֱ���Ͱ뾶
*   @retuen void
*/
void Mgraph::GetDiamesterAndRadius()
{
    //�õ�������������ΪFloyed�����ж�Ӧ����ľ�������ֵ
    for(int i=0;i<vexnum;i++)
    {
        int maxway=0;

        //ȡ�����������ֵΪ�õ������ʼ�¼�ڸõ��Ա������
        for(int j=0;j<vexnum;j++)
        {
            if(FloydMatrix[i][j]!=INFINITY1)
                maxway=maxway>FloydMatrix[i][j]?maxway:FloydMatrix[i][j];
        }
        vertices[i].Eccentricity=maxway;
    }

    //��ͼ��ֱ����뾶
    int maxecc=0;
    int minecc=INFINITY1;

    //�ڸ�����������Ѱ�����ֵ����Сֵ��¼�ڳ�Ա������
    for(int i=0;i<vexnum;i++)
    {
        maxecc=maxecc>vertices[i].Eccentricity?maxecc:vertices[i].Eccentricity;
        minecc=minecc<vertices[i].Eccentricity?minecc:vertices[i].Eccentricity;
    }
    Diamester=maxecc;
    Radius=minecc;
}

/**
*   ����������һ�ĸ�ʽ���ݹ����·��
*   @param P[]:·��
*   @param  v��·�����
*   @param  u��·���յ�
*/
void Mgraph::PutOutWay(int P[],int v,int u)
{
    if(v==u)
    {
        printf("%d ",u);
        return;
    }

    //�ݹ�ȷ�����˳��Ϊ����
    PutOutWay(P,v,P[u]);
    printf("%d ",u);
}

/**
*   �����ڵ���·��ͼ�ĵݹ����·��
*   @param P��·��
*   @param v����㶥����
*   @param u:�յ㶥����
*/
void Mgraph::PutOutStation(int P[],int v,int u)
{
    if(v==u)
    {
        cout<<vertices[u].name;
        return;
    }
    PutOutStation(P,v,P[u]);
    cout<<"=="<<AdjMatrix[u][P[u]].Road<<"==>"<<vertices[u].name;
}


/**
*   �����������վ����Ѱ�����š�
*   @param s��վ������
*   @return ������
*/
int Mgraph::FindNodeNum(string &s)
{
    int i=0;
    //�Ϸ���������õ�վ������
    GetString(s);

    //��������Ѱ����������ͬ��վ��ı��
    while(!(s==vertices[i++].name)&&i<237);

    //��û�����ѯ��������ʾ��������
    while(i==237)
    {
        cout<<"�޷���ѯ��վ�㡰"<<s<<"�������������룡"<<endl;
        i=0;
        GetString(s);
        while(!(s==vertices[i++].name)&&i<237);
    }

    //����վ����
    return --i;
}


