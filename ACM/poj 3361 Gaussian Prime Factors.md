# 题目
Let a, b, c, d be integers. The complex number a+bj, where j 2 = -1, is a factor of c+dj, if there exist integers e and f such that

c + dj = (a + bj)(e + fj).

A complex number a + bj where a and b are integers is a Gaussian prime if the factors are 1, -1, -a - bj and a + bj only.

The following are Gaussian primes: 1 + j, 1 - j, 1 + 2j, 1 - 2j, 3 and 7.

The Gaussian prime factors of 5 are:
```
1 + 2j and 1 - 2j, or
2 + j and 2 - j, or
-1 - 2j and -1 + 2j, or
-2 - j and -2 + j.
```
Write a program that finds all the Gaussian prime factors of a positive integer.

输入描述

One line of input per case. The line represents a positive integer n.

输出描述

One line of output per test case. The line represents the Gaussian prime factors of n . If a + bj is a Gaussian prime factor of n , then a > 0, |b | ≥ a , if b ≠ 0. If b = 0, the output must be a .

输入例子
```
2
5
6
700
```
输出例子
```
Case #1: 1+j, 1-j 
Case #2: 1+2j, 1-2j 
Case #3: 1+j, 1-j, 3 
Case #4: 1+j, 1-j, 1+2j, 1-2j, 7
```
Hint

Output the Gaussian prime factors in ascending order of a. If there are more than one factors with the same a, output them in ascending order of b by absolute value. If two conjugate factors coexist, the one with a positive imaginary part precedes that with a negative imaginary part.

# 参考答案
```c++
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 1005
struct ele
{
	int a,b;
	bool operator < (const ele &c) const
	{
		if(a==c.a)
		{
			if(abs(b)==abs(c.b))
				return b>c.b;
			else
				return abs(b)<abs(c.b);
		}
		else
			return a<c.a;
	}
}e[MAXN];
int up;
void get(int p)
{
	if((p-3)%4==0) e[up].a=p,e[up++].b=0;
	else
	{
		for(int i=1;i*i<=p;i++)
		{
			int j=sqrt(1.0*(p-i*i));
			if(i*i+j*j==p)
			{
				e[up].a=i,e[up++].b=j;
				e[up].a=i,e[up++].b=-j;
				break;
			}
		}
	}
}
int main()
{
	int cas=1,n;
	while(scanf("%d",&n)!=EOF)
	{
		up=0;
		for(int i=2;i*i<=n;i++)
			if(n%i==0)
			{
				get(i);
				while(n%i==0) n/=i;
			}
		if(n>1) get(n);
		sort(e,e+up);
		printf("Case #%d:",cas++);
		for(int i=0;i<up;i++)
		{
			printf(" %d",e[i].a);
			if(e[i].b<0)
			{
				if(e[i].b==-1) printf("-j");
				else printf("%dj",e[i].b);
			}
			else if(e[i].b>0)
			{
				if(e[i].b==1) printf("+j");
				else printf("+%dj",e[i].b);
			}
			if(i<up-1) printf(",");
		}
		printf("\n");
	}
	return 0;
}
