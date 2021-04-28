
#ifndef GraphClass
#define GraphClass
#include<locale>
#include <iostream>
#include <vector>

#define MAX_DIS 100000
#define MAX_VER_NUM 1000
#define INFINITY1 999
#include <string>
#define MAX_NAME 100



//����ṹ��
typedef struct MGNode{
    int val;
    int degree;
    std::string name;
    std::vector<int> Road;

    double NodeClusCoefficient;//����ϵ��
    int Eccentricity;//�ڵ�������

    //���캯����ʼ��
    MGNode()
    {
        val=0;
        degree=0;
        NodeClusCoefficient=0;
        Eccentricity=0;
    }

}MGNode,vertices;

//�ߵĽṹ��
typedef struct ArcNode{
    int val;
    int Node1,Node2;
    int Road;
    bool exist;
    //���캯����ʼ��
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
    //���캯����ʼ��,�˴�Ҫ��������ݺϷ�
    //Mgraph(int theVexnum,int theArcnum);
    Mgraph(int theVexnum,int theArcnum);
    Mgraph(int theVexnum);

    ~Mgraph(){}

    //����
    AdjMatrix AdjMatrix[MAX_VER_NUM][MAX_VER_NUM];
    vertices vertices[MAX_VER_NUM];
    int vexnum;
    int arcnum;
    int FloydMatrix[MAX_VER_NUM][MAX_VER_NUM];//��������֮������·������
    int Diamester;//ͼֱ��
    int Radius;//ͼ�뾶
    int MaxConnectedStation;
    double ClusCoefficient;//ͼ�ľ���ϵ��
    int ConnectedComponent;//��ͨ��֧

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
    void FindWay(std::string s1,std::string s2);
    int FindNodeNum(std::string s);





private:


    //��Ա����
    void GetClusCoefficient();
    void GetConnectedComponent();
    void DFS(int i,bool visited[MAX_VER_NUM]);//ȷ����ͨ��
    void GetFloyedMatrix();
    void GetDiamesterAndRadius();
    //��������
    void PutOutWay(int P[],int v,int u);
    void PutOutStation(int P[],int v,int u);
    void GetData(int &node1,int &node2,int &theVal);//����Ϸ��Լ��


};



#endif // GraphClass
