# 题目

The FORTH programming language does not support floating-point arithmetic at all. Its author, Chuck Moore, maintains that floating-point calculations are too slow and most of the time can be emulated by integers with proper scaling. For example, to calculate the area of the circle with the radius R he suggests to use formula like R * R * 355 / 113, which is in fact surprisingly accurate. The value of 355 / 113 ≈ 3.141593 is approximating the value of PI with the absolute error of only about 2*10<sup>-7</sup> . You are to find the best integer approximation of a given floating-point number A within a given integer limit L. That is, to find such two integers N an

输入描述<br>
The first line of input contains a floating-point number

输出描述<br>
Output file must contain two integers, N and D, separated by space.

输入例子
```
3.14159265358979
10000
```
输出例子
```
355 113
```
# 参考答案
```c++
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;

struct Elem
{
    int a, b;
}ans;

double n;
int lim;

int binarysearch(int x)
{
    int l = 1;
    int r = min(lim, x * 10);
    while (l < r)
    {
        int mid = (l + r) / 2;
        if (mid * 1.0 / x < n)
            l = mid + 1;
        else
            r = mid;
    }
    return l;
}

void make(int a, int b)
{
    if (abs(a * 1.0 / b - n) < abs(ans.a * 1.0 / ans.b - n))
    {
        ans.a = a;
        ans.b = b;
    }
}

int main()
{
    scanf("%lf%d", &n, &lim);
    ans.a = (int)(n + 0.5);
    ans.b = 1;
    if (ans.a == 0)
        ans.a = 1;
    if (ans.a > lim)
        ans.a = lim;
    for (int i = 2; i <= lim; i++)
    {
        int x = binarysearch(i);
        make(x, i);
        if (x > 1)
            make(x - 1, i);
    }
    printf("%d %d\n", ans.a, ans.b);
    return 0;
}
