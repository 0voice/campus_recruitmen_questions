# 题目
Let x and y be two strings over some finite alphabet A. We would like to transform x into y allowing only operations given below:

Deletion: a letter in x is missing in y at a corresponding position.<br>
Insertion: a letter in y is missing in x at a corresponding position.<br>
Change: letters at corresponding positions are distinct<br>
Certainly, we would like to minimize the number of all possible operations.<br>

Illustration
```
<tt>A G T A A G T * A G G C

| | |       |   |   | |

A G T * C * T G A C G C</tt>
```
Deletion: * in the bottom line<br>
Insertion: * in the top line<br>
Change: when the letters at the top and bottom are distinct<br>
This tells us that to transform x = AGTCTGACGC into y = AGTAAGTAGGC we would be required to perform 5 operations (2 changes, 2 deletions and 1 insertion). If we want to minimize the number operations, we should do it like
```
<tt>A  G  T  A  A  G  T  A  G  G  C

|  |  |        |     |     |  |

A  G  T  C  T  G  *  A  C  G  C</tt>
```
and 4 moves would be required (3 changes and 1 deletion).

In this problem we would always consider strings x and y to be fixed, such that the number of letters in x is m and the number of letters in y is n where n ≥ m.

Assign 1 as the cost of an operation performed. Otherwise, assign 0 if there is no operation performed.

Write a program that would minimize the number of possible operations to transform any string x into a string y.

输入描述

The input consists of the strings x and y prefixed by their respective lengths, which are within 1000.

输出描述

An integer representing the minimum number of possible operations to transform any string x into a string y.

输入例子
```
10 AGTCTGACGC
11 AGTAAGTAGGC
```
输出例子
```
4
```
# 参考答案
```c++
#include<stdio.h>
#include<string.h>

char a[1010];
char b[1010];
int t[1010][1010],A,B;

int main()
{
    int i,j;
    while(scanf("%d%s%d%s",&A,a,&B,b)!=EOF)
    {
        memset(t,0,sizeof(t));
        for(i=0;i<=A;i++)
            t[i][0]=i;
        for(j=0;j<=B;j++)
            t[0][j]=j;

        for(i=1;i<=A;i++)
            for(j=1;j<=B;j++)
            {
                if(a[i-1]==b[j-1]) t[i][j]=t[i-1][j-1];
                else 
                {
                    t[i][j]=t[i-1][j]+1<t[i-1][j-1]+1?t[i-1][j]+1:t[i-1][j-1]+1;
                    t[i][j]=t[i][j]<t[i][j-1]+1?t[i][j]:t[i][j-1]+1;
                }
            }
            printf("%d\n",t[A][B]);
    }
    return 0;
}



