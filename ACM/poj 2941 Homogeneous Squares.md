# 题目
Assume you have a square of size n that is divided into n × n positions just as a checkerboard. Two positions (x <sub>1</sub>, y <sub>1</sub>) and (x <sub>2</sub>, y <sub>2</sub>), where 1 ≤ x <sub>1</sub>, y <sub>1</sub>, x <sub>2</sub>, y <sub>2</sub> ≤ n, are called “independent” if they occupy different rows and different columns, that is, x <sub>1</sub> ≠ x <sub>2</sub> and y <sub>1</sub> ≠ y <sub>2</sub>. More generally, n positions are called independent if they are pairwise independent. It follows that there are n! different ways to choose n independent positions.

Assume further that a number is written in each position of such an n × n square. This square is called “homogeneous” if the sum of the numbers written in n independent positions is the same, no matter how the positions are chosen. Write a program to determine if a given square is homogeneous!

输入描述
The input contains several test cases.

The first line of each test case contains an integer n (1 ≤ n ≤ 1000). Each of the next n lines contains n numbers, separated by exactly one space character. Each number is an integer from the interval [−1000000, 1000000].

The last test case is followed by a zero.

输出描述
For each test case output whether the specified square is homogeneous or not. Adhere to the format shown in the sample output.

输入例子
```
2
1 2
3 4
3
1 3 4
8 6 -2
-3 4 0
0
```
输出例子
```
homogeneous
not homogeneous
```
# 参考答案
```c++
#include <cstdlib>  
#include <cctype>  
#include <cstring>  
#include <cstdio>  
#include <cmath>  
#include <algorithm>  
#include <vector>  
#include <string>  
#include <iostream>  
#include <sstream>  
#include <map>  
#include <set>  
#include <queue>  
#include <stack>  
#include <fstream>  
#include <numeric>  
#include <iomanip>  
#include <bitset>  
#include <list>  
#include <stdexcept>  
#include <functional>  
#include <utility>  
#include <ctime>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MEM(a,b) memset((a),(b),sizeof(a))
const LL INF = 1000000007;
const int N = 1e3+10;
const double eps = 1e-12;
int a[N][N];
int main()
{

	int n;
	while (scanf("%d", &n) != EOF)
	{
		if (n == 0) break;
		int flag = 1;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				scanf("%d", &a[i][j]);
			}
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = i + 1; j < n; j++)
			{
				if (a[i][i] + a[j][j] != a[i][j] + a[j][i])
				{
					flag = 0;
					break;
				}
			}
			if (flag == 0) break;
		}
		if (flag) puts("homogeneous");
		else puts("not homogeneous");
	}
	return 0;
}
