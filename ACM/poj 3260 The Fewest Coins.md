# 题目
Farmer John has gone to town to buy some farm supplies. Being a very efficient man, he always pays for his goods in such a way that the smallest number of coins changes hands, i.e., the number of coins he uses to pay plus the number of coins he receives in change is minimized. Help him to determine what this minimum number is.

FJ wants to buy T (1 ≤ T ≤ 10,000) cents of supplies. The currency system has N (1 ≤ N ≤ 100) different coins, with values V <sub>1</sub>, V <sub>2</sub>, ..., V<sub>N</sub> (1 ≤ V<sub>i</sub> ≤ 120). Farmer John is carrying C <sub>1</sub> coins of value V <sub>1</sub>, C <sub>2</sub> coins of value V <sub>2</sub>, ...., and C<sub>N</sub> coins of value VN (0 ≤ C<sub>i</sub> ≤ 10,000). The shopkeeper has an unlimited supply of all the coins, and always makes change in the most efficient manner (although Farmer John must be sure to pay in a way that makes it possible to make the correct change).

输入描述<br>
Line 1: Two space-separated integers: N and T .<br>
Line 2: N space-separated integers, respectively V <sub>1</sub> , V <sub>2</sub> , ..., V<sub>N</sub> coins (V <sub>1</sub> , ...V<sub>N</sub> )<br>
Line 3: N space-separated integers, respectively C <sub>1</sub> , C <sub>2</sub> , ..., C<sub>N</sub>

输出描述<br>
Line 1: A line containing a single integer, the minimum number of coins involved in a payment and change-making. If it is impossible for Farmer John to pay and receive exact change, output -1.

输入例子
```
3 70
5 25 50
5 2 1
```
输出例子
```
3
```

Hint
Farmer John pays 75 cents using a 50 cents and a 25 cents coin, and receives a 5 cents coin in change, for a total of 3 coins used in the transaction.
# 参考答案
```c++
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int v[105],c[105],MAX,n,sum;
int dp[33333],inf = 100000000;

void ZeroOnePack(int cost,int cnt)
{
    int i;
    for(i = sum+MAX; i>=cost; i--)
        dp[i] = min(dp[i],dp[i-cost]+cnt);
}

void CompletePack(int cost,int cnt)
{
    int i;
    for(i = sum+MAX+cost; i>=0; i--)
        dp[i] = min(dp[i],dp[i-cost]+cnt);
}

int MultiplePack()
{
    int i,j,k;
    for(i = 1; i<=sum+MAX; i++)
        dp[i] = inf;
    dp[0] = 0;
    for(i = 1; i<=2*n; i++)
    {
        if(i<=n)
        {
            k = 1;
            while(k<c[i])
            {
                ZeroOnePack(k*v[i],k);
                c[i]-=k;
                k*=2;
            }
            ZeroOnePack(c[i]*v[i],c[i]);
        }
        else
            CompletePack(-v[i-n],1);
    }
    if(dp[sum]==inf)
        return -1;
    else
        return dp[sum];
}

int main()
{
    int i;
    while(~scanf("%d%d",&n,&sum))
    {
        MAX = 0;
        for(i=1; i<=n; i++)
        {
            scanf("%d",&v[i]);
            MAX = max(MAX,v[i]);
        }
        MAX*=MAX;
        for(i=1; i<=n; i++)
            scanf("%d",&c[i]);
        printf("%d\n",MultiplePack());
    }

    return 0;
}
