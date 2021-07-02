# 题目
Lily runs a repairing company that services the Q blocks in the city. One day the company receives M repair tasks, the ith of which occurs in block pi , has a deadline ti on any repairman’s arrival, which is also its starting time, and takes a single repairman di time to finish. Repairmen work alone on all tasks and must finish one task before moving on to another. With a map of the city in hand, Lily want to know the minimum number of repairmen that have to be assign to this day’s tasks.

输入描述

The input contains multiple test cases. Each test case begins with a line containing Q and M (0 < Q ≤ 20, 0 < M ≤ 200). Then follow Q lines each with Q integers, which represent a Q × Q matrix Δ = {δ ij }, where δ ij means a bidirectional road connects the ith and the jth blocks and requires δ ij time to go from one end to another. If δ ij = −1, such a road does not exist. The matrix is symmetric and all its diagonal elements are zeroes. Right below the matrix are M lines describing the repairing tasks. The ith of these lines contains pi , ti and di . Two zeroes on a separate line come after the last test case.

输出描述

For each test case output one line containing the minimum number of repairmen that have to be assigned.

输入例子
```
1 2
0
1 1 10
1 5 10
0 0
```
输出例子
```
2
```
# 参考答案
```c++
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
const int INF = 0X1f1f1f1f;
#define clr(x) memset(x, 0, sizeof(x))

struct Task
{
    int p;
    int t;
    int d;
}task[210];

struct Edge
{
    int next;
    int to;
}edge[1000000];
int tot;
int head[210];

int link[210];
int vis[210];
int G[25][25], dis[25][25];
int sum, n;
int Q, M;

void floyd()
{
    for(int k = 0; k < Q; ++k)
    for(int i = 0; i < Q; ++i) {
        for(int j = 0; j < Q; ++j)
          G[i][j] = G[i][j] < G[i][k]+G[k][j]?G[i][j]:G[i][k]+G[k][j];
    }
  }

void add(int s, int u)
{
    edge[tot].to = u;
    edge[tot].next = head[s];
    head[s] = tot++;
}

int dfs(int x)
{
    for(int i = head[x]; i != 0; i = edge[i].next){
        int y = edge[i].to;
        if(!vis[y]){
            vis[y] = true;
            if(link[y] == 0 || dfs(link[y])){
                link[y] = x;
                return true;
            }
        }
    }
    return false;
}

void solve()
{
    clr(link);
    sum = 0;
    for(int i = 1; i <= n; ++i){
        clr(vis);
        if(dfs(i))
            sum++;
    }
}

int main()
{
    int i, j, k;
    while(scanf("%d %d", &Q, &M) != EOF)
    {
        if(Q == 0 || M == 0) break;
        clr(G), clr(dis), clr(head);
        n = M;
        tot = 1;

        for(i = 0; i < Q; ++i)
        for(j = 0; j < Q; ++j) {
            scanf("%d", &G[i][j]);
            if(G[i][j] == -1) G[i][j] = INF;
        }
        for(i = 1; i <= n; ++i)
            scanf("%d %d %d", &task[i].p, &task[i].t, &task[i].d);

        floyd();
        for(i = 1; i <= n; ++i)
        for(j = 1; j <= n; ++j)
        if(i != j) {
            if(task[i].d + task[i].t + G[task[i].p-1][task[j].p-1] <= task[j].t)
            add(i, j);
        }
        solve();

        printf("%d\n", n-sum);
    }
    return 0;
}
