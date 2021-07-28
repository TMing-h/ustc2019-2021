#include "fun.h"
int m[50][50] = {{0}}; // 用于备忘录
int n[50][50] = {{0}}; // 用于动态规划

/*
    穷举法：
    对于0-1背包问题，每个物品要么取要么不取，故一共有2^n种情况
    如果记1为取，0为不取，则可以用一长为n的0-1串来表示一种情况
    所以关键是穷举长为n的0-1串的所有取值，这在函数binadd中实现
*/
// 二进制加法，用来穷举2^n种情况
void binadd(int bin[], int number){
    int carry=0;
    bin[0] += 1;
    for(int i = 0; i < number; i++){
        bin[i] += carry;
        carry = bin[i] / 2;
        bin[i] = bin[i] % 2;
        if(carry == 0)
            return;
    }
}
int Exhaustion(int number, int capacity, int weight[], int value[], int bin[], int x[]){
    int temp = 0; // 记录当前方案价值
    int maxvalue = 0; // 最大价值
    int cur_cap = capacity; // 记录当前背包剩余容量
    int i,j;
    for(i = 0; i < pow(2, number); i++){ // 穷举2^n种情况
        temp = 0;
        cur_cap = capacity;
        for(j = 0; j < number; j++){ // 对于每一种情况，扫描0-1串
            if(bin[j] == 1){
                if(weight[j] > cur_cap)
                    break;
                else{
                    temp = temp + value[j];
                    cur_cap = cur_cap - weight[j];
                }
            }
        }
        if(temp > maxvalue){
            maxvalue = temp;
            for(int k = 0; k < number; k++)
                x[k] = bin[k];
        }
        binadd(bin, number);
    }
    for(int k = 0; k < number; k++)
        cout << x[k] << " ";
    cout << endl;
    return maxvalue;
}


int max_of_two(int a, int b){
    if(a >= b)
        return a;
    return b;
}
int min_of_two(int a, int b){
    if(a >= b)
        return b;
    return a;
}

/*
    备忘录法+动态规划
    二者思路基本一致，都是利用递归的思想
    备忘录法采取自上而下直接递归的方式求解，过程中为每个解过的子问题建立记录，避免相同子问题的重复求解；
    动态规划则是建立一个表格，自底向上从最小子问题开始把每一个子问题的解填入表格中，直到出现原问题的解。
    二者最大区别是动态规划自底向上求解了所有的子问题，而备忘录法只求解需要求解的子问题。

*/
void initmemo(int number, int capacity){
    for(int i = 0; i < number; i++){
        for(int j = 0; j <= capacity; j++)
            m[i][j] = -1;
    }
}
int memo(int i, int j, int number, int weight[], int value[]){
    if(m[i][j] > 0)
        return m[i][j];
    if(i == number-1){
        if(j >= weight[i])
            m[i][j] = value[i];
        else
            m[i][j] = 0;
        return m[i][j];
    }
    if(j >= weight[i]){
        m[i][j] = max_of_two(memo(i+1,j,number,weight,value), (memo(i+1,j-weight[i],number,weight,value)+value[i]));
        return m[i][j];
    }
    else{
        m[i][j] = memo(i+1,j,number,weight,value);
        return m[i][j];
    }
}
void path(int i, int number, int value[], int weight[], int capacity, int x[]){
    if(i == number-1){
		if(m[i][capacity] == value[i])
			x[i] = 1;
		else
			x[i] = 0;
		return;
	}
    if (m[i][capacity] == m[i+1][capacity]){
        x[i] = 0;
        path(i+1, number, value, weight, capacity, x);
        return;
    }
    else{
        x[i] = 1;
        path(i+1, number, value, weight, capacity-weight[i], x);
        return;
    }
}

int dp(int number, int capacity, int weight[], int value[]){
    int jMax = min_of_two(weight[number-1]-1, capacity);
    for(int j = 0; j <= jMax; j++)
        n[number-1][j] = 0;
    for(int j = weight[number-1]; j <= capacity; j++)
        n[number-1][j] = value[number-1];
    for(int i = number-2; i > 0; i--){
        jMax = min_of_two(weight[i]-1, capacity);
        for(int j = 0; j <= jMax; j++)
            n[i][j] = n[i+1][j];
        for(int j = weight[i]; j <= capacity; j++)
            n[i][j] = max_of_two(n[i+1][j],(n[i+1][j-weight[i]]+value[i]));
    }
    if(capacity >= weight[0])
        n[0][capacity] = max_of_two(n[1][capacity],(n[1][capacity-weight[0]]+value[0]));
    else
        n[0][capacity] = n[1][capacity];
    return n[0][capacity];
}

