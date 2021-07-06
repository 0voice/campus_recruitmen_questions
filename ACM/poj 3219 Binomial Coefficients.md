# 题目
The binomial coefficient C(n, k) has been extensively studied for its importance in combinatorics. Binomial coefficients can be recursively defined as follows:
```
C(n, 0) = C(n, n) = 1 for all n > 0;
C(n, k) = C(n − 1, k − 1) + C(n − 1, k) for all 0 < k < n.
```
Given n and k, you are to determine the parity of C(n, k).

输入描述<br>
The input contains multiple test cases. Each test case consists of a pair of integers n and k (0 ≤ k ≤ n < 2<sup>31</sup>, n > 0) on a separate line.

End of file (EOF) indicates the end of input.

输出描述<br>
For each test case, output one line containing either a “0” or a “1”, which is the remainder of C(n, k) divided by two.

输入例子
```
1 1
1 0
2 1
```
输出例子
```
1
1
0
```
# 参考答案
```c++
#include<stdio.h>
int main()
{
	int a, b;
	while (scanf("%d%d", &a, &b) == 2) {
		printf("%d\n", (a - b) & b ? 0 : 1);
		continue;
		int c = a - b;
		int x = 0, y = 0, z = 0;
		while (a = a >> 1) {
			x += a;
		}
		while (b = b >> 1) {
			y += b;
		}
		while (c = c >> 1) {
			z += c;
		}
		if (x - y > z) printf("0\n");
		else printf("1\n");
	}
    return 0;
}
