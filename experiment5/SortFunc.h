#ifndef SortFunc.h
#define SortFunc.h

#include <iostream>
#include <vector>


#define MAX 1000
using namespace std;

int FindMiddleMilk(int n,int milk[]);
void QuickSort(int l,int r,int milk[]);
int FindM(int l,int r,int milk[]);
void Temp(int &a,int &b);


int *Maxk(int k,int n,int arr[]);
void Init(int k,int arr[]);
void PushDown(int i,int k,int arr[]);


void Msort(int *start,int *_end,int M);;
void QuickjSort(int l,int r,int *start,int *_end);
int FindPivot(int l,int r,int *start,int *_end);
void findPeriod(int *start,int *_end,int M,int N);

#endif // SortFunc
