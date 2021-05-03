#include <iostream>
#include<cstdio>
#include<string>
#include<sstream>
#include<fstream>
#include "GraphClass.h"

/**
*问题执行的开关
*@param READ_TEST_FILE 为问题一的开关，1为执行，0为关闭
*@param TEST_2 为问题二的开关，1为执行，0为关闭
*/
#define READ_TEST_FILE 1
#define TEST_2 1

using namespace std;



int main() {

    /**问题一执行的main函数体*/
    if(READ_TEST_FILE)
    {
        int node_num;
        int edge_num;
        int ca = 1;
        fstream fp("stu.in");

        if (!fp.is_open()) {
            printf("There is an error in reading file stu.in！\n");
            return -1;
        }

        while (GetData(fp,node_num,edge_num) != false) {

            //输出测试示例的标号
            cout<<endl;
            cout<<"case "<<ca++<<":"<<endl;

            //每个示例中的基础变量
            int start_idx, end_idx, weight;

            //创建图对象
            Mgraph *g = new Mgraph(node_num,edge_num);


            //读入文件数据对图进行初始化
            for (int i = 0; i < edge_num; i++) {
                GetData(fp,start_idx,end_idx,weight);           //从文件中读入边信息
                g->AddNode(start_idx,end_idx,weight,0);         //将信息加入到图中对应结点和边
            }


            g->Init();      //图的初始化，包括加载图的连通度、各点聚类系数、floyed矩阵、直径与半径


            //格式化输出连通与否、各顶点度数
            cout<<"connected:" <<(g->ConnectedComponent==1)<<endl;
            cout<<"degree distribution:"<<endl;
            for(int i=0; i<g->vexnum; i++)
            {
                cout<<"node"<<g->vertices[i].val<<":"<<g->vertices[i].degree<<",";
            }
            cout<<endl;

            //按格式输出图的聚类系数
            double c = g->ClusCoefficient;
            printf("clustering coefficient:%f\n", c);

            //若图连通输出图从1到3的Dijkstra算法的最短路径、直径、半径
            if(g->ConnectedComponent==1)
            {
                g->Dijkstra(1,3);

                int diameter, radius;
                diameter=g->Diamester;
                radius=g->Radius;

                cout<<"diamester:"<<diameter<<endl;
                cout<<"radius:"<<radius<<endl;
            }
            delete g;
        }
        fp.close();
    }//测试用例部分


    /**测试二地铁图*/
    if(TEST_2)
    {
        //读取数据创建地铁线路图
        fstream fp("metro.txt");
        if(!fp.is_open())
        {
            cerr<<"Failed to open the file to create the subway map graph!"<<endl;
            return -1;
        }

        int vexnum,roadnum;


        //读入图的结点数、路线数
        GetOneData(fp,vexnum);
        GetOneData(fp,roadnum);

        //创建地铁图对象
        Mgraph *SubMap = new Mgraph(vexnum);


        //读入文件中的结点信息与边信息
        for(int road=0;road<roadnum;road++)
        {
            //读入第i号线的结点数
            int RoadVexnum;
            GetOneData(fp,RoadVexnum);

            //顺次循环读入结点与边的信息并加入到地铁图中
            int Station,D,preStation;
            for(int k=0;k<RoadVexnum;k++)
            {
                GetOneData(fp,Station);
                GetOneData(fp,D);

                //若该结点与上一结点之间时间消耗为零，则为路线起点，否则将边权赋予相应边
                if(D==0)
                {
                    preStation=Station;
                    SubMap->vertices[Station].Road.push_back(road);
                }

                else
                {
                    SubMap->AddNode(Station,preStation,D,road);
                    preStation=Station;
                }

            }
        }
        fp.close();

        //读入地铁站相应标号的名称，赋名到对应结点
        fstream fp2("no2metro.txt");
        if(!fp2.is_open())
        {
            cerr<<"Error!Faild to open the Station name!"<<endl;
            return -1;
        }
        int StationNum;
        GetOneData(fp2,StationNum);
        //fp2>>StationNum;
        for(int i=0;i<StationNum;i++)
        {
            int num;

            GetOneData(fp2,num);
            //fp2>>num;
            fp2>>SubMap->vertices[num].name;
        }
        fp2.close();
        //加载文件以创建图结束



        //地铁图的初始化，包括连通分支数、各结点聚类系数、floyed矩阵、最大度结点直径与半径
        SubMap->Init();

        //打印输出问题的相关信息
        //连通
        cout<<(SubMap->ConnectedComponent==1)<<endl;

        //最多换乘站点
        cout<<"最多换乘站点："<<SubMap->MaxConnectedStation<<"."<<SubMap->vertices[SubMap->MaxConnectedStation].name<<endl;
        cout<<"地铁图直径："<<SubMap->Diamester<<endl;
        cout<<"地铁图半径："<<SubMap->Radius<<endl;


        //输入站点名称查询最短路与中间乘经站
        string s1;
        string s2;
        cout<<"请输入您想查询站点的名称："<<endl;
        SubMap->FindWay(s1,s2);

        //释放空间
        delete SubMap;
    }//else if test_2


    return 0;
}

