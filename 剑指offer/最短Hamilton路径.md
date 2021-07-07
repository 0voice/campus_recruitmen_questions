# 题目
给定一张 n 个点的带权无向图，点从 0∼n−1 标号，求起点 0 到终点 n−1 的最短 Hamilton 路径。

Hamilton 路径的定义是从 0 到 n−1 不重不漏地经过每个点恰好一次。

输入格式<br>
第一行输入整数 n。

接下来 n 行每行 n 个整数，其中第 i 行第 j 个整数表示点 i 到 j 的距离（记为 a[i,j]）。

对于任意的 x,y,z，数据保证 a[x,x]=0，a[x,y]=a[y,x] 并且 a[x,y]+a[y,z]≥a[x,z]。

输出格式<br>
输出一个整数，表示最短 Hamilton 路径的长度。

数据范围<br>
1≤n≤20<br>
0≤a[i,j]≤107<br>

输入样例：
```
5
0 2 4 5 1
2 0 6 5 3
4 6 0 8 3
5 5 8 0 5
1 3 3 5 0
```
输出样例：
```
18
```
# 参考答案
```c++
#include <stdio.h>
#include <string.h>

const int N = 20;
const int M = 1 << N;

int n;
int w[N][N];
int f[M][N];
int log_2[M >> 1]; // 存 1 到 M / 2 中，所有 2 的整次幂的数以 2 为底的对数

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i ++ )
        for (int j = 0; j < n; j ++ )
            scanf("%d", &w[i][j]);

    for (int i = 0; i < 20; i ++ ) // 预处理 log_2
        log_2[1 << i] = i;

    memset(f, 0x3f, sizeof f);
    f[1][0] = 0;
    for (int state = 1; state < 1 << n; state ++ )
        if (state & 1)
            for (int t = state; t; t &= t - 1)     // 只枚举 state 所包含的点集
            {
                int j = log_2[t & -t];             // 将集合 t 中最小的点取出
                for (int u = state ^ t & -t; u; u &= u - 1) // 只枚举 state 中去掉点 j 的点集
                {
                    int k = log_2[u & -u];         // 将集合 u 中最小的点取出
                    if (f[state ^ t & -t][k] + w[k][j] < f[state][j])
                        f[state][j] = f[state ^ t & -t][k] + w[k][j];
                }
            }

    printf("%d\n", f[(1 << n) - 1][n - 1]);
    return 0;
}
