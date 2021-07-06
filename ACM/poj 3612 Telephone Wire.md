# 题目
Farmer John's cows are getting restless about their poor telephone service; they want FJ to replace the old telephone wire with new, more efficient wire. The new wiring will utilize N (2 ≤ N ≤ 100,000) already-installed telephone poles, each with some heighti meters (1 ≤ height<sub>i</sub> ≤ 100). The new wire will connect the tops of each pair of adjacent poles and will incur a penalty cost C × the two poles' height difference for each section of wire where the poles are of different heights (1 ≤ C ≤ 100). The poles, of course, are in a certain sequence and can not be moved.

Farmer John figures that if he makes some poles taller he can reduce his penalties, though with some other additional cost. He can add an integer X number of meters to a pole at a cost of X <sup>2</sup>.

Help Farmer John determine the cheapest combination of growing pole heights and connecting wire so that the cows can get their new and improved service.

输入描述
* Line 1: Two space-separated integers: N and C
* Lines 2..N+1: Line i+1 contains a single integer: height<sub>i</sub>

输出描述
* Line 1: The minimum total amount of money that it will cost Farmer John to attach the new telephone wire.

输入例子
```
5 2
2
3
5
1
4
```
输出例子
```
15
```
# 参考答案
```c++
#include<cstdio>
#define min(a,b) ((a)<(b)?(a):(b))
#define inf 1<<30

int main()
{
	int n,m,i,j,t,ans,a,low[105],high[105],d[105];
	while(scanf("%d%d",&n,&m)==2)
	{
		scanf("%d",&a);
		for(i=1;i<=100;i++)
			d[i]=i<a?inf:(a-i)*(a-i);
		for(i=1;i<n;i++)
		{
			scanf("%d",&a);
			for(t=inf,j=100;j>0;j--)
				low[j]=t=min(t,d[j]+j*m);
			for(t=inf,j=1;j<=100;j++)
			{
				high[j]=t=min(t,d[j]-j*m);
				d[j]=inf;
			}
			for(j=a;j<=100;j++)
				d[j]=(j-a)*(j-a)+min(low[j]-j*m,high[j]+j*m);
		}
		for(ans=inf,i=1;i<=100;i++)
			ans=min(ans,d[i]);
		printf("%d\n",ans);
	}
}

