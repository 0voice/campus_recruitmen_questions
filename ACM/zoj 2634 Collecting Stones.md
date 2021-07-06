# 题目
Trudy is playing a phone game called Collecting Stones. In this game, a robert is placed on the upper-left corner of the board, which consists of 8x8 grids. On each grid, there are less than 2000001 stones. The robert can move up, down, right, up-right and down-right, but can not move into a grid that has already been passed before. All the stones on the grids which were passed by the robert are collected and Trudy is want to know if it is possible to collect exactly M number of stones when the robert arrives at the lower-right corner.

Input:

The first line of input contains a single integer T(T

Output:

For each testcase, output "Yes" if there exists a path for the robert to collect exactly M number of stones, output "No" otherwise.

Sample Input:
```
2
374
1 2 3 4 5 6 7 8
9 10 11 12 13 14 15 16
17 18 19 20 21 22 23 24
25 26 27 28 29 30 31 32
33 34 35 36 37 38 39 40
41 42 43 44 45 46 47 48
49 50 51 52 53 54 55 56
57 58 59 60 61 62 63 64
2032
1 2 3 4 5 6 7 8
9 10 11 12 13 14 15 16
17 18 19 20 21 22 23 24
25 26 27 28 29 30 31 32
33 34 35 36 37 38 39 40
41 42 43 44 45 46 47 48
49 50 51 52 53 54 55 56
57 58 59 60 61 62 63 64
```
Sample Output:
```
Yes
No
```
Note for the first sample: A possible path is 1, 10 18, 19, 20, 29, 38, 31, 40, 48, 56, 64.
# 参考答案
```c++
#include<iostream>
#include<cstdio>
#include<memory.h>

using namespace std;

#define Clear(f, nr) memset(f, nr, sizeof(f))
const int SIZE =9;
const int INF = 1 << 30;

int G[SIZE][SIZE];
bool vis[SIZE][SIZE];
bool flag;
int move[5][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}};
int sum, m;
int up[SIZE];

bool Judge(int x, int y)
{
 if(x >= 0 && x < 8 && y >= 0 && y < 8 && !vis[x][y])
 return 1;
 return 0;
}

void dfs(int x, int y)
{
 if(flag || sum > m) return ;
 if(up[y] < m - sum) return ; 
 if(x == 7 && y == 7) {
 if(sum == m) flag = 1;
 return ;
 }
 for(int i = 0; i < 5; i ++) {
 int row = x + move[i][0];
 int col = y + move[i][1];
 if(Judge(row, col)) {
 vis[row][col] = 1;
 sum += G[row][col];
 dfs(row, col);
 sum -= G[row][col];
 vis[row][col] = 0;
 }
 }
}

int main()
{
 int T;
 scanf("%d", &T);
 while(T --) {
 scanf("%d", &m);
 Clear(up, 0);
 for(int i = 0; i < 8; i ++)
 for(int j = 0; j < 8; j ++) {
 scanf("%d", &G[i][j]);
 up[j] += G[i][j];
 }
 for(int j = 6; j >= 0; j --)
 up[j] += up[j + 1];
 flag = 0;
 Clear(vis, 0);
 sum = G[0][0];
 vis[0][0] = 1;
 dfs(0, 0);
 puts(flag ? "Yes" : "No");
 }
}
