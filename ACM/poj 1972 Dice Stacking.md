# 题目
Chun-Soo is playing a dice stacking game. Six faces of a die are squares of the same size; each face of a die has a number from 1 to 6. But, they are not standard dice because the sum of the numbers in the opposite faces may not always be 7.

The dice game is to stack several dice up in the order Die 1, Die 2, Die 3, from the base keeping the following rule: For each pair of consecutive dice, the number on the bottom of the top die must match the number on the top of the bottom die. In other words, the two faces that are together must have the same number. We are free to place the bottom die as we wish, so Die 1 can be set freely.

A long rectangular pillar which has 4 sides is created. We are trying to make one side have the maximum sum. (Note that after we rotate a die to fix the top face and bottom face, we can still rotate the die by 90, 180, or 270 degrees.) Write a program to find the maximum sum that one side can have.

输入描述

![poj_3430input_0](http://uploadfiles.nowcoder.com/probs/acm/poj_3430input_0.jpg)

The first line of the input contains a single integer t (1

输出描述

There should be one line per test case which contains the maximum sum of the numbers in one side.

输入例子
```
1
5
2 3 1 6 5 4
3 1 2 4 6 5
5 6 4 1 3 2
1 3 6 2 4 5
4 1 6 5 2 3
```
输出例子
```
29
```
Hint

To get the maximum sum for the above input, you should pile up the dice as follows:

![poj_3430outputs_0](http://uploadfiles.nowcoder.com/probs/acm/poj_3430outputs_0.jpg)

# 参考答案
```c++
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int getmax(int a,int b)
{
    for(int i=6;i>=4;i--)
        if(i!=a&&i!=b)
            return i;
}
int po[10005][7];
int main()
{
    int T;
    for(scanf("%d",&T);T;T--)
    {
        int n,ans=0;
        scanf("%d",&n);
        for(int i=0;i<n;i++)
        {
            int a,b,c,d,e,f;
            scanf("%d%d%d%d%d%d",&a,&b,&c,&d,&e,&f);
            po[i][a]=f;po[i][f]=a;
            po[i][b]=d;po[i][d]=b;
            po[i][c]=e;po[i][e]=c;
        }
        int sum,lx;
        for(int i=1;i<=6;i++)
        {
            sum=getmax(i,lx=po[0][i]);
            for(int j=1;j<n;j++)
            {
                sum+=getmax(lx,po[j][lx]);
                lx=po[j][lx];
            }
            ans=max(sum,ans);
        }
        printf("%d\n",ans);
    }
    return 0;
}




