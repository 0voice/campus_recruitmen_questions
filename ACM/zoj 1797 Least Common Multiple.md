# 题目
The least common multiple (LCM) of a set of positive integers is the smallest positive integer which is divisible by all the numbers in the set. For example, the LCM of 5, 7 and 15 is 105.

Input

Input will consist of multiple problem instances. The first line of the input will contain a single integer indicating the number of problem instances. Each instance will consist of a single line of the form m n1 n2 n3 ... nm where m is the number of integers in the set and n1 ... nm are the integers. All integers will be positive and lie within the range of a 32-bit integer.


Output

For each problem instance, output a single line containing the corresponding LCM. All results will lie in the range of a 32-bit integer.


Sample Input
```
2
3 5 7 15
6 4 10296 936 1287 792 1
```

Sample Output
```
105
10296
```
# 参考答案
```c++
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <memory.h>
#define MAX 10001
using namespace std;
long long int gcd(long long int x,long long int y)
{
	return y == 0? x : gcd(y,x%y);
}
int main(void)
{
	int num[MAX];
	int ncases,n;
	scanf("%d",&ncases);
	while( ncases -- )
	{
		scanf("%d",&n);
		for(int i=0; i<n; i++)
			scanf("%d",&num[i]);
		if( n == 1 )
		{
			printf("%d\n",num[0]);
			continue;
		}
		int temp = gcd(num[0],num[1]);
		if(temp == 0 )
		{
			printf("%d\n",temp);
			continue;
		}
		temp = num[0]/temp*num[1];
		for(int i=2; i<n; i++)
		{
			int x = gcd(temp,num[i]);
			if( x == 0 )
			{
				temp = 0;
				break;
			}
			temp = temp/x*num[i];
		}
		printf("%d\n",temp);
	}
    return 0;
}





