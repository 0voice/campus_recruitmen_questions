# 题目
Mirko works on a pig farm that consists of M locked pig-houses and Mirko can't unlock any pighouse because he doesn't have the keys. Customers come to the farm one after another. Each of them has keys to some pig-houses and wants to buy a certain number of pigs.

All data concerning customers planning to visit the farm on that particular day are available to Mirko early in the morning so that he can make a sales-plan in order to maximize the number of pigs sold.

More precisely, the procedure is as following: the customer arrives, opens all pig-houses to which he has the key, Mirko sells a certain number of pigs from all the unlocked pig-houses to him, and, if Mirko wants, he can redistribute the remaining pigs across the unlocked pig-houses.

An unlimited number of pigs can be placed in every pig-house.

Write a program that will find the maximum number of pigs that he can sell on that day.

输入描述
The first line of input contains two integers M and N, 1 The next line contains M integeres, for each pig-house initial number of pigs. The number of pigs in each pig-house is greater or equal to 0 and less or equal to 1000.<br>
The next N lines contains records about the customers in the following form ( record about the i-th customer is written in the (i+2)-th line):<br>
A K1 K2 ... KA B It means that this customer has key to the pig-houses marked with the numbers K1, K2, ..., KA (sorted nondecreasingly ) and that he wants to buy B pigs. Numbers A and B can be equal to 0.

输出描述
The first and only line of the output should contain the number of sold pigs.

输入例子
```
3 3
3 1 10
2 1 2 2
2 1 3 3
1 2 6
```
输出例子
```
7
```
# 参考答案
```c++
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

#define maxm 1005
#define maxn 105
#define N maxn
#define E 2 * maxn * maxm
#define inf 0x3f3f3f3f

struct edge
{
    int x, y, nxt, c;
} bf[E];

int ne, head[N], cur[N], ps[N], dep[N];
int n, m;
int pig[maxm];
int custom[maxm][maxn];
int num[maxm];
int buy[maxn];
int s, t;

void addedge(int x, int y, int c)
{
    bf[ne].x = x;
    bf[ne].y = y;
    bf[ne].c = c;
    bf[ne].nxt = head[x];
    head[x] = ne++;
    bf[ne].x = y;
    bf[ne].y = x;
    bf[ne].c =0;
    bf[ne].nxt = head[y];
    head[y] = ne++;
}

int flow(int n, int s, int t)
{
    int tr, res =0;
    int i, j, k, f, r, top;

    while (1)
    {
        memset(dep, -1, n *sizeof(int));
        for (f = dep[ps[0] = s] =0, r =1; f != r;)
            for (i = ps[f++], j = head[i]; j; j = bf[j].nxt)
            {
                if (bf[j].c &&-1== dep[k = bf[j].y])
                {
                    dep[k] = dep[i] +1;
                    ps[r++] = k;
                    if (k == t)
                    {
                        f = r;
                        break;
                    }
                }
            }
        if (-1== dep[t])
            break;

        memcpy(cur, head, n *sizeof(int));
        for (i = s, top =0;;)
        {
            if (i == t)
            {
                for (k =0, tr = inf; k < top; ++k)
                    if (bf[ps[k]].c < tr)
                        tr = bf[ps[f = k]].c;
                for (k =0; k < top; ++k)
                    bf[ps[k]].c -= tr, bf[ps[k] ^1].c += tr;
                res += tr;
                i = bf[ps[top = f]].x;
            }
            for (j = cur[i]; cur[i]; j = cur[i] = bf[cur[i]].nxt)
                if (bf[j].c && dep[i] +1== dep[bf[j].y])
                    break;
            if (cur[i])
            {
                ps[top++] = cur[i];
                i = bf[cur[i]].y;
            }
            else
            {
                if (0== top)
                    break;
                dep[i] =-1;
                i = bf[ps[--top]].x;
            }
        }
    }
    return res;
}

void input()
{
    memset(num, 0, sizeof(num));
    scanf("%d%d", &m, &n);
    for (int i =0; i < m; i++)
        scanf("%d", &pig[i]);
    for (int i =0; i < n; i++)
    {
        int a, b;
        scanf("%d", &a);
        for (int j =0; j < a; j++)
        {
            scanf("%d", &b);
            b--;
            custom[b][num[b]++] = i;
        }
        scanf("%d", &buy[i]);
    }
}

void work()
{
    ne =2;
    memset(head, 0, sizeof(head));
    s = n;
    t = n +1;
    for (int i =0; i < n; i++)
        addedge(i, t, buy[i]);
    for (int i =0; i < m; i++)
    {
        if (num[i] >0)
            addedge(s, custom[i][0], pig[i]);
        for (int j =1; j < num[i]; j++)
            addedge(custom[i][j -1], custom[i][j], inf);
    }
}

int main()
{
    input();
    work();
    printf("%d\n", flow(n +2, s, t));
    return 0;
}
