# 题目
Given a set of sticks of various lengths, is it possible to join them end-to-end to form a square?

输入描述

The first line of input contains N, the number of test cases. Each test case begins with an int

输出描述

For each case, output a line containing "yes" if is is possible to form a square; otherwise output "no".

输入例子
```
3
4 1 1 1 1
5 10 20 30 40 50
8 1 7 2 6 4 4 3 5
```
输出例子
```
yes
no
yes
```
# 参考答案
```c++
#include<iostream>
#include<stdio.h>
#include<algorithm>
using namespace std;
int a[100],b[100],n,sum;
bool d;
void dog(int x,int y,int z)
{
    int i;
    if (x==0) {d=true;return;}

    if (z==0)
    {
        for(i=1;i<=n;i++)
          if (b[i]==0)
    {
     b[i]=1;
     dog(x-1,i+1,sum/4-a[i]);
     b[i]=0;
     return ;
    }
    }
 if (y>n) return ;
    for(i=y;i<=n;i++)
    if (b[i]==0)
    {
  if (b[i-1]==0&&a[i]==a[i-1]) continue;
        if(z>=a[i])
        {                       
            b[i]=1;
            dog(x-1,i+1,z-a[i]);
            b[i]=0;
            if (d) return ;
        }  
    }
}
bool cmp(int x,int y)
{
    if (x>y) return true;
    return false;
}

int main()
{
    int t,ii,i,max;
    scanf("%d",&t);
    for(ii=1;ii<=t;ii++)
    {
        scanf("%d",&n);
        sum=0;
        max=0;
        for(i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            sum+=a[i];
            if (a[i]>max) max=a[i];
        }
        if (sum%4!=0) {printf("no\n");continue;}
        if (max>sum/4){printf("no\n");continue;}
        sort(a+1,a+n+1,cmp);
        d=false;
        for(i=1;i<=n;i++)
          b[i]=0;
  b[0]=1;
  a[0]=-100000;
        b[1]=1;
        dog(n-1,2,sum/4-a[1]);
        if (d) printf("yes\n");
        else
           printf("no\n");
    }
    return 0;
}




