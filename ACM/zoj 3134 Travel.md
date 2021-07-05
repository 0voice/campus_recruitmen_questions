# 题目
Kim works in a traveling agency in Korea. Recently, his foreign customer gave him an international call and asked him to make a travel plan in Korea. The customer wants to visit two famous roads along which beautiful flowers are in full blossom. The customer would like to fly to a city in the plan and rent a car, enjoy his travel, and return to the city where he started. He does not want to visit the same city or the same road twice. Also, he hates to travel along any toll roads. It does not matter how many cities are included in the plan. Can Kim make a travel plan satisfying the requirements?

For example, see the maps in Figure 1. In the figure a circle represents a city and the line between two cities represents the road between them. The two bold lines represent the famous roads that the customer wants to visit and the dotted line is a toll road.

![zoj_937desc_0](http://uploadfiles.nowcoder.com/probs/acm/zoj_937desc_0.jpg)

Figure 1

In case of Figure 1(a), Kim can make travel plans such as 1 -> 2 -> 4 -> 5 -> 3 -> 1 and 2 -> 3 -> 5 -> 4 -> 2. In case of Figure 1(b), Kim can not make any plan satisfying the requirements.

You are to write a program to help Kim. For a given map with two famous roads and some toll roads, your program should determine whether there can be a travel plan satisfying the requirements.

Input

Your program is to read from standard input. The input consists of T test cases. The number of test cases T is given in the first line of the input. Each testcase starts with a line containing two integers N and M, the number of cities and the number of roads in the map, respectively, where 5 <= N <= 1000 . In the next M lines, each line contains two positive integers that represent a road connecting two cities. In the next two lines, each line contains a road that the customer wants to visit. In the next line, the number of toll roads F is given, 0 <= F <= M. In the next F lines, each line contains toll roads. Assume the cities are labeled from 1 to N and there is at most one road between two cities. Also, assume the two roads that the customer wants to visit are not toll roads.

Output

Your program is to write to standard output. Print exactly one line for each test case. For each test case, print YES if there can be a travel plan satisfying the requirements. Otherwise, print NO.

Sample Input
```
3
6 8
2 1
1 3
4 5
2 4
5 3
2 3
3 6
5 6
3 5
2 4
1
6 5
6 8
2 1
1 3
4 5
2 4
5 3
2 3
3 6
5 6
2 3
3 5
1
4 2
5 4
1 2
2 3
3 4
4 5
1 2
4 5
2
2 3
3 4
```
Output for the Sample Input
```
YES
NO
NO
```
# 参考答案
```c++
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector <int> vi;

#define FOR(i, a, b) for (i = (a); i <= (b); i++)
#define FORD(i, a, b) for (i = (a); i >= (b); i--)
#define REP(i, a) for (i = 0; i < (a); i++)
#define REPD(i, a) for (i = (a) - 1; i >= 0; i--)

#define ALL(v) (v).begin(), (v).end()
#define SET(a, x) memset((a), (x), sizeof(a))
#define SZ(a) ((int)(a).size())
#define CL(a) ((a).clear())

#define SORT(x) sort(ALL(x))

#define PB push_back
#define NN 2004
int cap[NN][NN];
int fnet[NN][NN];
int q[NN], qf, qb, prev[NN];

int fordFulkerson( int n, int s, int t )
{
 memset( fnet, 0, sizeof( fnet ) );

 int flow = 0;

 while( true )
 {
 memset( prev, -1, sizeof( prev ) );
 qf = qb = 0;
 prev[q[qb++] = s] = -2;
 while( qb > qf && prev[t] == -1 )
 for( int u = q[qf++], v = 0; v < n; v++ )
 if( prev[v] == -1 && fnet[u][v] - fnet[v][u] < cap[u][v] )
 prev[q[qb++] = v] = u;
 if( prev[t] == -1 ) break;
 int bot = 0x7FFFFFFF;
 for( int v = t, u = prev[v]; u >= 0; v = u, u = prev[v] )
 bot =min(bot, cap[u][v] - fnet[u][v] + fnet[v][u]);
 for( int v = t, u = prev[v]; u >= 0; v = u, u = prev[v] )
 fnet[u][v] += bot;

 flow += bot;
 if(flow==2)break;
 }

 return flow;
}

void init()
{
 SET(cap,0);
}

int SRC,TNK;
int main()
{
 int u,v,i,t,N,M;
 scanf("%d",&t);
 while(t--)
 {
 scanf("%d%d",&N,&M);
 init();

 SRC=0;
 TNK=2*N+1;

 FOR(i,1,N)cap[i][N+i]=1;

 REP(i,M)
 {
 scanf("%d%d",&u,&v);
 cap[u+N][v]=cap[v+N][u]=1;
 }

 int u,v;

 scanf("%d%d",&u,&v);
 cap[SRC][v]=cap[SRC][u]=1;
 cap[u+N][v]=cap[v+N][u]=0;

 scanf("%d%d",&u,&v);
 cap[u+N][TNK]=cap[v+N][TNK]=1;
 cap[u+N][v]=cap[v+N][u]=0;

 int F;
 scanf("%d",&F);
 REP(i,F)
 {
 scanf("%d%d",&u,&v);
 cap[u+N][v]=cap[v+N][u]=0;
 }

 if(fordFulkerson(2*N+2,SRC,TNK)==2)printf("YES\n");
 else printf("NO\n");

 }
 return 0;
}



