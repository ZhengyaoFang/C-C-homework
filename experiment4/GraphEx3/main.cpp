#include <iostream>
#include<cstdio>
#include<string>
#include<sstream>

#include<fstream>
#include "GraphClass.h"
#define READ_TEST_FILE 0
#define TEST_2 1

using namespace std;


int main() {

    if(READ_TEST_FILE)
    {


        int node_num;
        int edge_num;
        int ca = 1;
        if (freopen("stu.in", "r", stdin) == NULL) {
            printf("There is an error in reading file stu.in");
        }



        while (scanf("%d %d\n", &node_num, &edge_num) != EOF) {


            printf("\ncase %d:\n", ca++);

            int start_idx, end_idx, weight;

            Mgraph *g = new Mgraph(node_num,edge_num);




            /*
            for(int i = 0; i < node_num; i++) {
                sprintf(g.vertices[i].val, "%d", i);
            }
            */

            for (int i = 0; i < edge_num; i++) {
                scanf("%d %d %d\n", &start_idx, &end_idx, &weight);
                g->AdjMatrix[start_idx][end_idx].val = weight;
                g->AdjMatrix[end_idx][start_idx].val = weight;
                g->AdjMatrix[start_idx][end_idx].exist=true;
                g->AdjMatrix[end_idx][start_idx].exist=true;
                g->vertices[start_idx].degree++;
                g->vertices[end_idx].degree++;
            }
            g->Init();

            printf("connected: %d\n", g->ConnectedComponent==1);

            //int *degree = (int *)malloc(sizeof(int) * g.N);
            //nodeDegree(g, degree);
            printf("degree distribution:\n");
            for(int i=0; i<g->vexnum; i++)
            {
                printf("node%d:%d,", g->vertices[i].val, g->vertices[i].degree);
            }
            printf("\n");
            //free(degree);

            double c = g->ClusCoefficient;
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
                printf("diameter:%d\n", diameter);
                printf("radius:%d\n", radius);
            }
            delete g;
        }
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
            fp>>RoadVexnum;
            int Station,D,preStation;
            for(int k=0;k<RoadVexnum;k++)
            {
                fp>>Station;
                fp>>D;
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
        fp2>>StationNum;
        for(int i=0;i<StationNum;i++)
        {
            int num;
            fp2>>num;
            fp2>>SubMap->vertices[num].name;
        }
        fp2.close();
        //创建图结束

        SubMap->Init();

        //连通
        cout<<SubMap->ConnectedComponent<<endl;
        cout<<SubMap->MaxConnectedStation<<endl;
        cout<<SubMap->vertices[200].Road.size()<<endl;








        delete SubMap;
    }//else if test_2


    return 0;
}

