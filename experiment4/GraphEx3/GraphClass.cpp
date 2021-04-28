#include <iostream>
#include "GraphClass.h"
using namespace std;
//类成员函数定义
/*
Mgraph::Mgraph(int theVexnum,int theArcnum)
{
    this->vexnum=theVexnum;
    this->arcnum=theArcnum;

    printf("sdf");


    //初始化结点和边
    for(int i=0;i<vexnum;i++)
        this->vertices[i].val=i;  //初始化顶点权值代为其编号

}
*/

//获得每个顶点的聚类系数和无向图的聚类系数
void Mgraph::GetClusCoefficient()
{
    double sum=0;
    for(int i=0;i<vexnum;i++)
    {
        int friends=vertices[i].degree;
        int AllArc;
        int existArc=0;
        if(friends==0||friends==1)
            vertices[i].NodeClusCoefficient=0;
        else{
            AllArc=friends*(friends-1)/2;
            for(int n1=0;n1<vexnum;n1++)
            {
                if(AdjMatrix[i][n1].exist)
                {
                    for(int n2=n1+1;n2<vexnum;n2++)
                    {
                        if(AdjMatrix[i][n2].exist&&AdjMatrix[n1][n2].exist)
                            existArc+=1;
                    }
                }
            }
            vertices[i].NodeClusCoefficient=((double)existArc)/AllArc;
        }//else

        sum+=vertices[i].NodeClusCoefficient;
    }
    ClusCoefficient=sum/vexnum;
}

//获得连通分支的个数
void Mgraph::GetConnectedComponent()
{
    ConnectedComponent=0;
    bool visited[MAX_VER_NUM];

    if(vexnum==0)
    {
        return;
    }

    //访问标志初始化
    for(int i=0;i<vexnum;i++)
        visited[i]=false;

    for(int i=0;i<vexnum;i++)
    {
        if(!visited[i])
        {
            ConnectedComponent++;
            DFS(i,visited);//对顶点进行深度优先遍历
        }
    }

}

//Dijkstra获取单源最短路径
void Mgraph::Dijkstra(int n1,int n2)
{
    if(n1==n2)
    {
        cerr<<"Error!Can not find the way on the one vertex!!"<<endl;
    }
    else if(ConnectedComponent!=1)//若图不连通
    {
        cerr<<"Error!The Graph is not connected!!"<<endl;
    }
    else if(n1>vexnum-1&&n2>vexnum-1)
    {
        cerr<<"Error!No vertex like this!"<<endl;
    }
    else
    {
        //Dijkstra算法
        int D[MAX_VER_NUM],P[MAX_VER_NUM];
        bool S[MAX_VER_NUM];//是否在已确定最短路径的集合中

        //初始化
        for(int i=0;i<vexnum;i++)
        {
            D[i]=AdjMatrix[n1][i].val;
            S[i]=false;
            P[i]=n1;
        }
        S[n1]=true;
        for(int i=0;i<vexnum-1;i++)
        {
            int mincost=INFINITY1;
            int node=n1;
            for(int j=0;j<vexnum;j++)
            {
                if(!S[j]&&mincost>D[j])
                {
                    mincost=D[j];
                    node=j;
                }
            }
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
        cout<<"the shortest path between "<<n1<<" and "<<n2<<":"<<D[n2]<<endl;

        cout<<"Path:";
        PutOutWay(P,n1,n2);
        cout<<endl;


    }
}

//深度遍历
void Mgraph::DFS(int v,bool visited[])
{
    visited[v]=true;
    for(int i=0;i<vexnum;i++)
    {
        if(v!=i&&AdjMatrix[v][i].exist&&!visited[i])
            DFS(i,visited);
    }
}

void Mgraph::GetFloyedMatrix()
{
    if(ConnectedComponent!=1)
    {
        cerr<<"Error!Can not get the FloyedMatrix for the Graph is not connected!"<<endl;
        return;
    }
    else
    {
        //初始化
        for(int i=0;i<vexnum;i++)
        {
            for(int j=0;j<vexnum;j++)
            {
                FloydMatrix[i][j]=AdjMatrix[i][j].val;
            }
        }
        for(int i=0;i<vexnum;i++)
        {
            for(int j=0;j<vexnum;j++)
            {
                if(j==i) continue;
                for(int k=0;k<vexnum;k++)
                {
                    if(k!=j&&k!=i&&FloydMatrix[i][j]!=INFINITY1&&FloydMatrix[i][k]!=INFINITY1&&FloydMatrix[j][i]+FloydMatrix[i][k]<FloydMatrix[j][k])
                    {
                        FloydMatrix[j][k]=FloydMatrix[k][j]=FloydMatrix[j][i]+FloydMatrix[i][k];
                    }
                }
            }
        }


    }
}

void Mgraph::GetDiamesterAndRadius()
{
    //得到结点的离心率
        for(int i=0;i<vexnum;i++)
        {
            int maxway=0;
            for(int j=0;j<vexnum;j++)
            {
                if(FloydMatrix[i][j]!=INFINITY1)
                    maxway=maxway>FloydMatrix[i][j]?maxway:FloydMatrix[i][j];
            }
            vertices[i].Eccentricity=maxway;
        }

    int maxecc=0;
    int minecc=INFINITY1;
    for(int i=0;i<vexnum;i++)
    {
        maxecc=maxecc>vertices[i].Eccentricity?maxecc:vertices[i].Eccentricity;
        minecc=minecc<vertices[i].Eccentricity?minecc:vertices[i].Eccentricity;
    }
    Diamester=maxecc;
    Radius=minecc;
}

void Mgraph::PutOutWay(int P[],int v,int u)
{
    if(v==u)
    {
        printf("%d ",u);
        return;
    }

    PutOutWay(P,v,P[u]);
    printf("%d ",u);
}

//暂时这样子，后面再改
void Mgraph::GetData(int &node1,int &node2,int &theVal)
{
    cin>>node1;
    cin>>node2;
    cin>>theVal;
}

