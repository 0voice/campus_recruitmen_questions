# 题目
Xiaoyao likes to play with pictures very much. When he got a picture, he will use rectangle selection tool to select an area ((x1, y1 ) to (x2, y2 ), inclusively) and perform these operations:

Invert: For any pixel with value v in selected area, change v to -v.<br>
Lighten: For any pixel with value v in selected area, increase v by 1.<br>
Darken: For any pixel with value v in selected area, decrease v by 1.<br>
Flip Horizontal: For any pixel at (x, y) in selected area, replace its value with pixel at (x1 + x2 - x, y).<br>
Flip Vertical: For any pixel at (x, y) in selected area, replace its value with pixel at (x, y1 + y2 - y).<br>
After several operations, Xiaoyao wonders what value a pixel at specified position is. Could you tell him?<br>

Input

There are multi cases (no more than 5). Please proceed to the end of input. Each case is like below:

The first line contains two integers W and H, indicating the width and height of the picture. W and H are both between 1 and 255, inclusively.

Following H lines, each line contains W integers, indicating the value of pixels. The first integer of the first line in these H lines is the value of pixel at (0, 0) and the last integer is the value of pixel at (W-1, H-1). All these values are between -105 and 105, inclusively.

Then, a line with one integer M(0 <= M <= 105).

Following M lines, each line contains 5 integers: x1 y1 x2 y2 op, indicating the selected area and the operation. (0 <= x1 <= x2 &lt W, 0 <= y1 <= y2 &lt H, 1 <= op <= 5). If op is 1, it means Invert operation. If op is 2, it means Lighten operation. The others follow by analogy. You should follow the order of the input to perform operations.

Finally, there is a line with two integers x and y. (0 <= x < W, 0 <= y < H) Your task is to output the value of pixel at (x, y) after performing above operations.

Output

For each case, output a single line containing one integer which is the value of pixel at (x, y) at last.

Sample Input
```
3 2
1 2 3
4 5 6
2
0 0 1 1 1
1 0 2 1 4
2 1
```
Sample Output
```
-5
```
# 参考答案
```c++
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#define MAXN 300
#define MAXM 101000
using namespace std;
const double eps = 1e-9;
int w, h, m;
long long ma[MAXN][MAXN];

struct que {
 int x1, x2, y1, y2, kind;
} all[MAXM];

int main() {
 while (scanf("%d %d", &w, &h) == 2) {
 for (int i = 0; i < h; i++)
 for (int j = 0; j < w; j++)
 scanf("%lld\n", ma[i] + j);
 int m;
 scanf("%d", &m);
 for (int i = 0; i < m; i++)
 scanf("%d %d %d %d %d", &all[i].x1, &all[i].y1, &all[i].x2, &all[i].y2, &all[i].kind);
 int x, y;
 long long ans = 0, hao = 1;
 scanf("%d %d", &x, &y);
 for (int i = m - 1; i >= 0; i--) {
 if (x >= all[i].x1 && x <= all[i].x2 && y >= all[i].y1 && y <= all[i].y2) {
 if (all[i].kind == 1) {
 hao *= -1;
 } else if (all[i].kind == 2) {
 ans += hao;
 } else if (all[i].kind == 3) {
 ans -= hao;
 } else if (all[i].kind == 4) {
 x = all[i].x1 + all[i].x2 - x;
 } else {
 y = all[i].y1 + all[i].y2 - y;
 }
 }
 }
 ans+=hao*ma[y][x];
 cout<<ans<<endl;
 }
}



