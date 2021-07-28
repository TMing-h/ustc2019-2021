#include "fun.h"
int m[50][50] = {{0}}; // ���ڱ���¼
int n[50][50] = {{0}}; // ���ڶ�̬�滮

/*
    ��ٷ���
    ����0-1�������⣬ÿ����ƷҪôȡҪô��ȡ����һ����2^n�����
    �����1Ϊȡ��0Ϊ��ȡ���������һ��Ϊn��0-1������ʾһ�����
    ���Թؼ�����ٳ�Ϊn��0-1��������ȡֵ�����ں���binadd��ʵ��
*/
// �����Ƽӷ����������2^n�����
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
    int temp = 0; // ��¼��ǰ������ֵ
    int maxvalue = 0; // ����ֵ
    int cur_cap = capacity; // ��¼��ǰ����ʣ������
    int i,j;
    for(i = 0; i < pow(2, number); i++){ // ���2^n�����
        temp = 0;
        cur_cap = capacity;
        for(j = 0; j < number; j++){ // ����ÿһ�������ɨ��0-1��
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
    ����¼��+��̬�滮
    ����˼·����һ�£��������õݹ��˼��
    ����¼����ȡ���϶���ֱ�ӵݹ�ķ�ʽ��⣬������Ϊÿ������������⽨����¼��������ͬ��������ظ���⣻
    ��̬�滮���ǽ���һ������Ե����ϴ���С�����⿪ʼ��ÿһ��������Ľ��������У�ֱ������ԭ����Ľ⡣
    ������������Ƕ�̬�滮�Ե�������������е������⣬������¼��ֻ�����Ҫ���������⡣

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
    ���ݷ�
    ������ȱ���
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
    ��֧�޽編
    ���ù�����ȱ�����û�����õݹ顣
    ������Ҫһ���Բ������еĺ��ӽ�㣬������Ҫһ�����н���洢��
    Ҳ����Ϊ��ˣ���Ҫͬʱ�洢�������weight,value����Ϣ������
    ����һ���ṹ������ʾ��������㡣
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
    ���ؿ��巨
    ����ṹ����ٷ����ƣ�������һ��0-1������ʾ����Ʒ��ȡ�벻ȡ��
    Ȼ����㲻ͬ����µļ�ֵ��ȡ���ֵ��
    ��֮ͬ�����ڣ���ʱ�������2^n����������Ƕ�һ������a[n]���������
    ����ÿһλ���Ӷ��õ�һ�������0-1����Ϊһ�������
    �����㷨�������ȷ���ؼ�����������Ĳ�����
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
    int temp = 0; // ��¼��ǰ������ֵ
    int cur_cap = capacity; // ��¼��ǰ����ʣ������
    int i,j;
    for(j = 0; j < number; j++){ // ����ÿһ�������ɨ��0-1��
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
