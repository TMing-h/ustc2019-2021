#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include "sort.h"

#define RANGE 1000000
#define N 50000

using namespace std;

int main()
{
    // 变量声明等初始操作
    FILE *fp1,*fp2;
    if( (fp1=fopen("result1.txt","a")) == NULL ){ // 该文件存储排序平均时间与方差
        printf("Fail to open file!\n");
        exit(0);
    }
    if( (fp2=fopen("result2.txt","a")) == NULL ){ // 该文件存储排序前一百个结果
        printf("Fail to open file!\n");
        exit(0);
    }
    struct timeval start,stop; // 为了获取更精确的时间，不直接使用time()函数，而是利用timeval结构体
    double start_time, stop_time, delta_time, delta_time_ms;
    int select;
    cout << "选择排序算法 ：（1-4 分别对应插入排序，归并排序，堆排序，快速排序）" << endl;
    cin >> select;
    int n = N; // n给出问题规模
    long *a;
    // 选择排序算法后，每种规模进行10次排序
    while(n <= 500000){
        a = (long *)malloc(sizeof(long)*n);
        for(int j = 0; j < n; j++)
            a[j] = 0; // 初始化数组
        double avtime = 0, variance = 0;
        double s[10] = {0};
        cout << "问题规模 n = " <<  n << endl;
        for(int i = 0; i < 10; i++){
            srand((unsigned)time(NULL)); //使得每次产生不同的随机数
            for(int k = 0; k < n; k++)
                a[k] = ((rand()*32767+rand()) % RANGE) + 1; //产生1-RANGE的随机数
            if(select == 1){
                gettimeofday(&start, NULL);
                insertion_sort(a, n);
            }
            else if(select == 2){
                gettimeofday(&start, NULL);
                merge_sort(a, 0, n-1);
            }
            else if(select == 3){
                gettimeofday(&start, NULL);
                heapsort(a, n);
            }
            else if(select == 4){
                gettimeofday(&start, NULL);
                quicksort(a, 0, n-1);
            }
            else
                break;
            gettimeofday(&stop, NULL);
            start_time = ((double)start.tv_sec*1000000+(double)start.tv_usec);
            stop_time = ((double)stop.tv_sec*1000000+(double)stop.tv_usec);
            delta_time = stop_time - start_time; // 单位：微秒
            delta_time_ms = delta_time / 1000; // 排序时间 单位：毫秒
            avtime = avtime + delta_time_ms;
            s[i] = delta_time_ms;
            //cout << "排序时间：" << delta_time_ms << "毫秒" <<endl;
        }
        avtime = avtime / 10; // 平均时间
        for(int m = 0; m < 10; m++)
            variance = variance + (s[m]-avtime)*(s[m]-avtime);
        variance = variance / 9; // 方差
        cout << "平均时间：" << avtime << "毫秒 方差：" << variance << endl;

        // 文件操作
        if(select == 1)
            fprintf(fp1,"插入排序， 规模：%d\n", n);
        else if(select == 2)
            fprintf(fp1,"归并排序， 规模：%d\n", n);
        else if(select == 3)
            fprintf(fp1,"堆排序， 规模：%d\n", n);
        else if(select == 4)
            fprintf(fp1,"快速排序， 规模：%d\n", n);
        fprintf(fp1,"平均时间：%lf 毫秒  方差：%lf\n", avtime, variance);
        fprintf(fp1,"\n");

        if(n < 500000){
            free(a);
            n = n + 50000; // 规模增加
        }
        else
            break;
    }
    fprintf(fp1,"\n");

    // 保存规模500000， 第 10 次排序结果的前100位
    if(select == 1){
        fprintf(fp2,"插入排序， 规模：500000 ，第 10 次排序结果的前100位：\n");
        for(int l = 0; l < 100; l++)
            fprintf(fp2, "%ld, ", a[l]);
        fprintf(fp2, "\n\n");
    }
    else if(select == 2){
        fprintf(fp2,"归并排序， 规模：500000 ，第 10 次排序结果的前100位：\n");
        for(int l = 0; l < 100; l++)
            fprintf(fp2, "%ld, ", a[l]);
        fprintf(fp2, "\n\n");
    }
    else if(select == 3){
        fprintf(fp2,"堆排序， 规模：500000 ，第 10 次排序结果的前100位：\n");
        for(int l = 0; l < 100; l++)
            fprintf(fp2, "%ld, ", a[l]);
        fprintf(fp2, "\n\n");
    }
    else if(select == 4){
        fprintf(fp2,"快速排序， 规模：500000 ，第 10 次排序结果的前100位：\n");
        for(int l = 0; l < 100; l++)
            fprintf(fp2, "%ld, ", a[l]);
        fprintf(fp2, "\n\n");
    }
    free(a);

    fclose(fp1);
    fclose(fp2);
    return 0;
}
