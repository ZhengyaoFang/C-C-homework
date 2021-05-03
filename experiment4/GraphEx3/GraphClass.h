#ifndef GraphClass
#define GraphClass


#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#define MAX_VER_NUM 1000
#define INFINITY1 999
#define MAX_NAME 100

//输入合法性检查，增强程序鲁棒性
bool GetData(std::fstream &fp,int &num1,int &num2);
bool GetData(std::fstream &fp,int &node1,int &node2,int &theVal);
bool GetOneData(std::fstream &fp,int &num);
bool GetString(std::string &s);



/**顶点结构体*/
typedef struct MGNode{

    int val;                     //顶点的权重或结点编号
    int degree;                  //结点的度数
    std::string name;           //结点名称
    std::vector<int> Road;      //栈结构记录该结点在第几号线上
    double NodeClusCoefficient; //结点的聚类系数
    int Eccentricity;           //结点的离心率

    //构造函数的初始化
    MGNode()
    {
        val=0;
        degree=0;
        NodeClusCoefficient=0;
        Eccentricity=0;
    }

}MGNode,vertices;


/**边的结构体*/
typedef struct ArcNode{

    int val;                //边的代价
    int Node1,Node2;        //边的两个顶点
    int Road;               //边所在的路线
    bool exist;             //该边是否存在

    //构造函数初始化
    ArcNode()
    {
        val=INFINITY1;      //无穷
        Node1=Node2=0;
        Road=0;
        exist=false;
    }
}ArcNode,AdjMatrix;


/**图类型的定义*/
class Mgraph{
public:

    //重载的构造函数初始化,此处要求传入的数据合法
    Mgraph(int theVexnum,int theArcnum);
    Mgraph(int theVexnum);

    //析构函数
    ~Mgraph(){}

    //成员属性
    AdjMatrix AdjMatrix[MAX_VER_NUM][MAX_VER_NUM];          //邻接矩阵
    vertices vertices[MAX_VER_NUM];                         //顶点向量
    int vexnum;                                             //顶点数
    int arcnum;                                             //边数
    int FloydMatrix[MAX_VER_NUM][MAX_VER_NUM];              //各个顶点之间的最短路径矩阵
    int Diamester;                                          //图直径
    int Radius;                                             //图半径
    int MaxConnectedStation;                                //度数最大的顶点
    double ClusCoefficient;                                 //图的聚类系数
    int ConnectedComponent;                                 //连通分支


    //成员函数
    void Dijkstra(int n1,int n2);
    int Dijkstra(int n1,int n2,int P[]);
    void Init()
    {
        GetConnectedComponent();
        GetClusCoefficient();
        GetFloyedMatrix();
        GetDiamesterAndRadius();
    }
    void AddNode(int node1,int node2,int theVal,int road);
    void FindWay(std::string &s1,std::string &s2);
    int FindNodeNum(std::string &s);





private:


    //成员函数
    void GetClusCoefficient();
    void GetConnectedComponent();
    void DFS(int i,bool visited[MAX_VER_NUM]);//确定连通度
    void GetFloyedMatrix();
    void GetDiamesterAndRadius();
    //辅助函数
    void PutOutWay(int P[],int v,int u);
    void PutOutStation(int P[],int v,int u);




};



#endif // GraphClass
