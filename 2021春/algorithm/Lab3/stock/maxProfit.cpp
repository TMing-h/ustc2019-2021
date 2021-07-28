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
    贪心算法：
    需要确定买卖日期，目的是为了使收益最大化
    为此要求
    ①购买股票后余下利润最大
    ②卖出股票时赚取利润最大
*/
/*
int greedy_maxProfit(int *prices, int pricesSize, int fee){
    // buy为购买股票后剩下的最大利润，profit为最大获利
    // 第一天的情况：
    // 购买股票后余下-prices[0]
    int buy = -prices[0];
    // 第一天无收益
    int profit = 0;
    /*
        从第二天开始，
        购买后余下利润最大的那天作为购买日期
        卖出获利最大的那天作为卖出日期
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
    int buy; // 购买花费
    int sell; // 卖出获利
    int profit; // 净利润 profit = sell-buy-fee
    int sprofit = 0;
    int i = 0; // 指示买票当天
    int j = 0; // 指示卖票当天
    quicksort(prices, 0, pricesSize-1);
    if(prices[pricesSize-1] <= fee)
        return 0;
    while(i < pricesSize){
        buy = 0;
        sell = 0;
        profit = 0;
        while((i<pricesSize-1)&&(prices[i] > prices[i+1])) // 低价买
            i++;
        if(i == pricesSize-1) // 最后一天的票就不买了
            return sprofit;
        buy = prices[i];
        j = i + 1;
        while((j<pricesSize-1)&&((prices[j+1]>prices[j]) || ((prices[j]-buy)<=fee))) // 高价卖，同时注意不能不赚或亏损
            j++;
        if(j == pricesSize-1){
            if((prices[j]-buy)<=fee) // 如果最后一天卖会亏，则不卖（实际前面买的也没算进去）
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
    int *profit1 = (int *)malloc(sizeof(int)*pricesSize); // 净利润 profit = sell-buy-fee
    int sprofit = 0; // 保存最大利润
    int i = 0; // 指示买票当天
    int j = 0; // 用来遍历子问题
    int k = 0; // 指示卖票当天
    int l = 0; // 用来记录i
    int x = 0;
    int flag = 0;
    int *tempk = (int *)malloc(sizeof(int)*pricesSize);
    for(int a = 0; a < pricesSize; a++)
        tempi[a] = 0;
    for(int a = 0; a < pricesSize; a++)
        profit1[a] = 0;
    // 首先建一个表，表中元素意味着第i天买的票在第j天卖，所得利润
    int **p = (int **)malloc(sizeof(int)*pricesSize);
    for(int m = 0; m < pricesSize; m++)
        p[m] = (int *)malloc(sizeof(int)*pricesSize);
    // 初始化
    for(int a = 0; a < pricesSize; a++){
        for(int b = a; b < pricesSize; b++)
            p[a][b] = 0;
    }
    for(int a = 0; a < pricesSize; a++){
        for(int b = a; b < pricesSize; b++)
            p[a][b] = prices[b] - prices[a] - fee;
    }
    // 下面求解原问题
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
                k = j+1; // 第k天卖，则下一次买至少是在第k+1天
                j = i+1; // 同理，下一次卖至少是在第i+1天
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
    int buy; // 在已有利润的基础上购买股票后余下的利润（简记为余润）
    int profit; // 总利润
    profit = 0; // 当天（第1天）利润为0
    buy = -prices[0]; // 由于当天（第1天）利润为0，购买股票后余下-prices[0]
    // 因为可以购买多次，为了使得总利润最大，同时也要让余润最大
    // 核心是把购买花的钱也作为（负）利润来看待
    // 从第2天开始考虑
    // 买入要求负的最少，卖出要求赚得最多
    for(int i = 1; i < pricesSize; i++){
        // 选择购买日期（只是假设，不一定真的买），要求余润最大
        buy = max_of_two(buy, profit-prices[i]);
        // 选择卖出日期（只是假设，不一定真的卖），要求赚得最多
        profit = max_of_two(profit, prices[i]-fee+buy);
    }
    return profit;
}
*/

