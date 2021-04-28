
#ifndef GraphClass
#define GraphClass

#include <iostream>

#define MAX_DIS 100000
#define MAX_VER_NUM 1000
#define INFINITY1 999
#include <string>


//顶点结构体
typedef struct MGNode{
    int val;
    int degree;
    std::string name;
    int Road;
    double NodeClusCoefficient;//聚类系数
    int Eccentricity;//节点离心率

    //构造函数初始化
    MGNode()
    {
        val=0;
        degree=0;
        Road=0;
        NodeClusCoefficient=0;
        Eccentricity=0;
    }

}MGNode,vertices;

//边的结构体
typedef struct ArcNode{
    int val;
    int Node1,Node2;
    int Road;
    bool exist;
    //构造函数初始化
    ArcNode()
    {
        val=INFINITY1;
        Node1=Node2=0;
        Road=0;
        exist=false;
    }
}ArcNode,AdjMatrix;

class Mgraph{
public:
    //构造函数初始化,此处要求传入的数据合法
    //Mgraph(int theVexnum,int theArcnum);
    Mgraph(int theVexnum,int theArcnum)
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
    ~Mgraph(){}

    //属性
    AdjMatrix AdjMatrix[MAX_VER_NUM][MAX_VER_NUM];
    vertices vertices[MAX_VER_NUM];
    int vexnum;
    int arcnum;
    int FloydMatrix[MAX_VER_NUM][MAX_VER_NUM];//各个顶点之间的最短路径矩阵
    int Diamester;//图直径
    int Radius;//图半径
    double ClusCoefficient;//图的聚类系数
    int ConnectedComponent;//连通分支

    void Dijkstra(int n1,int n2);
    void Init()
    {
        GetConnectedComponent();
        GetClusCoefficient();
        GetFloyedMatrix();
        GetDiamesterAndRadius();
    }





private:


    //成员函数
    void GetClusCoefficient();
    void GetConnectedComponent();
    void DFS(int i,bool visited[MAX_VER_NUM]);//确定连通度
    void GetFloyedMatrix();
    void GetDiamesterAndRadius();
    //辅助函数
    void PutOutWay(int P[],int v,int u);
    void GetData(int &node1,int &node2,int &theVal);//输入合法性检测


};



#endif // GraphClass
