# 题目
The EKG sequence is a sequence of positive integers generated as follows: The first two numbers of the sequence are 1 and 2. Each successive entry is the smallest positive integer not already used that shares a factor with the preceding term. So, the third entry in the sequence is 4 (being the smallest even number not yet used). The next number is 6 and the next is 3. The first few numbers of this sequence are given below.
```
1, 2, 4, 6, 3, 9, 12, 8, 10, 5, 15, 18, 14, 7, 21, 24, 16, 20, 22, 11, 33, 27
```
The sequence gets its name from its rather erratic fluctuations. The sequence has a couple of interesting,but non-trivial, properties. One is that all positive integers will eventually appear in the sequence.Another is that all primes appear in increasing order. Your job here is to find the position in the sequence of a given integer.

输入描述<br>
Input consists of a number of test cases. Each case will be a line containing a single integer n, 1 1,000,000.<br>
输出描述<br>
Each test case should produce one line of output of the form:<br>
The number n appears in location p.<br>
where n is the number given and p is the position of n in the EKG sequence. You are guaranteed that p will be no larger than 1,000,000.<br>
输入例子<br>
```
12
21
2
33
100000
299977
0
```
输出例子
```
The number 12 appears in location 7.
The number 21 appears in location 15.
The number 2 appears in location 2.
The number 33 appears in location 21.
The number 100000 appears in location 97110.
The number 299977 appears in location 584871.
```

# 参考答案
```c++
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn=1000000+5;

inline void debug()
{
    printf("where is wrong?\n");
}

inline int max(int a,int b)
{
    return a>b?a:b;
}

inline int min(int a,int b)
{
    return a<b?a:b;
}

int res[maxn]={0};
int a[maxn];
int b[maxn]={0};

inline void make_table()
{
   int i,j,n,cur,k,an,p;
   res[1]=1;
   res[2]=2;

   for(i=0;i<maxn;i++)
    a[i]=i;
    a[2]=4;

   for(i=2;i<maxn;i++)
   {
      if(b[i]==0)
      {
        for(j=1;i*j<maxn;j++)
        {
            if(b[i*j]==0)
                b[i*j]=i;
        }
      }
   }

   cur=2;
   for(n=2;n<maxn;n++)
   {
     k=cur;
     cur=maxn;
     while(k!=1)
     {
         p=b[k];
         while(res[a[p]]!=0&&a[p]+p<maxn)//更新a[]
          a[p]+=p;
         cur=cur>a[p]?a[p]:cur;
         while(k%p==0)    //去除k的最小因子，继续比较
         k=k/p;
     }
     res[cur]=n+1;
   }
}

int main()
{
   int n;
   make_table();
   while(scanf("%d",&n)&&n)
   {
     printf("The number %d appears in location %d.\n",n,res[n]);
   }
   return 0;
}



