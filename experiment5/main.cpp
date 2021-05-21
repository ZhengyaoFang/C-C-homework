#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "SortFunc.h"

using namespace std;
#define ms 10000
void test1(){
    int caseNum; //表示测试轮数
    int n;
    int ans[ms];
    int a[ms];
    if (freopen("5_1_input_5.in", "r", stdin) == NULL) {
		printf("There is an error in reading file 5_1_input_5.in");
    }
    scanf("%d", &caseNum);
    for (int case1 = 0; case1 < caseNum; case1++) {
        printf("==== Case %d ====\n", case1 + 1);
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }

  //      for(int i=0;i<n;i++)
  //          cout<<a[i]<<endl;

        ans[case1] = FindMiddleMilk(n,a);
        printf("ans is:%d\n", ans[case1]);
        printf("\n");
    }
    fclose(stdin);
}

void test2(){
	int caseNum; //表示测试轮数
	if (freopen("5_2_input_5.in", "r", stdin) == NULL) {
		printf("There is an error in reading file 5_2_input_5.in");
    }
	scanf("%d", &caseNum);
    int case1 = 0;
    for (; case1 < caseNum; case1++) {
		int k,N;
        scanf("%d%d", &k, &N);
        int arr[MAX];
        int i = 0;
        for (; i < N; i++) {
            scanf("%d", &arr[i]);
        }
        int *res;
		res = Maxk(k,N,arr);
		printf("==== Case %d ====\nres : ", case1 + 1);
        for (i = 0; i < k; i++) {
            printf("%d ",res[i]);
        }
    }
	fclose(stdin);
}



int main()
{
   int N, M; //分别存储时间的段数和学生的个数
   int caseNum = 0;
   int start[1002];
   int _end[1002];

   test1();

   if (freopen("5_3_input.in", "r", stdin) == NULL) {
		printf("There is an error in reading file 5_3_input.in");
    }

   while(scanf("%d %d",&N,&M)!=EOF){
       caseNum++;
       printf("==== Case %d ====\n",caseNum);
       for(int i = 0; i < M;i++){
           scanf("%d %d",&start[i],&_end[i]);
       }
       Msort(start, _end, M);
       findPeriod(start, _end, M, N);
   }
   fclose(stdin);
}
