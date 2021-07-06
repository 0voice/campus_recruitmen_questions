# 题目
Advanced Cargo Movement, Ltd. uses trucks of different types. Some trucks are used for vegetable delivery, other for furniture, or for bricks. The company has its own code describing each type of a truck. The code is simply a string of exactly seven lowercase letters (each letter on each position has a very special meaning but that is unimportant for this task). At the beginning of company's history, just a single truck type was used but later other types were derived from it, then from the new types another types were derived, and so on.

Today, ACM is rich enough to pay historians to study its history. One thing historians tried to find out is so called derivation plan -- i.e. how the truck types were derived. They defined the distance of truck types as the number of positions with different letters in truck type codes. They also assumed that each truck type was derived from exactly one other truck type (except for the first truck type which was not derived from any other type). The quality of a derivation plan was then defined as

<tt>1/Σ(t<sub>o</sub>,t<sub>d</sub>)d(t<sub>o</sub>,t<sub>d</sub>) </tt>

where the sum goes over all pairs of types in the derivation plan such that t<sub>o</sub> is the original type and t<sub>d</sub> the type derived from it and d(t<sub>o</sub> ,t<sub>d</sub> ) is the distance of the types.
Since historians failed, you are to write a program to help them. Given the codes of truck types, your program should find the highest possible quality of a derivation plan.

输入描述<br>
The input consists of several test cases. Each test case begins with a line containing the number of truck types

输出描述<br>
For each test case, your program should output the text "The highest possible quality is 1/Q.", where 1/Q is the quality of the best derivation plan.

输入例子
```
4
aaaaaaa
baaaaaa
abaaaaa
aabaaaa
0
```
输出例子
```
The highest possible quality is 1/3.
```
# 参考答案
```c++
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

#define maxn 2005
#define inf 0x3f3f3f3f

int n;
char code[maxn][10];
int cost[maxn][maxn];
int vis[maxn];
int lowc[maxn];

int cal(int a, int b)
{
    int ret = 0;
    for (int i = 0; i < 7; i++)
        if (code[a][i] != code[b][i])
            ret++;
    return ret;
}

int prim()
{
    int i, j, p;
    int minc, res = 0;
    memset(vis, 0, sizeof(vis));
    vis[0] = 1;
    for (i = 1; i < n; i++)
        lowc[i] = cost[0][i];
    for (i = 1; i < n; i++)
    {
        minc = inf;
        p = -1;
        for (j = 0; j < n; j++)
            if (0 == vis[j] && minc > lowc[j])
            {
                minc = lowc[j];
                p = j;
            }
        if (inf == minc) return -1;
        res += minc; vis[p] = 1;
        for (j = 0; j < n; j++)
            if (0 == vis[j] && lowc[j] > cost[p][j])
                lowc[j] = cost[p][j];
    }
    return res;
}

int main()
{
        while (scanf("%d", &n), n)
    {
        memset(cost, 0, sizeof(cost));
        getchar();
        for (int i = 0; i < n; i++)
            gets(code[i]);
        for (int i = 0; i < n - 1; i++)
            for (int j = i + 1; j < n; j++)
            {
                cost[i][j] = cal(i, j);
                cost[j][i] = cost[i][j];
            }
        printf("The highest possible quality is 1/%d.\n", prim());
    }
    return 0;
}
