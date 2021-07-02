# 题目
This program will not be part of the KOKOD��H collection, but it may be more important than the games themselves. It will serve to the marketing staff to find suitable procedures for promoting and selling the collection. So try to do your best.

Extensive marketing case study tried to prove that the total income from selling a product is polynomial function of number of satisfied customers. Experiments showed that the real results are not exactly the same which you can obtain using the function. However, this method is widely used. The reason is probably nonexistence of better solution. Let's denote the number of satisfied customers <var>y</var>, than we can express profits (denoted <var>x</var>) as

<var>x = P(y) = a0 + a1.y + a2.y2 + ... + am.ym</var>

The number of satisfied customers depends on the price of a product. Again, there is hypothese that this dependence is polynomial. If we denote the price <var>z</var>, we can write

<var>y = Q(x) = b0 + b1.z + b2.z2 + ... + bn.zn</var>

Coeficients <var>ai</var> and <var>bi</var> strongly depend on the season of the year, the moon phase, the purchasing power of customers, inflation rate and hunderds of other parameters. Besides on the kind of product and its quality, of course. In the past there was lot of effort put into the reserarch of these parameters. For various combinations of input parameters, the coeficients are stated in Pyshwejc's marketing tables. It is not thus difficult to find out their values. But the degree of polynoms is usualy very high. It is very difficult to substitute one polynom into the other and to compute the dependency of the profit on the price. This dependency is usually crucial for us to set the right price.

Your goal is to write the program which can substitute the polynom <var>Q</var> into the polynom <var>P</var> and determine the restulting polynom <var>R</var> indicating dependency of the profit on the price:

<var>x = R(z) = c0 + c1.z + c2.z2 + ... + cp.zp</var>

Input Specification
The input consists of <var>Z</var> assignments. The number of them is given by the single positive integer <var>Z</var> appearing on the first line of input. Each assingement constist of three lines. On the first line there are two integers <var>m</var> and <var>n</var> (<var>0 <= n,m <= 100</var>) separated by space. These numbers give the degree of polynoms <var>Q</var> and <var>P</var>. On the second line there are <var>m+1</var> integers <var>a0</var> ... <var>am</var>. These numbers are coeficients of polynom <var>P</var>. On the third line there are <var>n+1</var> integers <var>b0</var> ... <var>bn</var>. Always <var>am <> 0</var> and <var>bn <> 0</var>. Coeficients <var>ai</var> and <var>bi</var> are separated by space and they are chosen in order to each resulting coeficient could fit into the standard type integer.

Output Specification
The program prints exactly one line for each assignement. On this line, there will be <var>p+1</var> numbers. These numbers are coeficients <var>c0</var> ... <var>cp</var> of resulting polynom. The coeficients are separated by space and the line does not consist any redundant spaces. The coeficient in the highest degree should not be zero.

Sample Input
```
3
0 0
7
-2
1 1
6 6
9 -6
3 3
-3 6 -5 1
0 3 -3 1
  ```
Output for the Sample Input
  ```
7
60 -36
-3 18 -63 123 -156 138 -86 36 -9 1
```
# 参考答案
```c++
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string.h>
#define N 10005

using namespace std;

void cheng(vector<int> &a,vector<int> &b)
{
	int i,j,k,c[N],m;
	k = a.size()+b.size()-1;
	m = b.size();
	for ( i = 0 ; i < k ; i++)
	{
		if( i >= m )	j = i-m+1;
		else	j = 0 ;
		for ( c[i] = 0 ; j <= i ; j++)
		{
			if( j < a.size() && (i-j) < b.size() )
				c[i] += a[j]*b[i-j];
		}
	}
	a.clear();
	for( i = 0 ; i < k ; i++)	a.push_back(c[i]);
}

int main()
{
	int i,j,n,m,num,x;
	int res[N];
	cin>>num;
	while (num--)
	{
		vector<int> a,b,c;
		cin>>m>>n;

		for ( i = 0 ; i <= m ; i++)
		{
			cin>>x;
			a.push_back(x);
		}
		for ( i = 0 ; i <= n ; i++)
		{
			cin>>x;
			b.push_back(x);
			c.push_back(x);		
		}

		memset(res,0,sizeof(res));
		for ( i = 1 , res[0] = a[0] ; i <= m ; i++)
		{
			for ( j = 0 ; j < c.size() ; j++)
				res[j] += c[j]*a[i];
			cheng(c,b);
		}		
		for ( i = 0 ; i <= n*m ; i++)
		{
			if( !(i == n*m && res[i] == 0 && i == 0 ))
			{
				if( i != 0 )
					cout<<" ";
				cout<<res[i];
			}
			else	cout<<0;
		}
		cout<<endl;
	}
	return 0;
}




