#include <iostream>
#include<string.h>
#include "GraphClass.h"
#include "Robust.h"


using namespace std;



/**
*构造函数初始化
*/
Mgraph::Mgraph(int theVexnum,int theArcnum)
{
    this->vexnum=theVexnum;
    this->arcnum=theArcnum;
    Diamester=0;
    Radius=0;
    ClusCoefficient=0;
    ConnectedComponent=0;



    //初始化结点和边
    for(int i=0;i<vexnum;i++)
        this->vertices[i].val=i;  //初始化顶点权值代为其编号

}


/**
*  适用question2的构造函数
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
*  输入信息在图中添加点，更新对应的邻接矩阵及信息
*  @param start_idx:边的起点
*  @param end_idx:边的终点
*  @param weight：边的权重/代价
*  @param road：该边在第几号线上
*/
void Mgraph::AddNode(int start_idx,int end_idx,int weight,int road)
{
    //在邻接矩阵对应添加边的信息
    AdjMatrix[start_idx][end_idx].val = weight;
    AdjMatrix[end_idx][start_idx].val = weight;
    AdjMatrix[start_idx][end_idx].exist=true;
    AdjMatrix[end_idx][start_idx].exist=true;
    AdjMatrix[end_idx][start_idx].Road=road;
    AdjMatrix[start_idx][end_idx].Road=road;

    //在顶点向量对应顶点更新信息
    vertices[start_idx].degree++;
    vertices[end_idx].degree++;
    vertices[start_idx].val=start_idx;
    vertices[end_idx].val=end_idx;
    vertices[start_idx].Road.push_back(road);   //以栈的形式记录该顶点都在哪些路径上

    //在添加点中记录最大度的点
    if(vertices[start_idx].degree>vertices[MaxConnectedStation].degree)
        MaxConnectedStation=start_idx;
    if(vertices[end_idx].degree>vertices[MaxConnectedStation].degree)
        MaxConnectedStation=end_idx;
}


/**
*  获得每个顶点的聚类系数和无向图的聚类系数
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

         //对每个顶点，根据其出入度判断最大邻元边数。若为0则直接返回空停止判断
        if(friends==0||friends==1)
            vertices[i].NodeClusCoefficient=0;


        else{
            AllArc=friends*(friends-1)/2;

            //在邻接矩阵中两次循环对该点所有的邻接点判断相互间是否有边
            for(int n1=0;n1<vexnum;n1++)
            {
                if(AdjMatrix[i][n1].exist)
                {
                    for(int n2=n1+1;n2<vexnum;n2++)
                    {
                        if(AdjMatrix[i][n2].exist&&AdjMatrix[n1][n2].exist)
                            existArc+=1;    //若有则边数++
                    }
                }
            }

            //根据公式，计算各点聚类系数将信息存储于各点成员属性中
            vertices[i].NodeClusCoefficient=((double)existArc)/AllArc;
        }//else

        //计算图的聚类系数
        sum+=vertices[i].NodeClusCoefficient;
    }
    ClusCoefficient=sum/vexnum;
}

/**
* 获得连通分支的个数
*/
void Mgraph::GetConnectedComponent()
{

    //设置访问标记向量，对图的顶点依次进行dfs搜索，记录最外层循环的执行次数（即有几个在之前的dfs中没有访问）
    ConnectedComponent=0;
    bool visited[MAX_VER_NUM];

    //若点=顶点个数为0则连通分支的个数为0
    if(vexnum==0)
    {
        return;
    }

    //访问标志初始化
    for(int i=0;i<vexnum;i++)
        visited[i]=false;

    //依次对没有访问过的顶点进行dfs搜索，搜索次数即连通分支数
    for(int i=0;i<vexnum;i++)
    {
        if(!visited[i])
        {
            ConnectedComponent++;
            DFS(i,visited);//对顶点进行深度优先遍历
        }
    }

}

