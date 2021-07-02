# 题目
You are appointed director of a famous concert hall, to save it from bankruptcy. The hall is very popular, and receives many requests to use its two fine rooms, but unfortunately the previous director was not very efficient, and it has been losing money for many years. The two rooms are of the same size and arrangement. Therefore, each applicant wishing to hold a concert asks for a room without specifying which. Each room can be used for only one concert per day.

In order to make more money, you have decided to abandon the previous fixed price policy, and rather let applicants specify the price they are ready to pay. Each application shall specify a period [i, j] and an asking price w, where i and j are respectively the first and last days of the period (1 <= i <= j <= 365), and w is a positive integer in yen, indicating the amount the applicant is willing to pay to use a room for the whole period.

You have received applications for the next year, and you should now choose the applications you will accept. Each application should be either accepted for its whole period or completely rejected. Each concert should use the same room during the whole applied period.

Considering the dire economic situation of the concert hall, artistic quality is to be ignored, and you should just try to maximize the total income for the whole year by accepting the most profitable applications.


Input

The input has multiple data sets, each starting with a line consisting of a single integer n, the number of applications in the data set. Then, it is followed by n lines, each of which represents one application with a period [i, j] and an asking price w yen in the following format.

i j w

A line containing a single zero indicates the end of the input.

The maximum number of applications in a data set is one thousand, and the maximum asking price is one million yen.


Output

For each data set, print a single line containing an integer, the maximum total income in yen for the data set.


Sample Input
```
4
1 2 10
2 3 10
3 3 10
1 3 10
6
1 20 1000
3 25 10000
5 15 5000
22 300 5500
10 295 9000
7 7 6000
8
32 251 2261
123 281 1339
211 235 5641
162 217 7273
22 139 7851
194 198 9190
119 274 878
122 173 8640
0
```

Sample Output
```
30
25500
38595
```
# 参考答案
```c++
#include <cstdio>
#include <stack>
#include <queue>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

const int NN=2100;
const int MM=1000000;
const int INF=0x3f3f3f3f;

struct interval{
    int s,t,cost;
    bool operator <(const interval a)const{
        return s<a.s;
    }
} a[NN];

int n,S,T,NV,en,head[NN];
struct Edge{
    int u,v,f,c,next;
}e[MM];
void add(int u,int v,int f,int c)
{
    e[en].u=u; e[en].v=v; e[en].c=c; e[en].f=f; e[en].next=head[u];
    head[u]=en++;
    e[en].u=v; e[en].v=u; e[en].c=-c; e[en].f=0; e[en].next=head[v];
    head[v]=en++;
}

void build_graph()
{
    en=0;
    S=0; T=2*n+1; NV=T+1;
    memset(head,-1,sizeof(head));

    for (int i=1; i<=n; i++) add(S,i,1,0);
    for (int i=1; i<=n; i++) add(i,i+n,1,a[i].cost);
    for (int i=1; i<=n; i++) add(i+n,T,1,0);

    for (int i=1; i<n; i++)
    {
        int j=i+1;
        while (j<=n && a[j].s<=a[i].t) j++;
        for (; j<=n; j++) add(i+n,j,1,0);
    }
}

int dis[NN],p[NN];
bool vis[NN];
bool spfa()
{
    for (int i=0; i<NV; i++) dis[i]=-INF;
    dis[S]=0;
    p[S]=-1;
    stack<int> q; 
    q.push(S);
    while (!q.empty())
    {
        int u=q.top();
        q.pop();
        vis[u]=false;
        for (int i=head[u]; i!=-1; i=e[i].next)
        {
            int v=e[i].v;
            if (e[i].f && dis[v]<dis[u]+e[i].c)
            {
                dis[v]=dis[u]+e[i].c;
                p[v]=i;
                if (!vis[v])
                {
                    vis[v]=true;
                    q.push(v);
                }
            }
        }
    }
}

int fee_flow()
{
    int u,v,ret=0;
    for (int i=1; i<=2; i++)
    {
        spfa();
        for (v=T; p[v]!=-1; v=u){
            u=e[p[v]].u;
            e[p[v]].f--;
            e[p[v]^1].f++;
        }
        ret+=dis[T];
    }
    return ret;
}

int main()
{
    while (scanf("%d",&n),n)
    {
        for (int i=1; i<=n; i++) scanf("%d%d%d",&a[i].s,&a[i].t,&a[i].cost);
        sort(a+1,a+n+1);
        if (n==1) { printf("%d\n",a[1].cost); continue; }
        if (n==2) { printf("%d\n",a[1].cost+a[2].cost); continue; }

        build_graph();
        printf("%d\n",fee_flow());
    }
    return 0;
}



