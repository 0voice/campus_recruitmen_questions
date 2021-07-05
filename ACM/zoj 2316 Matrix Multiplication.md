# 题目
Let us consider undirected graph G = <v e=""> which has N vertices and M edges. Incidence matrix of this graph is N * M matrix A = {a<sub>ij</sub>}, such that aij is 1 if i-th vertex is one of the ends of j-th edge and 0 in the other case. Your task is to find the sum of all elements of the matrix A<sup>T</sup>A.</v>


This problem contains multiple test cases!

The first line of a multiple input is an integer N, then a blank line followed by N input blocks. Each input block is in the format indicated in the problem description. There is a blank line between input blocks.

The output format consists of N output blocks. There is a blank line between output blocks.


Input

The first line of the input file contains two integer numbers - N and M (2
Output

Output the only number - the sum requested.


Sample Input
```
1

4 4
1 2
1 3
2 3
2 4
```
Sample Output
```
18
```
# 参考答案
```c++
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;

typedef long long ll;
int a[10005], n, m;

int main()
{
 int T;
 scanf("%d", &T);
 for(int kase=1; kase<=T; kase++) {
 memset(a, 0, sizeof(a));
 scanf("%d%d", &n, &m);
 for(int j=0; j<m; j++) {
 int x, y;
 scanf("%d%d", &x, &y);
 a[x] ++;
 a[y] ++;
 }

 ll ans = 2 * m;
 for(int i=1; i<=n; i++) {
 ans += (ll)a[i] * ((ll)a[i] - 1);
 }

 cout << ans << endl;
 if(kase != T) printf("\n");
 }

 return 0;
}



