# 题目
Farmer John's N cows (1
```
 1 5 3 2 5 1 3 4 4 2 5 1 2 3
```

Farmer John's acute mathematical mind notices all sorts of properties of number sequences like that above. For instance, he notices that the sequence 3 4 1 3 is a subsequence (not necessarily contiguous) of the sequence of breed IDs above. FJ is curious what is the length of the shortest possible sequence he can construct out of numbers in the range 1..K that is NOT a subsequence of the breed IDs of his cows. Help him solve this problem.

输入描述
* Line 1: Two integers, N and K

* Lines 2..N+1: Each line contains a single integer that is the breed ID of a cow. Line 2 describes cow 1; line 3 describes cow 2; and so on.

输出描述

* Line 1: The length of the shortest sequence that is not a subsequence of the input

输入例子
```
14 5
1
5
3
2
5
1
3
4
4
2
5
1
2
3
```
输出例子
```
3
```
Hint

All the single digit 'sequences' appear. Each of the 25 two digit sequences also appears. Of the three digit sequences, the sequence 2, 2, 4 does not appear.

# 参考答案
```c++
#include<stdio.h>
#include<string.h>
#define clr(x)memset(x,0,sizeof(x))
int v[10005];
int main()
{
    int n,k,p,i,res,num;
    while(scanf("%d%d",&n,&k)!=EOF)
    {
        res=num=0;
        clr(v);
        for(i=0;i<n;i++)
        {
            scanf("%d",&p);
            if(!v[p])
            {
                v[p]=1;
                num++;
                if(num==k)
                {
                    res++;
                    clr(v);
                    num=0;
                }
            }
        }
        printf("%d\n",res+1);
    }
    return 0;
}