void path2(int i, int number, int value[], int weight[], int capacity, int x[])
{
	for (int i = 0; i < number; i++){
		if (n[i][capacity] == n[i + 1][capacity])
            x[i] = 0;
		else {
		    x[i] = 1;
            capacity -= weight[i];
        }
	}
}


/*
    回溯法
    深度优先遍历
*/
int trace(int number, int capacity, int weight[], int value[], int x[]){
    int cw = 0;
    int cv = 0;
    int bestv = 0;
    backtrace(number, capacity, weight, value, bestv, cw, cv, 0, x);
    return bestv;
}
void backtrace(int number, int capacity, int weight[], int value[], int &bestv, int cw, int cv, int i, int x[]){
    if(i == number){
        if(bestv < cv){
            bestv = cv;
            for(int k = 0; k < number; k++)
                cout << x[k] << " ";
            cout << endl;
        }
    }
    else{
        if(cw + weight[i] <= capacity){
            x[i] = 1;
            cw += weight[i];
            cv += value[i];
            backtrace(number, capacity, weight, value, bestv, cw, cv, i+1, x);
            cw -= weight[i];
            cv -= value[i];
        }
        x[i] = 0;
        backtrace(number, capacity, weight, value, bestv, cw, cv, i+1, x);
    }
}

/*
    分支限界法
    采用广度优先遍历，没有利用递归。
    由于需要一次性产生所有的孩子结点，所以需要一个队列将其存储，
    也正因为如此，需要同时存储多个结点的weight,value等信息，所以
    建立一个结构体来表示结点会更方便。
*/
void bound(int number, int capacity, int weight[], int value[], BNode &a){
    int cleft = capacity - a.w;
    double b = a.v;
    int i = a.i;
    while(i < number && weight[i] <= cleft){
        cleft -= weight[i];
        b += value[i];
        i++;
    }
    if(i < number){
        double bv = value[i];
        b += (bv/weight[i])*cleft;
    }
    a.ub = b;
}
int branch(int number, int capacity, int weight[], int value[], int bestx[]){
    queue<BNode> q;
    int bestv = 0;
    BNode p,lc,rc;
    p.i=0;
    p.w=0;
    p.v=0;
    bound(number, capacity, weight, value, p);
    q.push(p);
    while(!q.empty()){
        p = q.front();
        q.pop();
        if(p.w + weight[p.i] <= capacity){
            lc.i = p.i + 1;
            lc.w = p.w + weight[p.i];
            lc.v = p.v + value[p.i];
            for(int j = 0; j < number; j++)
                lc.x[j] = p.x[j];
            lc.x[p.i] = 1;
            bound(number, capacity, weight, value, lc);
            if(lc.i == number){
                if(lc.v > bestv){
                    bestv  = lc.v;
                    for(int j = 0; j < number; j++)
                        bestx[j] = lc.x[j];
                }
            }
            else
                q.push(lc);
        }
        rc.i = p.i + 1;
        rc.w = p.w;
        rc.v = p.v;
        for(int j = 0; j < number; j++)
            rc.x[j] = p.x[j];
        rc.x[p.i] = 0;
        bound(number, capacity, weight, value, rc);
        if(rc.i == number){
            if(rc.v > bestv){
                bestv  = rc.v;
                for(int j = 0; j < number; j++)
                    bestx[j] = rc.x[j];
            }
        }
        else{
            if(rc.ub > bestv)
                q.push(rc);
        }
    }
    return bestv;
}

/*
    蒙特卡洛法
    代码结构与穷举法类似，即是用一个0-1串来表示各物品的取与不取，
    然后计算不同情况下的价值，取最大值。
    不同之处在于，此时并不穷举2^n种情况，而是对一个数组a[n]，随机产生
    它的每一位，从而得到一个随机的0-1串作为一种情况。
    所以算法求解结果正确与否关键在于随机数的产生。
*/
void random(int number, int a[]){
    /*
    HCRYPTPROV hcp;
	unsigned char rdata[32];
	int i;
	if (!CryptAcquireContextA(&hcp, NULL, "Microsoft Base Cryptographic Provider v1.0", PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
		return;
	}
	CryptGenRandom(hcp, 32, rdata);
	for(i=0; i<number; i++)
		a[i] = rdata[i]%2;
		*/

    for(int i = 0; i < number; i++){
        srand(time(NULL) + rand());
		a[i] = rand()%2;
    }
}
int MC(int number, int capacity, int weight[],int value[], int x[], int a[]){
    random(number, a);
    int temp = 0; // 记录当前方案价值
    int cur_cap = capacity; // 记录当前背包剩余容量
    int i,j;
    for(j = 0; j < number; j++){ // 对于每一种情况，扫描0-1串
        if(a[j] == 1){
            if(weight[j] > cur_cap)
                break;
            else{
                temp = temp + value[j];
                cur_cap = cur_cap - weight[j];
            }
        }
    }
    return temp;
}
