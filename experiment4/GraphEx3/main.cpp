#include <iostream>
#include<cstdio>
#include<string>
#include<sstream>
#include<fstream>
#include "GraphClass.h"

/**
*����ִ�еĿ���
*@param READ_TEST_FILE Ϊ����һ�Ŀ��أ�1Ϊִ�У�0Ϊ�ر�
*@param TEST_2 Ϊ������Ŀ��أ�1Ϊִ�У�0Ϊ�ر�
*/
#define READ_TEST_FILE 1
#define TEST_2 1

using namespace std;



int main() {

    /**����һִ�е�main������*/
    if(READ_TEST_FILE)
    {
        int node_num;
        int edge_num;
        int ca = 1;
        fstream fp("stu.in");

        if (!fp.is_open()) {
            printf("There is an error in reading file stu.in��\n");
            return -1;
        }

        while (GetData(fp,node_num,edge_num) != false) {

            //�������ʾ���ı��
            cout<<endl;
            cout<<"case "<<ca++<<":"<<endl;

            //ÿ��ʾ���еĻ�������
            int start_idx, end_idx, weight;

            //����ͼ����
            Mgraph *g = new Mgraph(node_num,edge_num);


            //�����ļ����ݶ�ͼ���г�ʼ��
            for (int i = 0; i < edge_num; i++) {
                GetData(fp,start_idx,end_idx,weight);           //���ļ��ж������Ϣ
                g->AddNode(start_idx,end_idx,weight,0);         //����Ϣ���뵽ͼ�ж�Ӧ���ͱ�
            }


            g->Init();      //ͼ�ĳ�ʼ������������ͼ����ͨ�ȡ��������ϵ����floyed����ֱ����뾶


            //��ʽ�������ͨ��񡢸��������
            cout<<"connected:" <<(g->ConnectedComponent==1)<<endl;
            cout<<"degree distribution:"<<endl;
            for(int i=0; i<g->vexnum; i++)
            {
                cout<<"node"<<g->vertices[i].val<<":"<<g->vertices[i].degree<<",";
            }
            cout<<endl;

            //����ʽ���ͼ�ľ���ϵ��
            double c = g->ClusCoefficient;
            printf("clustering coefficient:%f\n", c);

            //��ͼ��ͨ���ͼ��1��3��Dijkstra�㷨�����·����ֱ�����뾶
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
    }//������������


    /**���Զ�����ͼ*/
    if(TEST_2)
    {
        //��ȡ���ݴ���������·ͼ
        fstream fp("metro.txt");
        if(!fp.is_open())
        {
            cerr<<"Failed to open the file to create the subway map graph!"<<endl;
            return -1;
        }

        int vexnum,roadnum;


        //����ͼ�Ľ������·����
        GetOneData(fp,vexnum);
        GetOneData(fp,roadnum);

        //��������ͼ����
        Mgraph *SubMap = new Mgraph(vexnum);


        //�����ļ��еĽ����Ϣ�����Ϣ
        for(int road=0;road<roadnum;road++)
        {
            //�����i���ߵĽ����
            int RoadVexnum;
            GetOneData(fp,RoadVexnum);

            //˳��ѭ����������ߵ���Ϣ�����뵽����ͼ��
            int Station,D,preStation;
            for(int k=0;k<RoadVexnum;k++)
            {
                GetOneData(fp,Station);
                GetOneData(fp,D);

                //���ý������һ���֮��ʱ������Ϊ�㣬��Ϊ·����㣬���򽫱�Ȩ������Ӧ��
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

        //�������վ��Ӧ��ŵ����ƣ���������Ӧ���
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
        //�����ļ��Դ���ͼ����



        //����ͼ�ĳ�ʼ����������ͨ��֧������������ϵ����floyed�������Ƚ��ֱ����뾶
        SubMap->Init();

        //��ӡ�������������Ϣ
        //��ͨ
        cout<<(SubMap->ConnectedComponent==1)<<endl;

        //��໻��վ��
        cout<<"��໻��վ�㣺"<<SubMap->MaxConnectedStation<<"."<<SubMap->vertices[SubMap->MaxConnectedStation].name<<endl;
        cout<<"����ͼֱ����"<<SubMap->Diamester<<endl;
        cout<<"����ͼ�뾶��"<<SubMap->Radius<<endl;


        //����վ�����Ʋ�ѯ���·���м�˾�վ
        string s1;
        string s2;
        cout<<"�����������ѯվ������ƣ�"<<endl;
        SubMap->FindWay(s1,s2);

        //�ͷſռ�
        delete SubMap;
    }//else if test_2


    return 0;
}

