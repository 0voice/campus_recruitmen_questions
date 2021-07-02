# 题目
Trees are an important component of the natural landscape because of their prevention of erosion and the provision of a specific ather-sheltered ecosystem in and under their foliage. Trees have also been found to play an important role in producing oxygen and reducing carbon dioxide in the atmosphere, as well as moderating ground temperatures. They are also significant elements in landscaping and agriculture, both for their aesthetic appeal and their orchard crops (such as apples). Wood from trees is a common building material.

Trees also play an intimate role in many of the world's mythologies. Many scholars are interested in finding peculiar properties about trees, such as the center of a tree, tree counting, tree coloring. A(x) is one of such properties.

A(x) (accumulation degree of node x) is defined as follows:

Each edge of the tree has an positive capacity.<br>
The nodes with degree of one in the tree are named terminals.<br>
The flow of each edge can't exceed its capacity.<br>
A(x) is the maximal flow that node x can flow to other terminal nodes.<br>
Since it may be hard to understand the definition, an example is showed below:

![poj_3005desc_0](http://uploadfiles.nowcoder.com/probs/acm/poj_3005desc_0.jpg)

![3585.png](https://img10.360buyimg.com/ddimg/jfs/t1/183908/30/12398/20176/60deda23E74c114c1/748cf279942cfd4a.png)

The accumulation degree of a tree is the maximal accumulation degree among its nodes. Here your task is to find the accumulation degree of the given trees.

输入描述

The first line of the input is an integer T which indicates the number of test cases. The first line of each test case is a positive integer n. Each of the following n - 1 lines contains three integers x, y, z separated by spaces, representing there is an edge between node x and node y, and the capacity of the edge is z. Nodes are numbered from 1 to n.
All the elements are nonnegative integers no more than 200000. You may assume that the test data are all tree metrics.

输出描述

For each test case, output the result on a single line.

输入例子
```
1
5
1 2 11
1 4 13
3 4 5
4 5 10
```
输出例子
```
26
```
# 参考答案
```c++
#include<iostream>
#include<algorithm>
#include<utility>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<sstream>
#include<cmath>
#include<ctime>
#include<vector>
#include<string>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<numeric>
#include<limits>
using namespace std;
typedef long long ll;
const int inf=1000000000;
const double pi=acos(-1.0);
#define eps (1e-15)
#define clr clear
#define PB push_back
#define SZ(x) ((int)(x).size())
#define MP make_pair
#define X first
#define Y second
#define PII pair<int,int>
#define VI vector<int>
#define VD vector<double>
#define VS vector<string>dd
#define FORD(i,b,c) for(int (i)=(b);(i)>=c;(i)--)
#define REPD(i,c) FORD(i,c,0)
#define FOR(i,b,c) for(int i=(b);i<(c);i++)
#define REP(i,c) FOR(i,0,c)
#define PQ priority_queue
#define L(x) ((x)<<1)
#define R(x) ((x)<<1|1)
#ifdef DBG
#define see(x) (cerr<<"[Line : "<< __LINE__<<"] : "<<#x<<"="<<x<<endl)
#define se(x) cerr<<x<<" "
#else
#define see(x) //
#define se(x) //
#endif

#define maxn 500010
int n,m;
int first[maxn],next[maxn],E[maxn],M,C[maxn];
int down[maxn],flag[maxn],in[maxn];
void _insert(int a,int b,int c)
{
	in[a]++;
	M++;
	next[M]=first[a];
	first[a]=M;
	E[M]=b;
	C[M]=c;
}

void insert(int a,int b,int c)
{
	_insert(a,b,c);
	_insert(b,a,c);
}

void init()
{
	memset(first,-1,sizeof(first));
	M=0;
}

void dfs(int u,int f)
{
	int i,e,j;
	int v,res=0;
	for(e=first[u]; e!=-1; e=next[e])
	{
		v=E[e];
		if(!flag[v])
		{
			flag[v]=1;
			dfs(v,C[e]);
			if(in[v]==1)
			{
				down[u]+=C[e];
			}
			else
			{
				down[u]+=min(C[e],down[v]);
			}
			flag[v]=0;
		}
	}
}

int ans=0;
void dfs2(int u,int f)
{
	int i,e,j,v,res=0;

	for(e=first[u]; e!=-1; e=next[e])
	{
		v=E[e];
		if(!flag[v])
		{
			flag[v]=1;
			ans=max(ans,f+down[u]);
			int tp=down[u]+f-C[e];
			if(tp==0)
				tp=C[e];
			dfs2(v,min(tp,C[e]));
			flag[v]=0;
		}
	}
	if(in[u]==1)
	{
		ans=max(ans,f);
	}
}
int main()
{

    int i,j,k,t;
	scanf("%d", &t);
	while(t--)
	{
		memset(in,0,sizeof(in));
		memset(flag,0,sizeof(flag));
		init();
		int a,b,c;
		scanf("%d", &n);
		for(i=0; i<n-1; i++)
		{
			scanf("%d%d%d", &a,&b,&c);
			insert(a,b,c);
		}

		memset(down,0,sizeof(down));
		flag[1]=1;
		dfs(1,0);

		ans=0;
		dfs2(1,0);
		printf("%d\n",ans);
	}
}




