# 题目
As a freshman of grave robbery, you luckily sneaked into the tomb of a great ancient emperor, and soon found the treasure room of it. After a great surprise at the valuable jewels and gold plates, you quickly recognized that it is not so easy at all: there're many traps at the door of the treasure room which were not active when you entered, but once you take a treasure up from its pedestal, some traps will be activated so you cannot leave the room safely. All the pedestals are made so meticulous that only placing an object which has exactly the same shape and the same weight with the original treasure placed on it can reset the switch and thus deactivate the traps. Of course you don't have such things. Now you begin to regret that you haven't learned how to defuse traps from your teacher, the greatest grave robber all over the world. However, you're a man with good luck and always don't give up so easily. After several attempts, you found that if either taking up treasure A or treasure B alone will activate the same trap, taking up both of them will deactivate the trap! Then it is possible for you to take away some treasures with all the traps deactivated! Maybe the ancient mechanism is not very good, or it is just a mistake of the switch designer that didn't make the traps only deactivated when all switches are off. Anyway, you're really a lucky guy. After recording the relationships between the pedestals and the traps, and then assigning a value for each treasure, you want to know the maximum value you can take from the room safely.

Input

There're no more than 1000 test cases.

For each test case, the first line contains an integer N (1 <= N <= 24), the number of treasures in the room. Then N lines followed, each describes a treasure together with the relationship between its pedestal and the traps. Each of the N line begins with two positive integers V and M, the value of the treasure (V < 32768) and the number of traps that taking up this treasure will activate/deactivate respectively, and then M distinct trap indices followed. There will the at most 50 traps and the trap indices are all between 1 and 50, inclusive.

There's a blank line between consecutive test cases, processing to the end of the file.

Output

For each test case, print the maximum value you can get in a single line.

Sample Input
```
5
2 2 3 5
3 3 2 4 5
2 3 1 2 3
4 2 1 4
10 5 1 2 3 4 5
```
Sample Output
```
11
```
# 参考答案
```c++
#include<cstdio>
#include<cstring>
#include<map>
using namespace std;
typedef long long LL;
int v[25],k[25],trap[25][55],n;
map <LL,int> a;
int main()
{
	int i,j,l;
	int ans;
	map <LL,int>::iterator it;
	while(scanf("%d",&n)!=EOF)
	{
		ans=0;
		a.clear();
		for(i=0;i<n;i++)
		{
			scanf("%d",v+i);
			scanf("%d",k+i);
			for(j=0;j<k[i];j++) scanf("%d",&trap[i][j]);
		}
		for(i=0;i<(1<<(n/2));i++)
		{
			LL x=0;
			int tmpv=0;
			for(j=0;j<n/2;j++)
				if((1<<j)&i)
				{
					for(l=0;l<k[j];l++) x^=(LL)(1LL<<trap[j][l]);
					tmpv+=v[j];
				}
			it=a.find(x);
			if(it!=a.end())
			{
				int last=it->second;
				if(last<tmpv) a[x]=tmpv;
			}
			else
				a[x]=tmpv;
		}
		int before=n/2;
		for(i=0;i<(1<<(n-before));i++)
		{
			LL x=0;
			int tmpv=0;
			for(j=0;j<(n-before);j++)
			{
				if((1<<j)&i)
				{
					for(l=0;l<k[j+before];l++) x^=(LL)(1LL<<trap[j+before][l]);
					tmpv+=v[before+j];
				}
			}
			LL y=(0LL^x);
			it=a.find(y);
			if(it!=a.end())
			{
				int now=it->second;
				tmpv+=now;
				ans=max(ans,tmpv);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}



