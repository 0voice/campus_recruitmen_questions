# 题目
Write a program that, given three positive integers x, y and z (x, y, z < 232, x ≤ y), computes the bitwise exclusive disjunction (XOR) of the arithmetic progression x, x + z, x + 2z, …, x + kz, where k is the largest integer such that x + kz ≤ y.

输入描述

The input contains multiple test cases. Each test case consists of three integers x, y, z separated by single spaces on a separate line. There are neither leading or trailing blanks nor empty lines. The input ends once EOF is met.

输出描述

For each test case, output the value of  on a separate line. There should be neither leading or trailing spaces nor empty lines.

输入例子
```
2 173 11
```
输出例子
```
48
```
# 参考答案
```C++
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
long long x,y,z;
long long Calculate(long long a,long long b,long long c,long long n)
{
    if(n==0) return 0;
    return (b/c)*n+(a/c)*n*(n-1)/2+Calculate(c,(a*n+b)%c,a%c,(a%c*n+b%c)/c);
}
int main()
{
    int i;
    while(cin>>x>>y>>z)
    {
        long long ans=0;
        for(i=0;i<32;i++)
            ans|=(Calculate(z,x,1ll<<i,(y-x)/z+1)&1ll)<<i;
        cout<<ans<<endl;
    }
    return 0;
}




