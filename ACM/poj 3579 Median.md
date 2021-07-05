# 题目
Given N numbers, X<sub>1</sub>, X<sub>2</sub>, ... , X<sub>N</sub> , let us calculate the difference of every pair of numbers: ∣X<sub>i</sub> - X<sub>j</sub> ∣ (1 ≤ i ＜ j ≤ N). We can get C(N,2) differences through this work, and now your task is to find the median of the differences as quickly as you can!

Note in this problem, the median is defined as the (m/2)-th  smallest number if m,the amount of the differences, is even. For example, you have to find the third smallest one in the case of m = 6.

输入描述
The input consists of several test cases.
In each test case, N will be given in the first line. Then N numbers are given, representing X<sub>1</sub>, X<sub>2</sub>, ... , X<sub>N</sub> , ( X<sub>i</sub> ≤ 1,000,000,000  3 ≤ N ≤ 1,00,000 )

输出描述

For each test case, output the median in a separate line.

输入例子
```
4
1 3 2 4
3
1 10 2
```
输出例子
```
1
8
```
# 参考答案
```c++
#include<cstdio>
#include<algorithm>
using namespace std;
#define maxn 100001
int n,a[maxn];
typedef long long LL;
LL limit;

int find(int x,int y)
{
    int left=1,right=y,mid;
    while (left<right)
    {
        mid=(left+right)>>1;
        if (a[mid]<x) left=mid+1;
        else right=mid;
    }
    return left;
}

bool check(int x)
{
    LL sum=0;    
    for (int i=1;i<=n;++i)
    {
        sum+=(LL)i-find(a[i]-x,i);
        if (sum>=limit) return true;
    }
    return false;
}
void solve()
{
    int left=0,right=0x7fffffff,mid;
    for (int i=1;i<=n;++i)
        scanf("%d",&a[i]);
    limit=(LL)n*(n-1)/2;
    limit=(limit+1)/2;
    sort(a+1,a+n+1);
    while (left<right)
    {
        mid=(left+right)>>1;
        if (!check(mid)) left=mid+1;
        else right=mid;
    }
    printf("%d\n",left);    
}
int main()
{
    while (scanf("%d",&n)>0)
        solve();
    return 0;
}


