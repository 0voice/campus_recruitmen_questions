# 题目
A computer professor, who is fond of programming, has come to Tehran to pay a visit to our regional contest. After hearing about such an event, he has tried his best to be able to participate in the contest as a visitor. He would decide to hold such contests in his university, if he finds it fun enough.

As could be predicted, he has been lost in our large and crowded city, Tehran. He does not know where to go. Getting really tired, he is standing in a city intersection when he suddenly remembers the phone number of a friend in the organizing committee, and instantly calls him. The friend understands the situation and wants to route the professor through mobile phone calls. He plans to give the professor directions at each intersection; i.e. he tells the tired professor in which direction to move, and after reaching the next intersection, there is another phone call, to get the new direction, etc. This process continues, until the professor sees his friend at the destination intersection, waiting for him. Due to poor telecommunications installment, not all city intersections are accessible through mobile network.

The professor should get to the regional contest location as soon as possible. There are a number of antennas located in some of city intersections. A city intersection is accessible through the network if an antenna can see the point; i.e. there is an imaginary straight line connecting the intersection to any part of the antenna. The line can never cross a building, but touching a boundary does not block the mobile connection. The city is composed of R*C rectangular blocks. Each block is a building having 10 meters width and length.

You should write a program to find out the shortest possible mobile route; i.e. a route that lets the professor call his friend from each intersection, until reaching the destination. The program is given R, C and height of each building and each antenna, and the location of antennas.

输入描述

The only number of the first line, T, (1 The first line of a block, contains two integers R, C (1 ij The lower and rightmost intersection is (R,C), while the opposite intersection is (0, 0).

Followed is

输出描述

For each block of the input, write a single integer, which is the least distance the professor is to travel before getting to the contest, in meters. If there is no mobile route, and the professor’s friend is to choose another way for the routing, output -1 instead.

输入例子
```
1
3 2
0 10
20 15
5 4
3 0
1 2
1
0 0 6
```
输出例子
```
40
```
# 参考答案
```c++
# include <cstdio>
using namespace std;
# include <algorithm>
# include <cmath>
# include <queue>
# include <cstring>
# include <utility>
# include <functional>
# define N 55
# define eps 1e-8
# define equ(a,b) (fabs((a)-(b))<eps)
# define gt(a,b) (!equ(a,b)&&(a)>(b))
int h[N][N],len[N][N];
bool used[N][N];
int n,m,num,sr,sc,er,ec;
struct node
{
	int r,c,h;
	bool operator<(const node &pos) const
	{
		return h>pos.h;
	}
}sta[105];
int bfs()
{
	used[er][ec]=true;
	if(!used[sr][sc]||!used[er][ec]) return -1;
	queue<pair<int,int> > q;
	memset(len,-1,sizeof(len));
	len[sr][sc]=0;
	q.push(make_pair<int,int>(sr,sc));
	while(!q.empty())
	{
		pair<int,int> top=q.front();
		q.pop();
		if(top.first-1>=0&&used[top.first-1][top.second]&&len[top.first-1][top.second]==-1)
		{
			len[top.first-1][top.second]=len[top.first][top.second]+1;
			q.push(make_pair<int,int>(top.first-1,top.second));
		}
		if(top.first+1<=n&&used[top.first+1][top.second]&&len[top.first+1][top.second]==-1)
		{
			len[top.first+1][top.second]=len[top.first][top.second]+1;
			q.push(make_pair<int,int>(top.first+1,top.second));
		}
		if(top.second-1>=0&&used[top.first][top.second-1]&&len[top.first][top.second-1]==-1)
		{
			len[top.first][top.second-1]=len[top.first][top.second]+1;
			q.push(make_pair<int,int>(top.first,top.second-1));
		}
		if(top.second+1<=m&&used[top.first][top.second+1]&&len[top.first][top.second+1]==-1)
		{
			len[top.first][top.second+1]=len[top.first][top.second]+1;
			q.push(make_pair<int,int>(top.first,top.second+1));
		}
	}
	return len[er][ec]==-1?-1:len[er][ec]*10;
}
bool detect(int r,int c,int pos)
{
	if(sta[pos].r==r||sta[pos].c==c) return true;
	double dr=10*(r-sta[pos].r),dc=10*(c-sta[pos].c),dh=-sta[pos].h;
	bool f1=r>sta[pos].r,f2=c>sta[pos].c;

	for(int i=f1?sta[pos].r+1:sta[pos].r-1;f1?i<=r:i>=r;f1?i++:i--)
	{
		double k=10*(i-sta[pos].r)/dr,nc=sta[pos].c*10+k*dc,nh=sta[pos].h+k*dh;
		int t1=f1?i-1:i,t2=f2?ceil(nc/10-eps)-1+eps:nc/10+eps;
		if(gt(h[t1][t2],nh)) return false;
	}
	for(int i=f2?sta[pos].c+1:sta[pos].c-1;f2?i<=c:i>=c;f2?i++:i--)
	{
		double k=10*(i-sta[pos].c)/dc,nr=sta[pos].r*10+k*dr,nh=sta[pos].h+k*dh;
		int t1=f1?ceil(nr/10-eps)-1+eps:nr/10+eps,t2=f2?i-1:i;
		if(gt(h[t1][t2],nh)) return false;
	}
	return true;
}
int main()
{
	int test;
	scanf("%d",&test);
	while(test--)
	{
		scanf("%d%d",&n,&m);
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				scanf("%d",&h[i][j]);
		scanf("%d%d%d%d%d",&sr,&sc,&er,&ec,&num);
		for(int i=0;i<num;i++)
			scanf("%d%d%d",&sta[i].r,&sta[i].c,&sta[i].h);
		sort(sta,sta+num);
		for(int i=0;i<=n;i++)
			for(int j=0;j<=m;j++)
			{
				used[i][j]=false;
				for(int k=0;k<num&&!used[i][j];k++)
				    if(detect(i,j,k)) used[i][j]=true;
			}

		printf("%d\n",bfs());
	}
	return 0;
}



