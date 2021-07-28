#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define cl 100001
using namespace std;

void ran(int N){
    FILE *fp;
    if( (fp=fopen("ran.txt","w")) == NULL ){
        printf("Fail to open file!\n");
        exit(0);  //退出程序（结束程序）
    }
    int a;
    char c[cl] = "";
    for(int i = 0; i < N; i++){
        a = rand() % 2;
        c[i] = char(a+48);
    }
    fputs(c, fp);
    fclose(fp);
}

#endif // RANDOM_H_INCLUDED
