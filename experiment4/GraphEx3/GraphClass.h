
#ifndef GraphClass
#define GraphClass

#include <iostream>

#define MAX_DIS 100000
#define MAX_VER_NUM 1000
#define INFINITY1 999
#include <string>


//����ṹ��
typedef struct MGNode{
    int val;
    int degree;
    std::string name;
    int Road;
    double NodeClusCoefficient;//����ϵ��
    int Eccentricity;//�ڵ�������

    //���캯����ʼ��
    MGNode()
    {
        val=0;
        degree=0;
        Road=0;
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
    Mgraph(int theVexnum,int theArcnum)
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
    ~Mgraph(){}

    //����
    AdjMatrix AdjMatrix[MAX_VER_NUM][MAX_VER_NUM];
    vertices vertices[MAX_VER_NUM];
    int vexnum;
    int arcnum;
    int FloydMatrix[MAX_VER_NUM][MAX_VER_NUM];//��������֮������·������
    int Diamester;//ͼֱ��
    int Radius;//ͼ�뾶
    double ClusCoefficient;//ͼ�ľ���ϵ��
    int ConnectedComponent;//��ͨ��֧

    void Dijkstra(int n1,int n2);
    void Init()
    {
        GetConnectedComponent();
        GetClusCoefficient();
        GetFloyedMatrix();
        GetDiamesterAndRadius();
    }





private:


    //��Ա����
    void GetClusCoefficient();
    void GetConnectedComponent();
    void DFS(int i,bool visited[MAX_VER_NUM]);//ȷ����ͨ��
    void GetFloyedMatrix();
    void GetDiamesterAndRadius();
    //��������
    void PutOutWay(int P[],int v,int u);
    void GetData(int &node1,int &node2,int &theVal);//����Ϸ��Լ��


};



#endif // GraphClass
