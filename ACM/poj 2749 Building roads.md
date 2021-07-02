# 题目
Farmer John's farm has N barns, and there are some cows that live in each barn. The cows like to drop around, so John wants to build some roads to connect these barns. If he builds roads for every pair of different barns, then he must build N * (N - 1) / 2 roads, which is so costly that cheapskate John will never do that, though that's the best choice for the cows.

Clever John just had another good idea. He first builds two transferring point S1 and S2, and then builds a road connecting S1 and S2 and N roads connecting each barn with S1 or S2, namely every barn will connect with S1 or S2, but not both. So that every pair of barns will be connected by the roads. To make the cows don't spend too much time while dropping around, John wants to minimize the maximum of distances between every pair of barns.

That's not the whole story because there is another troublesome problem. The cows of some barns hate each other, and John can't connect their barns to the same transferring point. The cows of some barns are friends with each other, and John must connect their barns to the same transferring point. What a headache! Now John turns to you for help. Your task is to find a feasible optimal road-building scheme to make the maximum of distances between every pair of barns as short as possible, which means that you must decide which transferring point each barn should connect to.

We have known the coordinates of S1, S2 and the N barns, the pairs of barns in which the cows hate each other, and the pairs of barns in which the cows are friends with each other.

Note that John always builds roads vertically and horizontally, so the length of road between two places is their Manhattan distance. For example, saying two points with coordinates (x1, y1) and (x2, y2), the Manhattan distance between them is |x1 - x2| + |y1 - y2|.

输入描述

The first line of input consists of 3 integers N, A and B (2

Next line contains 4 integer sx1, sy1, sx2, sy2, which are the coordinates of two different transferring point S1 and S2 respectively.

Each of the following N line contains two integer x and y. They are coordinates of the barns from the first barn to the last one.

Each of the following A lines contains two different integers i and j(1

The same pair of barns never appears more than once.

Each of the following B lines contains two different integers i and j(1

You should note that all the coordinates are in the range [-1000000, 1000000].

输出描述

You just need output a line containing a single integer, which represents the maximum of the distances between every pair of barns, if John selects the optimal road-building scheme. Note if there is no feasible solution, just output -1.

输入例子
```
4 1 1
12750 28546 15361 32055
6706 3887
10754 8166
12668 19380
15788 16059
3 4
2 3
```
输出例子
```
53246
```
# 参考答案
```c++
#include<stack>
#include<cmath>
#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=2200;
stack <int> s;
vector <int> g[maxn];
int n,a,b,sx1,sy1,sx2,sy2;
int dist,dis1[maxn],dis2[maxn];
int xa[maxn],ya[maxn],xb[maxn],yb[maxn];
int ins[maxn],dfn[maxn],low[maxn],bel[maxn];
int calc(int x0,int y0,int xx,int yy){
	return abs(x0-xx)+abs(y0-yy);
}
void build(int lim){
	for(int i=n<<1|1;i>1;i--) g[i].clear(),dfn[i]=0;
	for(int i=1;i<=a;i++){
		g[xa[i]<<1].push_back(ya[i]<<1|1);
		g[ya[i]<<1].push_back(xa[i]<<1|1);
		g[xa[i]<<1|1].push_back(ya[i]<<1);
		g[ya[i]<<1|1].push_back(xa[i]<<1);
	}
	for(int i=1;i<=b;i++){
		g[xb[i]<<1].push_back(yb[i]<<1);
		g[yb[i]<<1].push_back(xb[i]<<1);
		g[xb[i]<<1|1].push_back(yb[i]<<1|1);
		g[yb[i]<<1|1].push_back(xb[i]<<1|1);
	}
	for(int i=1;i<n;i++)
		for(int j=i+1;j<=n;j++){
			if(dis1[i]+dis1[j]>lim){
				g[i<<1].push_back(j<<1|1);
				g[j<<1].push_back(i<<1|1);
			}
			if(dis2[i]+dis2[j]>lim){
				g[i<<1|1].push_back(j<<1);
				g[j<<1|1].push_back(i<<1);
			}
			if(dis1[i]+dis2[j]+dist>lim){
				g[i<<1].push_back(j<<1);
				g[j<<1|1].push_back(i<<1|1);
			}
			if(dis2[i]+dis1[j]+dist>lim){
				g[j<<1].push_back(i<<1);
				g[i<<1|1].push_back(j<<1|1);
			}
		}
}
int cnt,sum;
void tarjan(int x){
	int i;
	dfn[x]=low[x]=++cnt,ins[x]=1,s.push(x);
	for(i=g[x].size()-1;~i;i--)
		if(!dfn[g[x][i]])
			tarjan(g[x][i]),low[x]=min(low[x],low[g[x][i]]);
		else if(ins[g[x][i]])
			low[x]=min(low[x],low[g[x][i]]);
	if(dfn[x]!=low[x]) return;
	sum++;
	do{
		i=s.top(),s.pop();
		ins[i]=0,bel[i]=sum;
	}while(i!=x);
}
bool jud(){
	cnt=sum=0;
	for(int i=n<<1|1;i>1;i--) 
		if(!dfn[i]) tarjan(i);
	for(int i=1;i<=n;i++)
		if(bel[i<<1]==bel[i<<1|1])
			return 0;
	return 1;
}
int main(){
	scanf("%d%d%d%d%d%d%d",&n,&a,&b,&sx1,&sy1,&sx2,&sy2);
	dist=calc(sx1,sy1,sx2,sy2);
	for(int x,y,i=1;i<=n;i++){
		scanf("%d%d",&x,&y);
		dis1[i]=calc(sx1,sy1,x,y);
		dis2[i]=calc(sx2,sy2,x,y);
	}
	for(int i=1;i<=a;i++) 
		scanf("%d%d",&xa[i],&ya[i]);
	for(int i=1;i<=b;i++) 
		scanf("%d%d",&xb[i],&yb[i]);
	int l=1,r=4000000,mid,ans=-1;
	while(l<=r){
		mid=(l+r)>>1;
		build(mid);
		if(jud()) ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%d",ans);
}




