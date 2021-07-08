# 题目
给定一个整数 M，对于任意一个整数集合 S，定义“校验值”如下:

从集合 S 中取出 M 对数(即 2×M 个数，不能重复使用集合中的数，如果 S 中的整数不够 M 对，则取到不能取为止)，使得“每对数的差的平方”之和最大，这个最大值就称为集合 S 的“校验值”。

现在给定一个长度为 N 的数列 A 以及一个整数 T。

我们要把 A 分成若干段，使得每一段的“校验值”都不超过 T。

求最少需要分成几段。

输入格式<br>
第一行输入整数 K，代表有 K 组测试数据。

对于每组测试数据，第一行包含三个整数 N,M,T 。

第二行包含 N 个整数，表示数列A<sub>1</sub>,A<sub>2</sub>…A<sub>N</sub>。

输出格式<br>
对于每组测试数据，输出其答案，每个答案占一行。

数据范围<br>
1≤K≤12,<br>
1≤N,M≤500000,<br>
0≤T≤10<sup>18</sup>,<br>
0≤A<sub>i</sub>≤2<sup>20</sup>
输入样例：
```
2
5 1 49
8 2 1 7 9
5 1 64
8 2 1 7 9
```
输出样例：
```
2
1
```
# 参考答案
```c++
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int N = 500005;

int n, m;
int ans;              // 存答案
ll T;                 // 题目中的 T
ll w[N], t[N];        // w 是输入的数组，t 是用于求校验值的数组

ll sq(ll x)           // 返回 x 的平方
{
    return x * x;
}

ll get(int l, int r)  // 求原数组区间 [l, r] 的校验值
{
    int k = 0;        // 要先把 w 的 [l, r] 这段复制到 t 中，用 k 记录 t 的长度。
    for (int i = l; i <= r; i ++ ) // 从 l 到 r 枚举一遍，将 w 数组复制到 t 数组中
        t[k ++ ] = w[i];
    sort(t, t + k);   // 将复制过来的数排序
    ll sum = 0;       // 存返回的校验值
    for (int i = 0; i < m && i < k; i ++ , k -- )
        sum += sq(t[i] - t[k - 1]); // 双指针，i 指向当前集合中剩余的最小数，k 指向当前集合中剩余的最大数
    return sum;
}

int main()
{
    int K;            // 测试数据组数
    cin >> K;
    while (K -- )     // 不写奇怪的 for 循环了qwq
    {
        cin >> n >> m >> T;
        for (int i = 0; i < n; i ++ ) cin >> w[i];
        ans = 0;      // 答案归零
        int start = 0;    // start 记录当前剩余的区间左端点
        while (start < n) // start < n 说明当前数组还有值，需要继续划分。结束时 start 应等于 n 
        {
            int l = start, r = n, mid; // 二分求出当前能划分的最长的区间
            while (l < r) // 二分板子
            {
                mid = l + r >> 1;
                if (get(start, mid) > T) r = mid;
                else    l = mid + 1;
            }
            start = r;    // 二分完后，r 即当前可划分的最长区间的下一个位置，将 start 制为 r。
            ans ++ ;      // 每次划分完一个区间，ans ++ 
        }
        printf("%d\n", ans);
    }
    return 0;
}