/**Dijkstra（1）获取两个顶点之间的最短路径
*  @param n1:从顶点n1出发
*  @param n2:到顶点n2
*  @param P[]:记录最短路径中每一个顶点的上一个顶点
*  @return D[n2]:从n1到n2的最短路径的长度。失败则返回-1.
*/
int Mgraph::Dijkstra(int n1,int n2,int P[])
{
    if(n1==n2)      //鲁棒性，防止输入同一个结点
    {
        cerr<<"Error!Can not find the way on the one vertex!!"<<endl;
    }
    else if(ConnectedComponent!=1)//若图不连通
    {
        //cerr<<"Error!The Graph is not connected!!"<<endl;     //为了符合输出要求，错误提示不输出
    }
    else if(n1>vexnum-1&&n2>vexnum-1)   //若顶点编号超出顶点总数则判断错误
    {
        cerr<<"Error!No vertex like this!"<<endl;
    }
    else
    {
        //Dijkstra算法


        int D[MAX_VER_NUM]; //记录n1为源的单源最短路
        bool S[MAX_VER_NUM];//是否在已确定最短路径的集合中

        //初始化D为各点到n1的邻接矩阵中的路径长度，S除n1外均未被访问，路径均设为n1
        for(int i=0;i<vexnum;i++)
        {
            D[i]=AdjMatrix[n1][i].val;
            S[i]=false;
            P[i]=n1;
        }
        S[n1]=true;

        //共对vexnum-1个顶点进行操作
        for(int i=0;i<vexnum-1;i++)
        {
            int mincost=INFINITY1;
            int node=n1;

            //在未被访问的结点中间选路径最小的一个
            for(int j=0;j<vexnum;j++)
            {
                if(!S[j]&&mincost>D[j])
                {
                    mincost=D[j];
                    node=j;
                }
            }

            //将该结点加入已访问结点中，更新路径P，并更新其它与之相连的结点判断从n1到各
            //路径经过该结点中转后路径是否较小，若是则重置各结点最短路。
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
*   Dijkstra（2）重载算法，适用于问题二，包括格式化输出，内核调用（1）
*   @param node1:路径起点的顶点标号
*   @param node2：路径终点的顶点标号
*   @param return void
*/
void Mgraph::Dijkstra(int node1,int node2)
{
    int distance,P[MAX_VER_NUM];

    //调用Dijkstra算法求取距离及路径
    distance=Dijkstra(node1,node2,P);

    //格式化打印输出
    cout<<"the shortest path between "<<node1<<" and "<<node2<<":"<<distance<<endl;
    cout<<"Path:";
    //递归打印路径
    PutOutWay(P,node1,node2);
    cout<<endl;
}


/**
*   适用于地铁图的寻找两站间最短距离的Dijkstra算法
*   @param s1:地铁站名（起点）
*   @param s2:地铁站名（终点）
*   @return void
*/
void Mgraph::FindWay(string &s1,string &s2)
{
    int node1,node2;

    //将地铁站名与其对应标号匹配方便查找
    node1=FindNodeNum(s1);
    node2=FindNodeNum(s2);

    //Dijkstra算法调用求取最短路距离及路径
    int P[MAX_VER_NUM];
    int distance;
    distance=Dijkstra(node1,node2,P);
    cout<<"需要最少时间："<<distance<<endl;
    cout<<"地铁路线：";

    //打印最短路径的地铁路线
    PutOutStation(P,node1,node2);
}


/**
*   深度遍历辅助求取连通分支的个数
*   @param v:对结点v进行深度遍历
*   @param visited[]:访问标记
*   @return void
*/
void Mgraph::DFS(int v,bool visited[])
{
    visited[v]=true;

    //对顶点v的邻接顶点递归进行深度遍历
    for(int i=0;i<vexnum;i++)
    {
        if(v!=i&&AdjMatrix[v][i].exist&&!visited[i])
            DFS(i,visited);
    }
}

/**
*   初始化获得floyed矩阵记录各顶点间的最小距离,得到的Floyed矩阵存储于Mgraph类成员属性中
*   @return void
*/
void Mgraph::GetFloyedMatrix()
{
    //判断图是否连通，否则return
    if(ConnectedComponent!=1)
    {
        //依据格式不输出错误提示。
        //cerr<<"Error!Can not get the FloyedMatrix for the Graph is not connected!"<<endl;
        return;
    }
    else
    {
        //初始化Floyed矩阵为邻接矩阵
        for(int i=0;i<vexnum;i++)
        {
            for(int j=0;j<vexnum;j++)
            {
                FloydMatrix[i][j]=AdjMatrix[i][j].val;
            }
        }

        //Floyed算法，依次将各顶点设置为允许经过中专，调整矩阵是否
        //在允许经过中转的点的中转下得到更小的路径
        for(int i=0;i<vexnum;i++)
        {
            for(int j=0;j<vexnum;j++)
            {
                if(j==i) continue;
                for(int k=0;k<vexnum;k++)
                {
                    //若经过该点中转的路径更短则最短路为经过该点中转的路径长度更新矩阵
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
*   初始化获得图的直径和半径
*   @retuen void
*/
void Mgraph::GetDiamesterAndRadius()
{
    //得到各结点的离心率为Floyed矩阵中对应各点的距离的最大值
    for(int i=0;i<vexnum;i++)
    {
        int maxway=0;

        //取距离各点的最大值为该点离心率记录于该点成员属性中
        for(int j=0;j<vexnum;j++)
        {
            if(FloydMatrix[i][j]!=INFINITY1)
                maxway=maxway>FloydMatrix[i][j]?maxway:FloydMatrix[i][j];
        }
        vertices[i].Eccentricity=maxway;
    }

    //求图的直径与半径
    int maxecc=0;
    int minecc=INFINITY1;

    //在各点离心率中寻找最大值与最小值记录于成员属性中
    for(int i=0;i<vexnum;i++)
    {
        maxecc=maxecc>vertices[i].Eccentricity?maxecc:vertices[i].Eccentricity;
        minecc=minecc<vertices[i].Eccentricity?minecc:vertices[i].Eccentricity;
    }
    Diamester=maxecc;
    Radius=minecc;
}

/**
*   适用于问题一的格式化递归输出路径
*   @param P[]:路径
*   @param  v：路径起点
*   @param  u：路径终点
*/
void Mgraph::PutOutWay(int P[],int v,int u)
{
    if(v==u)
    {
        printf("%d ",u);
        return;
    }

    //递归确保输出顺序为正向
    PutOutWay(P,v,P[u]);
    printf("%d ",u);
}

/**
*   适用于地铁路线图的递归输出路径
*   @param P：路径
*   @param v：起点顶点编号
*   @param u:终点顶点编号
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
*   问题二的输入站点名寻找其标号。
*   @param s：站点名称
*   @return 顶点编号
*/
int Mgraph::FindNodeNum(string &s)
{
    int i=0;
    //合法性输入检查得到站点名称
    GetString(s);

    //遍历顶点寻找与名称相同的站点的编号
    while(!(s==vertices[i++].name)&&i<237);

    //若没有则查询不到，提示重新输入
    while(i==237)
    {
        cout<<"无法查询到站点“"<<s<<"”，请重新输入！"<<endl;
        i=0;
        GetString(s);
        while(!(s==vertices[i++].name)&&i<237);
    }

    //返回站点编号
    return --i;
}


