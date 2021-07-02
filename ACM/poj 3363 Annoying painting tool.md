# 题目
Maybe you wonder what an annoying painting tool is? First of all, the painting tool we speak of supports only black and white. Therefore, a picture consists of a rectangular area of pixels, which are either black or white. Second, there is only one operation how to change the colour of pixels:

Select a rectangular area of r rows and c columns of pixels, which is completely inside the picture. As a result of the operation, each pixel inside the selected rectangle changes its colour (from black to white, or from white to black).

Initially, all pixels are white. To create a picture, the operation described above can be applied several times. Can you paint a certain picture which you have in mind?

输入描述

The input contains several test cases. Each test case starts with one line containing four integers n, m, r and c. (1 ≤ r ≤ n ≤ 100, 1 ≤ c ≤ m ≤ 100), The following n lines each describe one row of pixels of the painting you want to create. The ith line consists of m characters describing the desired pixel values of the ith row in the finished painting ('0' indicates white, '1' indicates black).

The last test case is followed by a line containing four zeros.

输出描述

For each test case, print the minimum number of operations needed to create the painting, or -1 if it is impossible.

输入例子
```
3 3 1 1
010
101
010
4 3 2 1
011
110
011
110
3 4 2 2
0110
0111
0000
0 0 0 0
```
输出例子
```
4
6
-1
```
# 参考答案
```c++
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

#define maxn 105

int n, m, r, c;
int map[maxn][maxn], vis[maxn][maxn];

void change(int x, int y)
{
 for (int i = x; i < x + r; i++)
 for (int j = y; j < y + c; j++)
 vis[i][j] = 1 - vis[i][j];
}

bool ok()
{
 for (int i = 0; i < n; i++)
 for (int j = 0; j < m; j++)
 if (map[i][j] != vis[i][j])
 return false;
 return true;
}

int main()
{
 while (scanf("%d%d%d%d", &n, &m, &r, &c), n | m | r | c)
 {
 getchar();
 for (int i = 0; i < n; i++)
 {
 for (int j = 0; j < m; j++)
 {
 char ch = getchar();
 map[i][j] = ch - '0';
 }
 getchar();
 }
 memset(vis, 0, sizeof(vis));
 int ans = 0;
 for (int i = 0; i < n - r + 1; i++)
 for (int j = 0; j < m - c + 1; j++)
 if (map[i][j] != vis[i][j])
 {
 change(i, j);
 ans++;
 }
 if (ok())
 printf("%d\n", ans);
 else
 printf("-1\n");
 }
 return 0;
}



