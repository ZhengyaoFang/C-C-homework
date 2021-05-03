#ifndef GraphClass
#define GraphClass


#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#define MAX_VER_NUM 1000
#define INFINITY1 999
#define MAX_NAME 100

//����Ϸ��Լ�飬��ǿ����³����
bool GetData(std::fstream &fp,int &num1,int &num2);
bool GetData(std::fstream &fp,int &node1,int &node2,int &theVal);
bool GetOneData(std::fstream &fp,int &num);
bool GetString(std::string &s);



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


    //��Ա����
    void GetClusCoefficient();
    void GetConnectedComponent();
    void DFS(int i,bool visited[MAX_VER_NUM]);//ȷ����ͨ��
    void GetFloyedMatrix();
    void GetDiamesterAndRadius();
    //��������
    void PutOutWay(int P[],int v,int u);
    void PutOutStation(int P[],int v,int u);




};



#endif // GraphClass
