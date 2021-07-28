#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"random.h"
#define len 100

using namespace std;

// 计算离差
int diff(int a[], int c[], int n){
    if(n == 0)
        return a[n];
    int d = a[n];
    for(int i = 1; i <= n; i++){
        d = d ^ (c[i] & a[n-i]);
    }
    return d;
}

int main(){
    while(1){
        int rn;
        //变量定义
        FILE *fp;
        int N;
        int L, m, n;
        int fx[len] = {0};
        int bx[len] = {0};
        int tx[len] = {0};
        char c[len] = "";
        int a[len];
        int d;
        char file[len] = "";

        // 初始化
        L = 0;
        m = -1;
        n = 0;
        fx[0] = 1;
        bx[0] = 1;

        char exi[len];
        cout << "press any key to continue（按0退出）：" << endl;
        cin >> exi;
        if(exi[0] == '0')
            return 0;

        cout << "输入随机数个数rn：" << endl;
        cin >> rn;
        ran(rn);
        // 获取输入序列a
        cout << "input the file name：" << endl;
        cin >> file;

        if( (fp=fopen(file, "r")) == NULL ){
            cout << "fail to open file" << endl;
            continue;
        }
        fgets(c, len, fp);
        N = strlen(c);
        for(int i = 0; i < N; i++)
            a[i] = (c[i]-48);

        // 计算
        int i,j;
        for(n = 0; n < N; n++){
            d = diff(a, fx, n);
            if(d == 1){ // 离差为1，需要更新f
                for(j = 0; j < N; j++)
                    tx[j] = fx[j];
                for(j = 0; j < N; j++){
                    if(bx[j]==1)
                        fx[j+n-m]=(fx[j+n-m]+1)%2;
                }
                if(L <= n/2){
                    L = n+1-L;
                    m = n;
                    for(j = 0; j < N; j++)
                        bx[j] = tx[j];
                }
            }
            // 复杂度大大大
            if(L > 10000){
                cout << "线性复杂度大于10000" << endl;
                exit(0);
            }
        }

        // 输出结果
        cout << "该序列线性复杂度 L = " << L << endl;
        cout << "联结多项式为 <";
        cout << fx[0];
        for(i = 1; i < N; i++){
            if(fx[i] != 0)
                cout << "+D^" << i;
        }
        cout << "> " << endl;
        cout << endl;
        fclose(fp);
    }

    return 0;
}
