# 题目
The kingdom Eintagra is in great danger! Overwhelming enemy has surrounded the emperor's castle and once they enter, a massacre is just what is going to be.

Now what all people in the kingdom Eintagra can rely on, is a huge catapult that can throw heavy rocks to the crowd of enemy. The catapult is so huge that it is too hard to adjust the direction it targets. So the damage it can do to the enemy is decreasing for every throw because the enemy in the targeted area are going to move away. If on the first attack it can make a certain damage, then on the second it can do only half, and 1/3 the damage on the third attack, and this holds, by estimation, that the K-th attack does 1/K damage of the first attack can do. People are optimistic so if the damage is not an integer, they round it up to the nearest bigger integer.

Given the damage of the first attack of the catapult and the life of the catapult, people need to know how much total damage the catapult can do to the enemy.

![poj_4549desc_0](http://uploadfiles.nowcoder.com/probs/acm/poj_4549desc_0.jpg)

输入描述
There are multiple test cases. Each contains two positive integers D and N in a single line, where D is the damage of the first attack of the catapult, and N is its life measured by the number of attacks it can make. D and N are both positive integers and not more than 2000000000.

Input ends with two zeros and this line should not be processed.

输出描述

Output a single line with an integer reporting the total damage that the catapult can do to the enemy.

输入例子
```
1 1
2 3
0 0
```
输出例子
```
1
4
```
# 参考答案
```c++
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

int main()
{
	int d,n;
	while (scanf("%d%d",&d,&n)>0,d||n)
	{
		long long sum=0;
		int tmp=(int)ceil(d/(n*1.0));
		int tmp1=n-(int)ceil(d/(tmp*1.0))+1;
		if (tmp1>=1) sum+=tmp1*tmp;
		int last=(int)ceil(d/(tmp*1.0));

		while (true)
		{
			if (last-1<=0) break;
			tmp=(int)ceil(d/((last-1)*1.0));

			tmp1=(last-(int)ceil(d/(tmp*1.0)));
			if (tmp1>=1) sum+=tmp*tmp1;
			last=ceil(d/(tmp*1.0));
			if (tmp>=d) break;
		}
		printf("%lld\n",sum);
	}
}



