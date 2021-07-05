# 题目
Bob wants to hold a race to encourage people to do sports. He has got trouble in choosing the route. There are N houses and N - 1 roads in his village. Each road connects two houses, and all houses are connected together. To make the race more interesting, he requires that every participant must start from a different house and run AS FAR AS POSSIBLE without passing a road more than once. The distance difference between the one who runs the longest distance and the one who runs the shortest distance is called “race difference” by Bob. Bob does not want the “race difference”to be more than Q. The houses are numbered from 1 to N. Bob wants that the No. of all starting house must be consecutive. He is now asking you for help. He wants to know the maximum number of starting houses he can choose, by other words, the maximum number of people who can take part in his race.

输入描述
There are several test cases.<br>
The first line of each test case contains two integers N and M. N is the number of houses, M is the number of queries.<br>
The following N-1 lines, each contains three integers, x, y and z, indicating that there is a road of length z connecting house x and house y.<br>
The following M lines are the queries. Each line contains an integer Q, asking that at most how many people can take part in Bob’s race according to the above mentioned rules and under the condition that the“race difference”is no more than Q.

The input ends with N = 0 and M = 0.

(N<=50000 M<=500 1<=x,y<=N 0<=z<=5000 Q<=10000000)<br>

输出描述<br>
For each test case, you should output the answer in a line for each query.<br>
输入例子
```
5 5
1 2 3
2 3 4
4 5 3
3 4 2
1
2
3
4
5
0 0
```
输出例子
```
1
3
3
3
5
```
# 参考答案
```c++
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
#define maxn 50003
int f1[maxn], f2[maxn];
int g1[maxn], g2[maxn];
int n, m;

struct E
{
    int v, next, w;
}edge[maxn<<1];

int head[maxn], tot;

void init()
{
    tot = 0;
    memset(head, -1, sizeof(int)*(n+1));
}

void add(int s, int t, int w)
{
    edge[tot].v = t;
    edge[tot].w = w;
    edge[tot].next = head[s];
    head[s] = tot++;
}

int maxz(int a, int b)
{
    return a > b ? a : b;
}
int minz(int a, int b)
{
    return a < b ? a : b;
}
void dfs1(int u, int pre)
{
    int i;
    f1[u] = f2[u] = 0;
    for(i = head[u]; i != -1; i = edge[i].next)
    {
        int v = edge[i].v;
        if(v == pre) continue;
        int w = edge[i].w;
        dfs1(v, u);
        if(f2[u] < f1[v] + w)
        {
            f2[u] = f1[v] + w;
            g2[u] = v;
            if(f2[u] > f1[u])
            {
                swap(f2[u], f1[u]);
                swap(g2[u], g1[u]);
            }
        }
    }
}

void dfs2(int u, int pre)
{
    int i;
    for(i = head[u]; i != -1; i = edge[i].next)
    {
        int v = edge[i].v;
        if(v == pre) continue;
        int w = edge[i].w;
        if(g1[u] == v)
        {
            if(f2[v] < f2[u] + w)
            {
                f2[v] = f2[u] + w;
                g2[v] = u;
                if(f1[v] < f2[v])
                {
                    swap(f1[v], f2[v]);
                    swap(g1[v], g2[v]);
                }
            }
        }
        else
        {
            if(f2[v] < f1[u] + w)
            {
                f2[v] = f1[u] + w;
                g2[v] = u;
                if(f1[v] < f2[v])
                {
                    swap(f1[v], f2[v]);
                    swap(g1[v], g2[v]);
                }
            }
        }
        dfs2(v, u);
    }
}

struct DEQUE
{
    int pos, val;
}que1[maxn], que2[maxn];
int main()
{
    int i, j;
    int x, y, z;
    int Q;
    while( ~scanf("%d%d", &n, &m))
    {
        if(!n && !m) break;
        init();
        for(i = 2; i <= n; i++)
        {
            scanf("%d%d%d", &x, &y, &z);
            add(x, y, z);
            add(y, x, z);
        }
        dfs1(1, -1);

        dfs2(1, -1);

        int h1, h2, t1, t2;
        int ans;
        while(m--)
        {
            scanf("%d", &Q);    
            h1 = h2 = 1; t1 = t2 = 0; ans = 1;
            for(i = 1; i <= n; i++)
            {
                while(h1 <= t1 && que1[t1].val >= f1[i]) 
                    t1--;
                que1[++t1].pos = i;
                que1[t1].val = f1[i];
                while(h1 <= t1 && abs(que1[t1].val - que1[h1].val) > Q)
                    h1++;

                while(h2 <= t2 && que2[t2].val <= f1[i]) 
                    t2--;
                que2[++t2].pos = i;
                que2[t2].val = f1[i];
                while(h2 <= t2 && abs(que2[t2].val - que2[h2].val) > Q)
                    h2++;
                ans = maxz(ans, i - maxz(que1[h1-1].pos, que2[h2-1].pos));
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}



