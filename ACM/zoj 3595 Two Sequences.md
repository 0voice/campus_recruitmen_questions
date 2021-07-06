# 题目
We have a real value x and two infinite sequences A and B. We know that B0 = 1. And for each i larger than zero, we know that:

![zoj_1164desc_3](http://uploadfiles.nowcoder.com/probs/acm/zoj_1164desc_3.jpg)

![image](https://user-images.githubusercontent.com/59190045/124537652-e4a79200-de4c-11eb-93fa-c5c3afdbefdb.png)

For every given A0 , define:

![image](https://user-images.githubusercontent.com/59190045/124537699-fc7f1600-de4c-11eb-85d2-335f3ca00f4f.png)


Now given A0 and list of xi which has n elements, calculate the geometric mean of all F(x), thus:

![image](https://user-images.githubusercontent.com/59190045/124537717-04d75100-de4d-11eb-9cf7-ffbaf58fa0a9.png)

Input
The input contains several test cases.

For each test case, the first line contains a real value A0 (0 < A<sub>0</sub> < 10000) and an integer n(0 < n < 10000), then the second line contains n real values xi (0 ≤ x<sub>i</sub> ≤ 30).

Output
For each test case, output a real number as the description required. The relative or absolute error of the answer should not exceed 1e-6.

Sample Input
```
55.55 1
0.0
12.34 1
1.0
```
Sample Output
```
55.55
55.304043
```
# 参考答案

```c++
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

int main()
{
 double x;
 int n;
 double a0;
 while (scanf("%lf %d", &a0, &n) == 2)
 {
 double ans = 0;
 for (int i = 0; i < n; i++)
 {
 scanf("%lf", &x);
 ans += x * x / 2.0 + x;
 }
 ans /= n;
 ans = a0 * exp(ans);
 printf("%lf\n", ans);
 }
 return 0;
}
