#include <iostream>
#include<cstdio>
#include "GraphClass.h"



int main() {
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



    return 0;
}

