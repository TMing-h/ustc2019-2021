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
    // ���������ȳ�ʼ����
    FILE *fp1,*fp2;
    if( (fp1=fopen("result1.txt","a")) == NULL ){ // ���ļ��洢����ƽ��ʱ���뷽��
        printf("Fail to open file!\n");
        exit(0);
    }
    if( (fp2=fopen("result2.txt","a")) == NULL ){ // ���ļ��洢����ǰһ�ٸ����
        printf("Fail to open file!\n");
        exit(0);
    }
    struct timeval start,stop; // Ϊ�˻�ȡ����ȷ��ʱ�䣬��ֱ��ʹ��time()��������������timeval�ṹ��
    double start_time, stop_time, delta_time, delta_time_ms;
    int select;
    cout << "ѡ�������㷨 ����1-4 �ֱ��Ӧ�������򣬹鲢���򣬶����򣬿�������" << endl;
    cin >> select;
    int n = N; // n���������ģ
    long *a;
    // ѡ�������㷨��ÿ�ֹ�ģ����10������
    while(n <= 500000){
        a = (long *)malloc(sizeof(long)*n);
        for(int j = 0; j < n; j++)
            a[j] = 0; // ��ʼ������
        double avtime = 0, variance = 0;
        double s[10] = {0};
        cout << "�����ģ n = " <<  n << endl;
        for(int i = 0; i < 10; i++){
            srand((unsigned)time(NULL)); //ʹ��ÿ�β�����ͬ�������
            for(int k = 0; k < n; k++)
                a[k] = ((rand()*32767+rand()) % RANGE) + 1; //����1-RANGE�������
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
            delta_time = stop_time - start_time; // ��λ��΢��
            delta_time_ms = delta_time / 1000; // ����ʱ�� ��λ������
            avtime = avtime + delta_time_ms;
            s[i] = delta_time_ms;
            //cout << "����ʱ�䣺" << delta_time_ms << "����" <<endl;
        }
        avtime = avtime / 10; // ƽ��ʱ��
        for(int m = 0; m < 10; m++)
            variance = variance + (s[m]-avtime)*(s[m]-avtime);
        variance = variance / 9; // ����
        cout << "ƽ��ʱ�䣺" << avtime << "���� ���" << variance << endl;

        // �ļ�����
        if(select == 1)
            fprintf(fp1,"�������� ��ģ��%d\n", n);
        else if(select == 2)
            fprintf(fp1,"�鲢���� ��ģ��%d\n", n);
        else if(select == 3)
            fprintf(fp1,"������ ��ģ��%d\n", n);
        else if(select == 4)
            fprintf(fp1,"�������� ��ģ��%d\n", n);
        fprintf(fp1,"ƽ��ʱ�䣺%lf ����  ���%lf\n", avtime, variance);
        fprintf(fp1,"\n");

        if(n < 500000){
            free(a);
            n = n + 50000; // ��ģ����
        }
        else
            break;
    }
    fprintf(fp1,"\n");

    // �����ģ500000�� �� 10 ����������ǰ100λ
    if(select == 1){
        fprintf(fp2,"�������� ��ģ��500000 ���� 10 ����������ǰ100λ��\n");
        for(int l = 0; l < 100; l++)
            fprintf(fp2, "%ld, ", a[l]);
        fprintf(fp2, "\n\n");
    }
    else if(select == 2){
        fprintf(fp2,"�鲢���� ��ģ��500000 ���� 10 ����������ǰ100λ��\n");
        for(int l = 0; l < 100; l++)
            fprintf(fp2, "%ld, ", a[l]);
        fprintf(fp2, "\n\n");
    }
    else if(select == 3){
        fprintf(fp2,"������ ��ģ��500000 ���� 10 ����������ǰ100λ��\n");
        for(int l = 0; l < 100; l++)
            fprintf(fp2, "%ld, ", a[l]);
        fprintf(fp2, "\n\n");
    }
    else if(select == 4){
        fprintf(fp2,"�������� ��ģ��500000 ���� 10 ����������ǰ100λ��\n");
        for(int l = 0; l < 100; l++)
            fprintf(fp2, "%ld, ", a[l]);
        fprintf(fp2, "\n\n");
    }
    free(a);

    fclose(fp1);
    fclose(fp2);
    return 0;
}
