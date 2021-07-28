#include <iostream>
#include <math.h>
#include "fun.h"
using namespace std;

int main()
{
    int x[20] = {0}; // 用于记录物品取舍

    cout << "穷举法：" << endl;
    int Exvalue1 = Exhaustion(number1, capacity1, weight1, value1, bin1, x);
    int Exvalue2 = Exhaustion(number2, capacity2, weight2, value2, bin2, x);
    int Exvalue3 = Exhaustion(number3, capacity3, weight3, value3, bin3, x);
    int Exvalue4 = Exhaustion(number4, capacity4, weight4, value4, bin4, x);
    cout << "test1：" << Exvalue1 << endl;
    cout << "test2：" << Exvalue2 << endl;
    cout << "test3：" << Exvalue3 << endl;
    cout << "test4：" << Exvalue4 << endl << endl;

    cout << "自顶向下的备忘录法：" << endl;
    initmemo(number1, capacity1);
    int mevalue1 = memo(0, capacity1, number1, weight1, value1);
    path(0, number1, value1, weight1, capacity1, x);
    for(int k = 0; k < number1; k++)
        cout << x[k] << " ";
    cout << endl;

    initmemo(number2, capacity2);
    int mevalue2 = memo(0, capacity2, number2, weight2, value2);
    path(0, number2, value2, weight2, capacity2, x);
    for(int k = 0; k < number2; k++)
        cout << x[k] << " ";
    cout << endl;

    initmemo(number3, capacity3);
    int mevalue3 = memo(0, capacity3, number3, weight3, value3);
    path(0, number3, value3, weight3, capacity3, x);
    for(int k = 0; k < number3; k++)
        cout << x[k] << " ";
    cout << endl;

    initmemo(number4, capacity4);
    int mevalue4 = memo(0, capacity4, number4, weight4, value4);
    path(0, number4, value4, weight4, capacity4, x);
    for(int k = 0; k < number4; k++)
        cout << x[k] << " ";
    cout << endl;

    cout << "test1：" << mevalue1 << endl;
    cout << "test2：" << mevalue2 << endl;
    cout << "test3：" << mevalue3 << endl;
    cout << "test4：" << mevalue4 << endl << endl;

    cout << "动态规划：" << endl;
    int dpvalue1 = dp(number1, capacity1, weight1, value1);
    path2(0, number1, value1, weight1, capacity1, x);
    for(int k = 0; k < number1; k++)
        cout << x[k] << " ";
    cout << endl;

    int dpvalue2 = dp(number2, capacity2, weight2, value2);
    path2(0, number2, value2, weight2, capacity2, x);
    for(int k = 0; k < number2; k++)
        cout << x[k] << " ";
    cout << endl;

    int dpvalue3 = dp(number3, capacity3, weight3, value3);
    path2(0, number3, value3, weight3, capacity3, x);
    for(int k = 0; k < number3; k++)
        cout << x[k] << " ";
    cout << endl;

    int dpvalue4 = dp(number4, capacity4, weight4, value4);
    path2(0, number4, value4, weight4, capacity4, x);
    for(int k = 0; k < number4; k++)
        cout << x[k] << " ";
    cout << endl;

    cout << "test1：" << dpvalue1 << endl;
    cout << "test2：" << dpvalue2 << endl;
    cout << "test3：" << dpvalue3 << endl;
    cout << "test4：" << dpvalue4 << endl << endl;

    cout << "回溯法：" << endl;
    int bvalue1 =  trace(number1, capacity1, weight1, value1, x);
    int bvalue2 =  trace(number2, capacity2, weight2, value2, x);
    int bvalue3 =  trace(number3, capacity3, weight3, value3, x);
    int bvalue4 =  trace(number4, capacity4, weight4, value4, x);
    cout << "test1：" << bvalue1 << endl;
    cout << "test2：" << bvalue2 << endl;
    cout << "test3：" << bvalue3 << endl;
    cout << "test4：" << bvalue4 << endl << endl;

    cout << "分支限界法：" << endl;
    int rvalue1 = branch(number1, capacity1, weight1, value1, x);
    for(int k = 0; k < number1; k++)
        cout << x[k] << " ";
    cout << endl;

    int rvalue2 = branch(number2, capacity2, weight2, value2, x);
    for(int k = 0; k < number2; k++)
        cout << x[k] << " ";
    cout << endl;

    int rvalue3 = branch(number3, capacity3, weight3, value3, x);
    for(int k = 0; k < number3; k++)
        cout << x[k] << " ";
    cout << endl;

    int rvalue4 = branch(number4, capacity4, weight4, value4, x);
    for(int k = 0; k < number4; k++)
        cout << x[k] << " ";
    cout << endl;

    cout << "test1：" << rvalue1 << endl;
    cout << "test2：" << rvalue2 << endl;
    cout << "test3：" << rvalue3 << endl;
    cout << "test4：" << rvalue4 << endl << endl;

    int a[20] = {0}; // 用于描述MC中是否取物品的0-1串
    int mvalue1=0,mvalue2=0,mvalue3=0,mvalue4=0;
    int temp1,temp2,temp3,temp4;
    int i;
    for(i = 0; i < 64; i++){
        temp1 = MC(number1, capacity1, weight1, value1, x, a);
        if(temp1 > mvalue1){
            mvalue1 = temp1;
            for(int k = 0; k < number1; k++)
                x[k] = a[k];
        }
    }
    for(int k = 0; k < number1; k++)
        cout << x[k] << " ";
    cout << endl;

    for(i = 0; i < 8196; i++){
        temp2 = MC(number2, capacity2, weight2, value2, x, a);
        if(temp2 > mvalue2){
            mvalue2 = temp2;
            for(int k = 0; k < number2; k++)
                x[k] = a[k];
        }
    }
    for(int k = 0; k < number2; k++)
        cout << x[k] << " ";
    cout << endl;

    for(i = 0; i < 900000; i++){
        temp3 = MC(number3, capacity3, weight3, value3, x, a);
        if(temp3 > mvalue3){
            mvalue3 = temp3;
            for(int k = 0; k < number3; k++)
                x[k] = a[k];
        }
    }
    for(int k = 0; k < number3; k++)
        cout << x[k] << " ";
    cout << endl;


    for(i = 0; i < 900000; i++){
        temp4 = MC(number4, capacity4, weight4, value4, x, a);
        if(temp4 > mvalue4){
            mvalue4 = temp4;
            for(int k = 0; k < number4; k++)
                x[k] = a[k];
        }
    }
    for(int k = 0; k < number4; k++)
        cout << x[k] << " ";

    cout << endl;
    cout << "蒙特卡洛法：" << endl;
    cout << "test1：" << mvalue1 << endl;
    cout << "test2：" << mvalue2 << endl;
    cout << "test3：" << mvalue3 << endl;
    cout << "test4：" << mvalue4 << endl;

    return 0;
}
