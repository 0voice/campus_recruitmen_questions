# 题目
Assume that there are lots of two colors of black and white Go Game Pieces in a box, we take out n Go Game Pieces (0<br>
For example, when n=8, m=2, k=2, the situation is as following:

![poj_3130desc_0](http://uploadfiles.nowcoder.com/probs/acm/poj_3130desc_0.jpg)

```
Original    first repetition  second repetition
```
输入描述

On every line a group of data is given. In each group there are three natural number n, m, k, separated by commas. After all data are given there is -1 as the symbol of termination.

输出描述

Find the number of white pieces corresponding to the input data of each group. One line is for every output. Its fore part is a repetition of the input data and then it follows a colon and a space. The last part of it is the computed number of the white pieces.

输入例子
```
8,2,2
3,1,1234
-1
```
输出例子
```
8,2,2: 4
3,1,1234: 2
```
# 参考答案
```c++
#include <stdio.h>
#include <string.h>

int n,m,p;
int a[130],b[130];

int main()
{
    int i,j,k;
    while (scanf("%d", &n) != EOF && n != -1)
    {
          scanf(",%d,%d", &m, &p);
          for (i = 0;i < m;i++)
              a[i] = 0;
          for (;i < n;i++)
              a[i] = 1;
          for (k = 1;k <= p;k++)
          {
              if (k % 2)
              {
                    for (i = 0;i < n - 1;i++)
                    {
                        if (a[i] == a[i + 1])
                           b[i] = 1;
                        else
                            b[i] = 0;
                    }
                    if (a[n - 1] == a[0])
                       b[n - 1] = 1;
                    else
                        b[n - 1] = 0;
              }
              else
              {
                    for (i = 0;i < n - 1;i++)
                    {
                        if (b[i] == b[i + 1])
                           a[i] = 1;
                        else
                            a[i] = 0;
                    }
                    if (b[n - 1] == b[0])
                       a[n - 1] = 1;
                    else
                        a[n - 1] = 0;
              }
          }
          int ct=  0;
          if (p % 2)
          {
                for (i = 0;i < n;i++)
                {
                    if (b[i] == 0)
                       ct++;
                }
          }
          else
          {
                for (i = 0;i < n;i++)
                {
                    if (a[i] == 0)
                       ct++;
                }
          }
          printf("%d,%d,%d: %d\n", n, m, p, ct);
    }
    return 0;
}



