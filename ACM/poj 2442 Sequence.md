# 题目
Given m sequences, each contains n non-negative integer. Now we may select one number from each sequence to form a sequence with m integers. It's clear that we may get n ^ m this kind of sequences. Then we can calculate the sum of numbers in each sequence, and get n ^ m values. What we need is the smallest n sums. Could you help us?

输入描述

The first line is an integer T, which shows the number of test cases, and then T test cases follow. The first line of each case contains two integers m

输出描述

For each test case, print a line with the smallest n sums in increasing order, which is separated by a space.

输入例子
```
1
2 3
1 2 3
2 2 3
```
输出例子
```
3 3 4
```

# 参考答案
```c++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int N=2002;
int main()
{
    int t,n,k,m,i,j;
    int a[N],b[N];
    priority_queue <int > q;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        for(i=0;i<n;i++)
        {
            if(i==0)
            {
                for(j=0;j<m;j++)
                    scanf("%d",&a[j]);
                sort(a,a+m);
            }
            else{
                for(j=0;j<m;j++)
                    scanf("%d",&b[j]);
                sort(b,b+m);

                for(j=0;j<m;j++)
                {
                    for(k=0;k<m;k++)
                    {
                        if(j==0)
                        {
                            q.push(b[j]+a[k]);
                        }else{
                            if(b[j]+a[k]<q.top())
                            {
                                q.pop();
                                q.push(b[j]+a[k]);
                            }else break;
                        }
                    }
                }
                for(k=0;k<m;k++)
                {
                    a[k]=q.top();
                    q.pop();
                }
                sort(a,a+m);
            }
        }
        printf("%d",a[0]);
        for(i=1;i<m;i++)
            printf(" %d",a[i]);
        printf("\n");
    }
    return 0;
}
