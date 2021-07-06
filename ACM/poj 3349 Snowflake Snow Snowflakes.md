# 题目
You may have heard that no two snowflakes are alike. Your task is to write a program to determine whether this is really true. Your program will read information about a collection of snowflakes, and search for a pair that may be identical. Each snowflake has six arms. For each snowflake, your program will be provided with a measurement of the length of each of the six arms. Any pair of snowflakes which have the same lengths of corresponding arms should be flagged by your program as possibly identical.

输入描述<br>
The first line of input will contain a single integer n, 0 < n ≤ 100000, the number of snowflakes to follow. This will be followed by n lines, each describing a snowflake. Each snowflake will be described by a line containing six integers (each integer is at least 0 and less than 10000000), the lengths of the arms of the snow ake. The lengths of the arms will be given in order around the snowflake (either clockwise or counterclockwise), but they may begin with any of the six arms. For example, the same snowflake could be described as 1 2 3 4 5 6 or 4 3 2 1 6 5.

输出描述<br>
If all of the snowflakes are distinct, your program should print the message:<br>
No two snowflakes are alike.<br>
If there is a pair of possibly identical snow akes, your program should print the message:<br>
Twin snowflakes found.

输入例子
```
2
1 2 3 4 5 6
4 3 2 1 6 5
```
输出例子
```
Twin snowflakes found.
```
# 参考答案
```c++
#include <iostream>

#include <cstdio>

#include <cstring>

#include <cstdlib>

using namespace std;

#define maxn 100000

struct Snow

{

    int arm[6];

    Snow *next;

};

Snow * snow[maxn];

bool same(Snow &a, Snow &b)

{

    for (int i = 0; i < 6; i++)

    {

        bool ok = true;

        for (int j = 0; j < 6; j++)

            if (a.arm[j] != b.arm[(j + i) % 6])

            {

                ok = false;

                break;

            }

        if (ok)

            return true;

    }

    for (int i = 0; i < 6; i++)

    {

        bool ok = true;

        for (int j = 0; j < 6; j++)

            if (a.arm[j] != b.arm[(i + 6 - j) % 6])

            {

                ok = false;

                break;

            }

        if (ok)

            return true;

    }

    return false;

}

bool ins(Snow &a, int index)

{

    if (snow[index] == 0)

    {

        a.next = snow[index];

        snow[index] = &a;

        return true;

    }

    Snow *p = snow[index];

    while (p != 0)

    {

        if (same(*p, a))

            return false;

        p = (*p).next;

    }

    a.next = snow[index];

    snow[index] = &a;

    return true;

}

int main()

{

    memset(snow, 0, sizeof(snow));

    int n;

    scanf("%d", &n);

    while (n--)

    {

        Snow *temp = new Snow;

        int sum = 0;

        for (int i = 0; i < 6; i++)

        {

            scanf("%d", &(*temp).arm[i]);

            sum += (*temp).arm[i];

        }

        if (!ins((*temp), sum % maxn))

        {

            printf("Twin snowflakes found.\n");

            return 0;

        }

    }

    printf("No two snowflakes are alike.\n");

    return 0;

}
