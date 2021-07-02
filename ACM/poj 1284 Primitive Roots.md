# 题目
We say that integer x, 0 i mod p) | 1 Write a program which given any odd prime 3

输入描述

Each line of the input contains an odd prime numbers p. Input is terminated by the end-of-file seperator.

输出描述

For each p, print a single number that gives the number of primitive roots in a single line.

输入例子
```
23
31
79
```
输出例子
```
10
8
24
```
# 参考答案
```c++
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
int phi[66000];
int main()
{
    int i , j ;
    for ( i = 2 ; i <=  65536 ; i ++ )
        phi[i]=0;
    phi[1]=1;
    for ( i = 2 ; i <=  65536 ; i ++ )
        if ( !phi[i] )
        {
            for ( j = i ; j <=  65536 ; j += i )
            {
                if ( !phi[j] )
                    phi[j] = j ;
                phi[j] = phi[j] / i * (i - 1 ) ;
            }
        }

    int n ;
    while ( cin >> n )
        cout<<phi[n-1]<<endl;

    return 0;
}




