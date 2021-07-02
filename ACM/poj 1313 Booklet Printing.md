# 题目
When printing out a document, normally the first page is printed first, then the second, then the third, and so on until the end. However, when creating a fold-over booklet, the order of printing must be altered. A fold-over booklet has four pages per sheet, with two on the front and two on the back. When you stack all the sheets in order, then fold the booklet in half, the pages appear in the correct order as in a regular book. For example, a 4-page booklet would print on 1 sheet of paper: the front will contain page 4 then page 1, and the back will contain page 2 then page 3.

```
Front              Back

-------------      -------------

|     |     |      |     |     |

|  4  |  1  |      |  2  |  3  |

|     |     |      |     |     |

-------------      -------------
```
Your task is to write a program that takes as input the number of pages to be printed, then generates the printing order.

输入描述

The input contains one or more test cases, followed by a line containing the number 0 that indicates the end of the file. Each test case consists of a positive integer n on a line by itself, where n is the number of pages to be printed; n will not exceed 100.

输出描述

For each test case, output a report indicating which pages should be printed on each sheet, exactly as shown in the example. If the desired number of pages does not completely fill up a sheet, then print the word Blank in place of a number. If the front or back of a sheet is entirely blank, do not generate output for that side of the sheet. Output must be in ascending order by sheet, front first, then back.

输入例子
```
1
14
4
0
```

输出例子

```
Printing order for 1 pages:
Sheet 1, front: Blank, 1
Printing order for 14 pages:
Sheet 1, front: Blank, 1
Sheet 1, back : 2, Blank
Sheet 2, front: 14, 3
Sheet 2, back : 4, 13
Sheet 3, front: 12, 5
Sheet 3, back : 6, 11
Sheet 4, front: 10, 7
Sheet 4, back : 8, 9
Printing order for 4 pages:
Sheet 1, front: 4, 1
Sheet 1, back : 2, 3
```
# 参考答案
```c++
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

#define maxn 105

int f[maxn][2];
int n;

void work()
{
    int page_num = (n + 3) / 4;
    for (int i = 0; i < page_num * 2; i++)
        f[i][(i & 1) ^ 1] = i + 1;
    int j = page_num * 2 + 1;
    for (int i = page_num * 2 - 1; i >= 0; i--, j++)
        f[i][i & 1] = j;
}

void output()
{
    int page_num = (n + 3) / 4;
    for (int i = 0; i < page_num * 2; i++)
    {
        if (f[i][0] > n && f[i][1] > n)
            continue;
        printf("Sheet %d, ", i / 2 + 1);
        if (i & 1)
            printf("back :");
        else
            printf("front:");
        if (f[i][0] <= n)
            printf(" %d", f[i][0]);
        else
            printf(" Blank");
        if (f[i][1] <= n)
            printf(", %d", f[i][1]);
        else
            printf(", Blank");
        puts("");
    }
}

int main()
{
    while (scanf("%d", &n), n)
    {
        printf("Printing order for %d pages:\n", n);
        work();
        output();
    }
    return 0;
}
