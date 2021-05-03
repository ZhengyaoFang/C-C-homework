#ifndef GraphClass
#define GraphClass


#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#define MAX_VER_NUM 1000
#define INFINITY1 999
#define MAX_NAME 100




/**����ṹ��*/
typedef struct MGNode{

    int val;                     //�����Ȩ�ػ�����
    int degree;                  //���Ķ���
    std::string name;           //�������
    std::vector<int> Road;      //ջ�ṹ��¼�ý���ڵڼ�������
    double NodeClusCoefficient; //���ľ���ϵ��
    int Eccentricity;           //����������

    //���캯���ĳ�ʼ��
    MGNode()
    {
        val=0;
        degree=0;
        NodeClusCoefficient=0;
        Eccentricity=0;
    }

}MGNode,vertices;


/**�ߵĽṹ��*/
typedef struct ArcNode{

    int val;                //�ߵĴ���
    int Node1,Node2;        //�ߵ���������
    int Road;               //�����ڵ�·��
    bool exist;             //�ñ��Ƿ����

    //���캯����ʼ��
    ArcNode()
    {
        val=INFINITY1;      //����
        Node1=Node2=0;
        Road=0;
        exist=false;
    }
}ArcNode,AdjMatrix;


/**ͼ���͵Ķ���*/
class Mgraph{
public:

    //���صĹ��캯����ʼ��,�˴�Ҫ��������ݺϷ�
    Mgraph(int theVexnum,int theArcnum);
    Mgraph(int theVexnum);

    //��������
    ~Mgraph(){}

    //��Ա����
    AdjMatrix AdjMatrix[MAX_VER_NUM][MAX_VER_NUM];          //�ڽӾ���
    vertices vertices[MAX_VER_NUM];                         //��������
    int vexnum;                                             //������
    int arcnum;                                             //����
    int FloydMatrix[MAX_VER_NUM][MAX_VER_NUM];              //��������֮������·������
    int Diamester;                                          //ͼֱ��
    int Radius;                                             //ͼ�뾶
    int MaxConnectedStation;                                //�������Ķ���
    double ClusCoefficient;                                 //ͼ�ľ���ϵ��
    int ConnectedComponent;                                 //��ͨ��֧


    //��Ա����
    void Dijkstra(int n1,int n2);                           //�������Dijkstra�����㷨
    int Dijkstra(int n1,int n2,int P[]);                    //�и�ʽ�����Dijkstra����
    void Init()                                             //ͼ�ĳ�ʼ�����ú����õ����ԣ�
    {
        GetConnectedComponent();                            //  ��ͨ��֧����
        GetClusCoefficient();                               //  �����ͼ�ľ���ϵ��
        GetFloyedMatrix();                                  //  Floyed����
        GetDiamesterAndRadius();                            //  ֱ�����뾶
    }

    void AddNode(int node1,int node2,int theVal,int road); //��ӱߡ�����
    void FindWay(std::string &s1,std::string &s2);         //����ͼ���������Ѱ�����·��
    int FindNodeNum(std::string &s);                       //������������Ѱ�Ҷ�Ӧ�ĵ���վ������

private:

    //��Ա����
    void GetClusCoefficient();                 //�õ�����ϵ��
    void GetConnectedComponent();              //�õ���ͨ��֧��
    void DFS(int i,bool visited[MAX_VER_NUM]);//������ȱ�����Ϊ��������ȷ����ͨ��
    void GetFloyedMatrix();                    //Floyed�㷨�õ�Floyed����
    void GetDiamesterAndRadius();              //����Floyed����õ�ͼ��ֱ�����뾶


    //��������
    void PutOutWay(int P[],int v,int u);       //����һ�ĵݹ����·��
    void PutOutStation(int P[],int v,int u);   //������ĵݹ����·��
};
#endif // GraphClass
