#include <iostream>
#include <math.h>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "Wincrypt.h"

using namespace std;

static int number1 = 4;
static int capacity1 = 6;
static int weight1[4] = {1, 2, 3, 2};
static int value1[4] = {4, 6, 12, 7};
static int bin1[4] = {0};
static int number2 = 10;
static int capacity2 = 30;
static int weight2[10] = {1, 2, 3, 2, 8, 10, 8, 6, 1, 4};
static int value2[10] = {4, 6, 12, 7, 2, 18, 2, 7, 9, 10};
static int bin2[10] = {0};
static int number3 = 15;
static int capacity3 = 30;
static int weight3[15] = {1, 2, 3, 2, 8, 10, 8, 6, 1, 4, 3, 4, 3, 7, 8};
static int value3[15] = {4, 6, 12, 7, 2, 18, 2, 7, 9, 10, 28, 12, 7, 2, 17};
static int bin3[15] = {0};
static int number4 = 20;
static int capacity4 = 50;
static int weight4[20] = {1, 2, 3, 2, 8, 10, 8, 6, 1, 4, 3, 4, 3, 7, 8, 7, 14, 13, 3, 5};
static int value4[20] = {4, 6, 12, 7, 2, 18, 2, 7, 9, 10, 28, 12, 7, 2, 17, 4, 17, 4, 8, 9};
static int bin4[20] = {0};

/*
    用于分支限界法
    关键是对树中每一个结点，其应该存储从根到达该结点
    的路径上的重量，价值总和。同时为了剪枝，存储结点
    的价值上界
*/
typedef struct node{
    int i; // 结点层次
    int w;
    int v;
    int x[20];
    double ub;
}BNode;


// 穷举法
void binadd(int bin[], int number);
int Exhaustion(int number, int capacity, int weight[],int value[],int bin[], int x[]);

// 自顶向下的备忘录法
int memo(int i, int j, int number, int weight[], int value[]);
void initmemo(int number, int capacity);
int max_of_two(int a, int b);
void path(int i, int number, int value[], int weight[], int capacity, int x[]);

// 动态规划
int dp(int number, int capacity, int weight[], int value[]);
int min_of_two(int a, int b);
void path2(int i, int number, int value[], int weight[], int capacity, int x[]);

// 回溯法
void backtrace(int number, int capacity, int weight[], int value[], int &bestv, int cw, int cv, int i, int x[]);
int trace(int number, int capacity, int weight[], int value[], int x[]);

// 分支限界法
void bound(int number, int capacity, int weight[], int value[],BNode &a);
int branch(int number, int capacity, int weight[], int value[], int bestx[]);

// 蒙特卡洛
int MC(int number, int capacity, int weight[],int value[], int x[], int a[]);
void random(int number, int a[]);
