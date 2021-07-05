# 题目
Well known Las-Vegas casino "Big Jo" has recently introduced the new playing machine, called Magic Multiplying Machine (MMM). MMM has N levers and one big red button. Each lever is marked with some integer number ranging from 1 to M, thus i-th lever is marked with number ai.

A player who wishes to play on MMM inserts a coin into a special slot. After that she chooses some levers and pulls them. After she has made her choice, she presses the big red button. MMM blinks all its lights, rings its bells, plays different tunes and after that declares whether player has won the game.

The algorithm for determining whether the player has won is the following. If the player has pulled some real subset S of {1, 2, . . .N} of levers, her score is the product of numbers that these levers are markedwith, taken modulo M (if the player has pulled no levers, her score is 1):
```
score =Πi∈Sai mod M
```
Player has won the game if her score is maximal possible for the given machine.

Given the description of some MMM determine which levers should be pulled to win the game.

输入描述

The first line of the input contains two integer numbers N an

输出描述

On the first line of the output file print one integer number -- the score that should be obtained to win the game. On the second line print in ascending order the numbers of levers that should be pulled to obtain this score (levers are numbered starting from one).

If there are several solutions, output any one.

输入例子
```
4 6
1 2 3 4
```
输出例子
```
4
1 4
```
# 参考答案
```c++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=10000+10;
const int maxm=1000+10;
int num[maxn],dp[maxm],pa[maxm];
int ans[maxn];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    memset(dp,0xff,sizeof(dp));
    memset(pa,0xff,sizeof(pa));
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&num[i]);
        num[i]%=m;
    }
    int tmp,tmp2;
    for(int i=1;i<=n;++i)
    {
        tmp=num[i];
        if(dp[tmp]==-1) {dp[tmp]=-2;pa[tmp]=i;}
        for(int j=0;j<m;++j)
        {
            if(dp[j]!=-1&&pa[j]!=i)
            {
                tmp2=(tmp*j)%m;
                if(dp[tmp2]==-1) {dp[tmp2]=j; pa[tmp2]=i;}
            }
        }
    }
    int maxv=0;
    for(int i=m-1;i>0;--i)
        if(dp[i]!=-1) {maxv=i;break;}
    if(maxv==0)
    {
        printf("1\n");
    }
    else
    {
        printf("%d\n",maxv);
        int p=maxv;
        int cnt=0;
        while(dp[p]!=-2)
        {
            ans[cnt++]=pa[p];
            p=dp[p];
        }
        ans[cnt++]=pa[p];
        sort(ans,ans+cnt);
        for(int i=0;i<cnt;++i)
            printf("%d ",ans[i]);
        printf("\n");
    }
    return 0;
}
