void exchange(int &a, int &b){
    int temp;
    temp = a;
    a = b;
    b = temp;
}
/*
int max_of_two(int a, int b){
    if(a >= b)
        return a;
    return b;
}
*/
/*
    ̰���㷨��
    ��Ҫȷ���������ڣ�Ŀ����Ϊ��ʹ�������
    Ϊ��Ҫ��
    �ٹ����Ʊ�������������
    ��������Ʊʱ׬ȡ�������
*/
/*
int greedy_maxProfit(int *prices, int pricesSize, int fee){
    // buyΪ�����Ʊ��ʣ�µ��������profitΪ������
    // ��һ��������
    // �����Ʊ������-prices[0]
    int buy = -prices[0];
    // ��һ��������
    int profit = 0;
    /*
        �ӵڶ��쿪ʼ��
        �����������������������Ϊ��������
        ������������������Ϊ��������
    */
/*
    for(int i = 1; i < pricesSize; i++){
        buy = max_of_two(buy, profit-prices[i]);
        profit = max_of_two(profit, profit+prices[i]-fee);
    }
}
*/
/*
int dp_maxProfit(int *prices, int pricesSize, int fee){
    int **dpt = (int **)malloc(sizeof(int)*pricesSize);
    for(int m = 0; m < pricesSize; m++)
        dpt[m] = (int *)malloc(sizeof(int)*2);
    dpt[0][0] = 0;
    dpt[0][1] = -prices[0];
    for(int i = 1; i < pricesSize; i++){
        dpt[i][0] = max_with_two(dpt[i-1][0], dpt[i-1][1]+prices[i]-fee);
        dpt[i][1] = max_with_two(dpt[i-1][1], dpt[i-1][0]+prices[i]);
    }
    return dpt[n-1][0];
}
*/
/*
int greedy_maxProfit(int *prices, int pricesSize, int fee){
    int buy; // ���򻨷�
    int sell; // ��������
    int profit; // ������ profit = sell-buy-fee
    int sprofit = 0;
    int i = 0; // ָʾ��Ʊ����
    int j = 0; // ָʾ��Ʊ����
    quicksort(prices, 0, pricesSize-1);
    if(prices[pricesSize-1] <= fee)
        return 0;
    while(i < pricesSize){
        buy = 0;
        sell = 0;
        profit = 0;
        while((i<pricesSize-1)&&(prices[i] > prices[i+1])) // �ͼ���
            i++;
        if(i == pricesSize-1) // ���һ���Ʊ�Ͳ�����
            return sprofit;
        buy = prices[i];
        j = i + 1;
        while((j<pricesSize-1)&&((prices[j+1]>prices[j]) || ((prices[j]-buy)<=fee))) // �߼�����ͬʱע�ⲻ�ܲ�׬�����
            j++;
        if(j == pricesSize-1){
            if((prices[j]-buy)<=fee) // ������һ���������������ʵ��ǰ�����Ҳû���ȥ��
                return sprofit;
        }
        sell = prices[j];
        profit = sell - buy - fee;
        sprofit = sprofit + profit;
        i = j + 1;
    }
    return sprofit;
}

int dp_maxProfit(int *prices, int pricesSize, int fee){
    int *profit1 = (int *)malloc(sizeof(int)*pricesSize); // ������ profit = sell-buy-fee
    int sprofit = 0; // �����������
    int i = 0; // ָʾ��Ʊ����
    int j = 0; // ��������������
    int k = 0; // ָʾ��Ʊ����
    int l = 0; // ������¼i
    int x = 0;
    int flag = 0;
    int *tempk = (int *)malloc(sizeof(int)*pricesSize);
    for(int a = 0; a < pricesSize; a++)
        tempi[a] = 0;
    for(int a = 0; a < pricesSize; a++)
        profit1[a] = 0;
    // ���Ƚ�һ��������Ԫ����ζ�ŵ�i�����Ʊ�ڵ�j��������������
    int **p = (int **)malloc(sizeof(int)*pricesSize);
    for(int m = 0; m < pricesSize; m++)
        p[m] = (int *)malloc(sizeof(int)*pricesSize);
    // ��ʼ��
    for(int a = 0; a < pricesSize; a++){
        for(int b = a; b < pricesSize; b++)
            p[a][b] = 0;
    }
    for(int a = 0; a < pricesSize; a++){
        for(int b = a; b < pricesSize; b++)
            p[a][b] = prices[b] - prices[a] - fee;
    }
    // �������ԭ����
    while(i<pricesSize){
        if(flag){
            j = tempj[l-1]+1;
            l--;
            profit = profit1[x-2];
            x--;
        }
        else if((flag==0)&&j<k);

        else if(i>k)
            j = 0;
        k = i;
        profit = 0;
        flag = 0;
        while((j<pricesSize)&&(k<pricesSize)){
            if(p[k][j] > 0){
                profit1[x+1] = profit1[x]+p[k][j];
                profit = profit1[x+1];
                x++;
                tempj[l] = j;
                l++;
                flag = 1;
                k = j+1; // ��k����������һ�����������ڵ�k+1��
                j = i+1; // ͬ����һ�����������ڵ�i+1��
                continue;
            }
            if((k==pricesSize-1)&&(p[i][k]<=0)){
                i++;
                break;
            }
            i++;
        }
        if(profit > sprofit)
            sprofit = profit;
        if(i>k)
            j++;
    }
    for(i = 0; i < pricesSize; i++)
        free(p[i]);
    free(p);
    return sprofit;
}
int greedy_maxProfit(int *prices, int pricesSize, int fee){
    int buy; // ����������Ļ����Ϲ����Ʊ�����µ����󣨼��Ϊ����
    int profit; // ������
    profit = 0; // ���죨��1�죩����Ϊ0
    buy = -prices[0]; // ���ڵ��죨��1�죩����Ϊ0�������Ʊ������-prices[0]
    // ��Ϊ���Թ����Σ�Ϊ��ʹ�����������ͬʱҲҪ���������
    // �����ǰѹ��򻨵�ǮҲ��Ϊ����������������
    // �ӵ�2�쿪ʼ����
    // ����Ҫ�󸺵����٣�����Ҫ��׬�����
    for(int i = 1; i < pricesSize; i++){
        // ѡ�������ڣ�ֻ�Ǽ��裬��һ������򣩣�Ҫ���������
        buy = max_of_two(buy, profit-prices[i]);
        // ѡ���������ڣ�ֻ�Ǽ��裬��һ�����������Ҫ��׬�����
        profit = max_of_two(profit, prices[i]-fee+buy);
    }
    return profit;
}
*/

