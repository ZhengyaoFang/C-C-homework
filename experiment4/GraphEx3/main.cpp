#include <iostream>
#include<cstdio>
#include<string>
#include<sstream>

#include<fstream>
#include "GraphClass.h"
#define READ_TEST_FILE 1
#define TEST_2 1

using namespace std;


int main() {

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


            cout<<endl;
            cout<<"case "<<ca++<<":"<<endl;


            int start_idx, end_idx, weight;

            Mgraph *g = new Mgraph(node_num,edge_num);




            /*
            for(int i = 0; i < node_num; i++) {
                sprintf(g.vertices[i].val, "%d", i);
            }
            */

            for (int i = 0; i < edge_num; i++) {
                GetData(fp,start_idx,end_idx,weight);
                g->AddNode(start_idx,end_idx,weight,0);
            }
            g->Init();

            cout<<"connected:" <<(g->ConnectedComponent==1)<<endl;
            //printf("connected: %d\n", g->ConnectedComponent==1);

            //int *degree = (int *)malloc(sizeof(int) * g.N);
            //nodeDegree(g, degree);
            cout<<"degree distribution:"<<endl;
            //printf("degree distribution:\n");

            for(int i=0; i<g->vexnum; i++)
            {
                cout<<"node"<<g->vertices[i].val<<":"<<g->vertices[i].degree<<",";
                //printf("node%d:%d,", g->vertices[i].val, g->vertices[i].degree);
            }
            cout<<endl;
            //printf("\n");
            //free(degree);

            double c = g->ClusCoefficient;

            //cout<<"clustering coefficient:"<<c<<endl;
            printf("clustering coefficient:%f\n", c);

            if(g->ConnectedComponent==1)
            {
                /*
                int *short_path = (int *)malloc(sizeof(int) * g.N);
                int dis = dijkstra(g, 1, 3, short_path);
                printf("the shortest path between 1 and 3: %d\n", dis);
                printPath(dis, short_path, g);
                free(short_path);
                //*/
                g->Dijkstra(1,3);

                int diameter, radius;
                diameter=g->Diamester;
                radius=g->Radius;

                cout<<"diamester:"<<diameter<<endl;
                //printf("diameter:%d\n", diameter);
                cout<<"radius:"<<radius<<endl;
                //printf("radius:%d\n", radius);
            }
            delete g;
        }
        fp.close();
    }//测试用例部分
    else if(TEST_2)
    {
        //读取数据创建地铁线路图
        fstream fp("metro.txt");
        if(!fp.is_open())
        {
            cerr<<"Failed to open the file to create the subway map graph!"<<endl;
            return -1;
        }

        int vexnum,roadnum;
        fp>>vexnum;
        fp>>roadnum;
        Mgraph *SubMap = new Mgraph(vexnum);


        for(int road=0;road<roadnum;road++)
        {
            int RoadVexnum;
            GetOneData(fp,RoadVexnum);
            //fp>>RoadVexnum;
            int Station,D,preStation;
            for(int k=0;k<RoadVexnum;k++)
            {
                GetOneData(fp,Station);
                GetOneData(fp,D);
                //fp>>Station;
                //fp>>D;
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
        //创建图结束

        SubMap->Init();

        //连通
        cout<<SubMap->ConnectedComponent<<endl;
        cout<<SubMap->MaxConnectedStation<<endl;
        cout<<SubMap->vertices[200].Road.size()<<endl;
        string s1="大学城";
        string s2="世界之窗";
        SubMap->FindWay(s1,s2);

        cout<<SubMap->Diamester<<endl;
        cout<<SubMap->Radius<<endl;








        delete SubMap;
    }//else if test_2


    return 0;
}

