# 题目
In the game of Jack Straws, a number of plastic or wooden "straws" are dumped on the table and players try to remove them one-by-one without disturbing the other straws. Here, we are only concerned with if various pairs of straws are connected by a path of touching straws. You will be given a list of the endpoints for some straws (as if they were dumped on a large piece of graph paper) and then will be asked if various pairs of straws are connected. Note that touching is connecting, but also two straws can be connected indirectly via other connected straws.

输入描述
Input consist multiple case,each case consists of multiple lines. The first line will be an integer n (1

When n=0,the input is terminated.

There will be no illegal input and there are no zero-length straws.

输出描述

You should generate a line of output for each line containing a pair a and b, except the final line where a = 0 = b. The line should say simply "CONNECTED", if straw a is connected to straw b, or "NOT CONNECTED", if straw a is not connected to straw b. For our purposes, a straw is considered connected to itself.

输入例子
```
7
1 6 3 3 
4 6 4 9 
4 5 6 7 
1 4 3 5 
3 5 5 5 
5 2 6 3 
5 4 7 2 
1 4 
1 6 
3 3 
6 7 
2 3 
1 3 
0 0

2
0 2 0 0
0 0 0 1
1 1
2 2
1 2
0 0

0
```
输出例子
```
CONNECTED 
NOT CONNECTED 
CONNECTED 
CONNECTED 
NOT CONNECTED 
CONNECTED
CONNECTED
CONNECTED
CONNECTED
```
# 参考答案
```c++
#include<iostream>
#include<string.h>
#include<algorithm>
#include<math.h>
#include<stdio.h>
using namespace std;
#define eps 1e-8
struct Point 
{
	double x,y;
};
struct Segment
{
	Point a,b;
};
int dblcmp(double d)
{
	return fabs(d)<=eps?0:d>0?1:-1;
}
double det(double x1,double y1,double x2,double y2)
{
	return x1*y2-x2*y1;
}
double cross(Point a,Point b,Point c)
{
	return det(b.x-a.x,b.y-a.y,c.x-a.x,c.y-a.y);
}
int xyCmp(double p,double mini,double maxi)
{
	return dblcmp(p-mini)*dblcmp(p-maxi);
}
int betweenCmp(Point a,Point b,Point c)
{
	if(fabs(b.x-c.x)>fabs(b.y-c.y))
	{
		return xyCmp(a.x,min(b.x,c.x),max(b.x,c.x));
	}
	else
	{
		return xyCmp(a.y,min(b.y,c.y),max(b.y,c.y));
	}
}
int segcross(Point a,Point b,Point c,Point d)
{
	double s1,s2,s3,s4;
	int d1,d2,d3,d4;
	d1=dblcmp(s1=cross(a,b,c));
	d2=dblcmp(s2=cross(a,b,d));
	d3=dblcmp(s3=cross(c,d,a));
	d4=dblcmp(s4=cross(c,d,b));
	if((d1^d2)==-2&&(d3^d4)==-2)
	{
		return 1;
	}
	if(d1==0&&betweenCmp(c,a,b)<=0||
	d2==0&&betweenCmp(d,a,b)<=0||
	d3==0&&betweenCmp(a,c,d)<=0||
	d4==0&&betweenCmp(b,c,d)<=0)
		return 1;
	return 0;
}
int pre[1005];
void UFSet(int n)
{
	for(int i=1;i<=n;i++)
	{
		pre[i]=i;
	}
}
int find(int x)
{
	if(x==pre[x])
		return x;
	else
		return pre[x]=find(pre[x]);
}
void Union(int x,int y)
{
	pre[find(x)]=find(y);
}
int main()
{
	int n,i,j;
	Segment seg[1005];
	while(scanf("%d",&n)==1&&n)
	{
		for(i=1;i<=n;i++)
		{
			scanf("%lf%lf%lf%lf",&seg[i].a.x,&seg[i].a.y,&seg[i].b.x,&seg[i].b.y);
		}
		UFSet(n);
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=n;j++)
			{
				if(j==i)continue;
				if(segcross(seg[i].a,seg[i].b,seg[j].a,seg[j].b)==1)
				{
					Union(j,i);
				}
			}
		}
		int a,b;
		while(scanf("%d%d",&a,&b)==2)
		{
			if(a==0&&b==0)break;
			if(find(a)==find(b))
			{
				printf("CONNECTED\n");
			}
			else
			{
				printf("NOT CONNECTED\n");
			}
		}
	}
	return 0;
}
