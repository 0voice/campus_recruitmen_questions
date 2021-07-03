# 题目
The army is going to have a military exercise. The General has divided his men into two groups, Blue and Red. Just before the exercise, the General found out that M pairs of people are close friends. In his opinion, if two people from different groups are close friends, the training may be affected by the emotional factors. So here is your task. There are N soldiers in the army, who are numbered from 0 to N-1, find out the minimum number of soldiers to be eliminate so that there are no two people from different groups are close friends. You should output the numbers of the people eliminated in ascending order. If there more than one solution, output the lexicographically smallest one.

输入描述
The first line of input is the number of test case.<br>
The first line of test case contains two integers N and M.<br>
The second line contains N integers.<br>
The i th integer denote which group the i th soldier is in, 0 stands for blue, and 1 for red.<br>
Then the M lines each contains two integers X and Y, denoted that X and Y are close friend.<br>
(1 ≤ N ≤ 200 , 0 ≤ M ≤ 20000).<br>
There is a blank line before each test case.<br>
输出描述<br>
For each test case output the answer on a single line, which contains the minimum number of the soldiers to be eliminated followed by the sequence of their numbers.<br>
输入例子
```
4

2 1
0 1
0 1

2 2
0 1
0 1
1 0

2 2
0 1
0 1
1 1

3 2
0 0 1
0 1
1 2
```
输出例子
```
1 0
1 0
1 0
1 1
```
# 参考答案
```c++
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iostream>
using namespace std;
struct eg
{
	int x,n;
}e[50005];
int head[205],n,m,v[205],met[205],vd[205];
int dfs(int u)
{
	for(int i=head[u];i>0;i=e[i].n)
	{
		if(!vd[e[i].x]&&v[e[i].x]==1)
		{
			vd[e[i].x]=1;
			if(met[e[i].x]==-1||dfs(met[e[i].x]))
			{
				met[e[i].x]=u;
				return 1;
			}
		}
	}
	return 0;
}
int match()
{
	int ans=0;
	for(int i=0;i<n;i++)
	{
		if(!v[i])
		{
			memset(vd,0,sizeof(vd));
			ans+=dfs(i);
		}
	}
	return ans;
}
void deal()
{
	int q[205],len=0;
	memset(met,-1,sizeof(met));
	int ans=match();
	for(int i=0;i<n;i++)
	{
			v[i]=v[i]^1;
			memset(met,-1,sizeof(met));
			int tem=match();
			if(tem<ans)
			{
				ans=tem;
				q[len++]=i;
			}
			else
			{
				v[i]=v[i]^1;
			}

	}
	printf("%d",len);
	for(int i=0;i<len;i++)
	{
		printf(" %d",q[i]);
	}
	printf("\n");
}
int main()
{
	int c,tem,x,y,pos=1;
	scanf("%d",&c);
	while(c--)
	{
		memset(head,-1,sizeof(head));
		scanf("%d%d",&n,&m);
		for(int i=0;i<n;i++)
		{
			scanf("%d",&v[i]);
		}
		for(int i=0;i<m;i++)
		{
			scanf("%d%d",&x,&y);
			if(v[x]!=v[y])
			{
				if(v[x]==0)
				{
					e[pos].x=y;
					e[pos].n=head[x];
					head[x]=pos++;
				}
				else
				{
					e[pos].x=x;
					e[pos].n=head[y];
					head[y]=pos++;
				}
			}
		}
		deal();
	}
	return 0;
}
