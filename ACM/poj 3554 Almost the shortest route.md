# 题目
N cities (2 ≤ N ≤ <nobr>10 000</nobr>) are connected by a network of M one-way roads (1 ≤ M < <nobr>100 000 000</nobr>). It is known that these roads do not cross outside the cities. The numeration of the cities and the roads starts from 1.There is at most one road from any city to another one. The length of each road does not exceed <nobr>10 000</nobr>.

The company for which you work sends you on a business trip from city 1 to city N on your personal car. The trip expenses will be compensated to you only if the distance you drive will differ from the shortest possible by no more than K (0 ≤ K ≤ <nobr>10 000</nobr>).

The task is to determine on which roads you can drive to have the right to the compensation. That means the list of all roads that appear on at least one route from city 1 to city N where the length of the route does not exceed the length of the shortest route by more than K.

输入描述

The input consists of M+1 lines. The first line contains the numbers N, M, and K. Each next line describes one road and contains the initial city number, the final city number and the length of the road. All numbers are integers and separated from each other by one or more spaces.

输出描述

The output consists of several lines. The first line contains the integer L – the number of roads you can use. The following L lines contain the numbers of the roads in ascending order.

输入例子
```
4 5 1
1 2 1
1 3 4
2 3 1
2 4 3
3 4 1
```
输出例子
```
4
1
3
4
5
```
# 参考答案
```c++
#pragma comment(linker, "/STACK:1024000000,1024000000")
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;
#define maxe 2001000
#define maxn 10010
#define INF 1<<29
struct node{
 int u,v,w,next;
}edge[maxe],nedge[maxe];
int head[maxn],add;
void adj(int u,int v,int w)
{
 edge[add].u=u; edge[add].v=v; edge[add].w=w; edge[add].next=head[u]; head[u]=add++;
}

int nhead[maxn],nadd;
void nadj(int u,int v,int w)
{
 nedge[nadd].u=u; nedge[nadd].v=v; nedge[nadd].w=w; nedge[nadd].next=nhead[u]; nhead[u]=nadd++;
}
int dis[maxn],vis[maxn],n,m,k;
int ndis[maxn];
queue<int>q;
void spfa(node edge[],int head[],int dis[],int st)
{
 int i,j,u,v;
 for(i=1;i<=n;i++)
 dis[i]=INF,vis[i]=0;
 dis[st]=0; q.push(st);
 while(!q.empty())
 {
 u=q.front(); q.pop();
 vis[u]=0;
 for(i=head[u];i!=-1;i=edge[i].next)
 {
 v=edge[i].v;
 if(dis[v]>dis[u]+edge[i].w)
 {
 dis[v]=dis[u]+edge[i].w;
 if(!vis[v])
 {
 vis[v]=1;
 q.push(v);
 }
 }
 }
 }
}
int vv[maxe];
void solve()
{
 int i,j,u,v,w; memset(head,-1,sizeof(head)); add=0;
 memset(nhead,-1,sizeof(nhead)); nadd=0;
 for(i=0;i<m;i++)
 {
 scanf("%d %d %d",&u,&v,&w);
 adj(u,v,w);
 nadj(v,u,w);
 }
 spfa(edge,head,dis,1);
 spfa(nedge,nhead,ndis,n);
 memset(vv,0,sizeof(vv)); int tot=0;
 for(i=0;i<m;i++)
 {
 if(ndis[edge[i].v]+dis[edge[i].u]+edge[i].w<=dis[n]+k)
 tot++,vv[i]=1;
 }
 printf("%d\n",tot);
 for(i=0;i<m;i++)
 if(vv[i])
 printf("%d\n",i+1);
}
int main()
{
 while(scanf("%d %d %d",&n,&m,&k)!=EOF)
 solve();
}



