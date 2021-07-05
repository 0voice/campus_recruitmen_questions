# 题目
Mirko has decided to rob mini-safe owned by his son so that he could take away some football stickers which are missing in his big sticker collection.

Lock on the safe consists of N equal discs, each of them being divided in 10,000,000 equal segments numbered from 1 to 10,000,000 clockwise. In the begining, segments on discs having the same number are placed one above (beneath) the other. Discs are layed one on the other such that the segments are overlaping and each disc is missing exactly one segment that is called hole.

In order to unlock the lock, all holes must be one above (beneath) the other.In one second, Mirko can turn one disc in one direction (clockwise or counterclockwise) for one segment.

Write a program which will find the minimal time that Mirko needs to open the safe.

输入描述

The first line of the input contains an integer N, 2 The next N lines contain data describing the initial positions of the holes on each disc.

The (i + 1)-th line contains an integer

输出描述

The first and only line of the output should contain the minimal time (in seconds).

Note: take care of the size of that number.

输入例子
```
4
9999999
7
16
9999995
```
输出例子
```
29
```
# 参考答案
```c++
#include <stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;
int P[300000];
int SEG=10000000;
int main()
{
    long n;
    long i;
    long j;
    double result,tempresult;
    cin>>n;
    for(i=0;i<n;i++)
    {
        cin>>P[i];

    }
    sort(P,P+n);
    for(i=0;i<n;i++)
    {
        P[i+n]=P[i]+SEG;
        P[i+2*n]=P[i+n]+SEG;
    }
    tempresult=0;
    int s;
    s=P[n]+SEG/2;
    for(i=n+1;P[i]<=s;++i)
    {
        tempresult+=(P[i]-P[n]); 
    }
    int ln=i;
    j=2*n-i;
    for(i=0;i<j;++i)
    {
        tempresult+=(P[n]-P[n-i-1]);
    }
    result=tempresult; 
    for(i=n+1;i<2*n;++i)
    {
        s=P[i]+SEG/2;
        for(j=ln;P[j]<=s;j++)
        {
            tempresult+=(P[j]-P[i]);
            tempresult-=(P[i-1]-P[j-n]);
        }
        tempresult+=((n-ln+2*i-j)*(P[i]-P[i-1]));
        ln=j;
        if(result>tempresult)
            result=tempresult;
    }
    printf("%.0f\n",result);
    return 0;
}



