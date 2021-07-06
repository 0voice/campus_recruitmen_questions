# 题目
You are given a row of m stones each of which has one of k different colors. What is the minimum number of stones you must remove so that no two stones of one color are separated by a stone of a different color?

输入描述

The input test file will contain multiple test cases. Each input test case begins with a single line containing the integers m and k where 1 ≤ m ≤ 100 and 1 ≤ k ≤ 5. The next line contains m integers x <sub>1</sub>, …, x<sub>m</sub> each of which takes on values from the set {1, …, k}, representing the k different stone colors. The end-of-file is marked by a test case with m = k = 0 and should not be processed.

输出描述

For each input case, the program should the minimum number of stones removed to satisfy the condition given in the problem.

输入例子
```
10 3
2 1 2 2 1 1 3 1 3 3
0 0
```
输出例子
```
2
```
Hint

In the above example, an optimal solution is achieved by removing the 2nd stone and the 7th stone, leaving three “2” stones, three “1” stones, and two “3” stones. Other solutions may be possible.

# 参考答案
```c++
#include <iostream>
using namespace std;
const int MAXN = 101;
const int MAXV = 0x3F3F3F3F;
int dp[MAXN][1<<6][6];
int a[MAXN];
int main() {
    int n,m;
    while (scanf("%d%d",&n,&m) != EOF && (n || m)) {
        for (int i = 1;i <= n;i++) {
            scanf("%d",&a[i]);
            a[i]--;
        }
        memset(dp,63,sizeof(dp));
        for (int i = 0;i < m;i++) {
            dp[1][1 << i][i] = (a[1] != i);
        }
        for (int i = 2;i <= n;i++) {
            for (int j = 0;j < 1<<m;j++) {
                for (int k = 0;k < m;k++) {
                    if ((j & (1<<k)) == 0) continue;
                    //if (dp[i-1][j][k] != MAXV)
                        dp[i][j][k] = min(dp[i][j][k],dp[i-1][j][k] + (a[i] != k));
                    for (int l = 0;l < m;l++) {
                        if (l == k || (j & (1<<l)) == 0) continue;
                        //if (dp[i-1][j&~(1<<k)][l] != MAXV)
                            dp[i][j][k] = min(dp[i][j][k],dp[i-1][j&~(1<<k)][l] + (a[i] != k));
                    }
                }
            }
        }
        int ans = 1<<30;
        for (int j = 0;j < 1<<m;j++) {
            for (int k = 0;k < m;k++) {
                if (dp[n][j][k] < ans) {
                    ans = dp[n][j][k];
                }
            }
        }
        printf("%d\n",ans);
    }
}
