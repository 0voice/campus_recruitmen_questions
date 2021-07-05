# 题目
This is a super simple problem. The description is simple, the solution is simple. If you believe so, just read it on. Or if you don't, just pretend that you can't see this one.

We say an element is inside a matrix if it has four neighboring elements in the matrix (Those at the corner have two and on the edge have three). An element inside a matrix is called "nice" when its value equals the sum of its four neighbors. A matrix is called "k-nice" if and only if k of the elements inside the matrix are "nice".

Now given the size of the matrix and the value of k, you are to output any one of the "k-nice" matrix of the given size. It is guaranteed that there is always a solution to every test case.

Input

The first line of the input contains an integer T (1 <= T <= 8500) followed by T test cases. Each case contains three integers n, m, k (2 &lt= n, m <= 15, 0 <= k &lt= (n - 2) * (m - 2)) indicating the matrix size n * m and it the "nice"-degree k.

Output

For each test case, output a matrix with n lines each containing m elements separated by a space (no extra space at the end of the line). The absolute value of the elements in the matrix should not be greater than 10000.

Sample Input
```
2
4 5 3
5 5 3
```
Sample Output
```
2 1 3 1 1
4 8 2 6 1
1 1 9 2 9
2 2 4 4 3
0 1 2 3 0
0 4 5 6 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
```
# 参考答案
```c++
#include<stdio.h>
#include<string.h>

int is[20][20];
int ans[20][20];

int main()
{
 int t,n,m,i,j,k;

 scanf("%d",&t);
 while(t--)
 {
	scanf("%d%d%d",&n,&m,&k);
	memset(is,0,sizeof(is));
	for(i=1;i<n;i++)
	{
	 if(!k)
		break;
	 for(j=1;j<m-1;j++)
	 {
		is[i][j]=1;
		k--;
		if(!k)
		 break;
	 }
	}
	memset(ans,0,sizeof(ans));
	for(i=1;i<n;i++)
	{
	 for(j=1;j<m;j++)
	 {
		if(i>1)
		 ans[i][j]=ans[i-1][j]-ans[i-1][j-1]-ans[i-1][j+1]-ans[i-2][j];
		else
		 ans[i][j]=0;
		if(!is[i-1][j])
		{
		 if(ans[i][j])
			ans[i][j]=0;
		 else
			ans[i][j]=1;
		}
	 }
	}
	for(i=0;i<n;i++)
	{
	 printf("%d",ans[i][0]);
	 for(j=1;j<m;j++)
		printf(" %d",ans[i][j]);
	 puts("");
	}
 }
}



