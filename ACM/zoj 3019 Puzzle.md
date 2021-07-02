# 题目
For sequences of integers a and b, if you can make the two sequences the same by deleting some elements in a and b, we call the remaining sequence "the common sub sequence". And we call the longest one the LCS.

Now you are given two sequences of integers a and b . You can arrange elements in a and b in any order. You are to calculate the max length of the LCS of each arrangement of a and b .

Input

Input will consist of multiple test cases. The first line of each case is two integers N(0 < N < 10000), M(0 < M < 10000) indicating the length of a and b . The second line is N 32-bit signed integers in a . The third line is M 32-bit signed integers in b .

Output

Each case one line. The max length of the LCS of each arrangement of a and b .

Sample Input
```
5 4
1 2 3 2 1
1 4 2 1
```
Sample Output
```
3
```
# 参考答案
```c++
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
#define N 100005
#define ll long long
#define pi acos(-1.0)

int a[N],b[N];

int main()
{

	int n,m,ans;
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		for(int i=1;i<=n;i++) scanf("%d",a+i);
		for(int i=1;i<=m;i++) scanf("%d",b+i);
		sort(a+1,a+n+1);
		sort(b+1,b+m+1);
		ans = 0;
		int ii = 1,jj = 1;
		while(ii<=n&&jj<=m)
		{
			if(a[ii]==b[jj])
			{
				ii++;
				jj++;
				ans++;
			}
			while(ii<=n&&a[ii]<b[jj]) ii++;
			while(jj<=m&&b[jj]<a[ii]) jj++;
		}
		printf("%d\n",ans);
	}
}
