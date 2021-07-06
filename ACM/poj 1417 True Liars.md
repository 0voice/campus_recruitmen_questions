# 题目
After having drifted about in a small boat for a couple of days, Akira Crusoe Maeda was finally cast ashore on a foggy island. Though he was exhausted and despaired, he was still fortunate to remember a legend of the foggy island, which he had heard from patriarchs in his childhood. This must be the island in the legend. In the legend, two tribes have inhabited the island, one is divine and the other is devilish, once members of the divine tribe bless you, your future is bright and promising, and your soul will eventually go to Heaven, in contrast, once members of the devilish tribe curse you, your future is bleak and hopeless, and your soul will eventually fall down to Hell.

In order to prevent the worst-case scenario, Akira should distinguish the devilish from the divine. But how? They looked exactly alike and he could not distinguish one from the other solely by their appearances. He still had his last hope, however. The members of the divine tribe are truth-tellers, that is, they always tell the truth and those of the devilish tribe are liars, that is, they always tell a lie.

He asked some of them whether or not some are divine. They knew one another very much and always responded to him "faithfully" according to their individual natures (i.e., they always tell the truth or always a lie). He did not dare to ask any other forms of questions, since the legend says that a devilish member would curse a person forever when he did not like the question. He had another piece of useful informationf the legend tells the populations of both tribes. These numbers in the legend are trustworthy since everyone living on this island is immortal and none have ever been born at least these millennia.

You are a good computer programmer and so requested to help Akira by writing a program that classifies the inhabitants according to their answers to his inquiries.

输入描述

The input consists of multiple data sets, each in the following format :

n p1 p2
xl yl a1
x2 y2 a2
...
xi yi ai
...
xn yn an

The first line has three non-negative integers n, p1, and p2. n is the number of questions Akira asked. pl and p2 are the populations of the divine and devilish tribes, respectively, in the legend. Each of the following n lines has two integers xi, yi and one word ai. xi and yi are the identification numbers of inhabitants, each of which is between 1 and p1 + p2, inclusive. ai is either yes, if the inhabitant xi said that the inhabitant yi was a member of the divine tribe, or no, otherwise. Note that xi and yi can be the same number since "are you a member of the divine tribe?" is a valid question. Note also that two lines may have the same x's and y's since Akira was very upset and might have asked the same question to the same one more than once.

You may assume that n is less than 1000 and that p1 and p2 are less than 300. A line with three zeros, i.e., 0 0 0, represents the end of the input. You can assume that each data set is consistent and no contradictory answers are included.

输出描述

For each data set, if it includes sufficient information to classify all the inhabitants, print the identification numbers of all the divine ones in ascending order, one in a line. In addition, following the output numbers, print end in a line. Otherwise, i.e., if a given data set does not include sufficient information to identify all the divine members, print no in a line.

输入例子
```
2 1 1
1 2 no
2 1 no
3 2 1
1 1 yes
2 2 yes
3 3 yes
2 2 1
1 2 yes
2 3 no
5 4 3
1 2 yes
1 3 no
4 5 yes
5 6 yes
6 7 no
0 0 0
```
输出例子
```
no
no
1
2
end
3
4
5
6
end
```
# 参考答案
```c++
#include<iostream>
#include<cstdio>
#include<map>
#include<cstring>
#include<cmath>
#include<vector>
#include<algorithm>
#include<set>
#include<string>
#include<queue>
#define inf 1<<30
#define M 60005
#define N 605
#define maxn 300005
#define eps 1e-10
#define zero(a) fabs(a)<eps
#define Min(a,b) ((a)<(b)?(a):(b))
#define Max(a,b) ((a)>(b)?(a):(b))
#define pb(a) push_back(a)
#define mem(a,b) memset(a,b,sizeof(a))
#define LL long long
#define lson step<<1
#define rson step<<1|1
#define MOD 1000000009
#define sqr(a) ((a)*(a))
using namespace std;
int pre[N],r[N];
int p1,p2,p;
bool vis[N];
int dp[N][N/2];
int cnt;   //最后分为几个集合
int a[N][2];  //a[i][0],a[i][1]分别表示把第i个集合分成的两个部分
vector<int> b[N][2];
int find(int x)
{
    if(x!=pre[x])
    {
        int f=pre[x];
        pre[x]=find(pre[x]);
        r[x]=r[x]^r[f];
    }
    return pre[x];
}
void Init()
{
    for(int i=1; i<=p1+p2; i++) pre[i]=i,r[i]=0;
    mem(vis,false);
    cnt=1;
    mem(a,0);
    for(int i=0; i<N; i++)
    {
        b[i][0].clear();
        b[i][1].clear();
    }
}
int main()
{
    while(scanf("%d%d%d",&p,&p1,&p2)!=EOF&&p+p1+p2)
    {
        Init();
        while(p--)
        {
            int u,v;
            char str[10];
            scanf("%d%d%s",&u,&v,str);
            int k=(str[0]=='n');
            int ra=find(u),rb=find(v);
            if(ra!=rb)
            {
                pre[ra]=rb;
                r[ra]=r[u]^r[v]^k;
            }
        }
        for(int i=1; i<=p1+p2; i++)
        {
            if(!vis[i])
            {
                int f=find(i);
                for(int j=i; j<=p1+p2; j++)
                {
                    if(find(j)==f)
                    {
                        vis[j]=true;
                        b[cnt][r[j]].pb(j);
                        a[cnt][r[j]]++;
                    }
                }
                cnt++;
            }
        }
        mem(dp,0);
        dp[0][0]=1;
        for(int i=1; i<cnt; i++)
        {
            for(int j=p1; j>=0; j--)
            {
                if(j-a[i][0]>=0)
                    dp[i][j]+=dp[i-1][j-a[i][0]];
                if(j-a[i][1]>=0)
                    dp[i][j]+=dp[i-1][j-a[i][1]];
            }
        }
        if(dp[cnt-1][p1]!=1)
        {
            printf("no\n");
            continue;
        }
        else
        {
            vector<int>ans;
            ans.clear();
            for(int i=cnt-1; i>=1; i--)
            {
                if(p1-a[i][0]>=0&&p2-a[i][1]>=0&&dp[i-1][p1-a[i][0]]==1)
                {
                    for(int j=0; j<b[i][0].size(); j++)
                    {
                        ans.pb(b[i][0][j]);
                    }
                    p1-=a[i][0];
                    p2-=a[i][1];
                }
                else if(p1-a[i][1]>=0&&p2-a[i][0]>=0&&dp[i-1][p1-a[i][1]]==1)
                {
                    for(int j=0; j<b[i][1].size(); j++)
                    {
                        ans.pb(b[i][1][j]);
                    }
                    p1-=a[i][1];
                    p2-=a[i][0];
                }
            }
            sort(ans.begin(),ans.end());
            for(int i=0; i<ans.size(); i++) printf("%d\n",ans[i]);
            printf("end\n");
        }
    }
    return 0;
}
