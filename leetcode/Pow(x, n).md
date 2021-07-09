# 题目
实现 pow(x, n) ，即计算 x 的 n 次幂函数（即，x<sup>n</sup>）。


示例 1：

    输入：x = 2.00000, n = 10
    输出：1024.00000
示例 2：

    输入：x = 2.10000, n = 3
    输出：9.26100
示例 3：

    输入：x = 2.00000, n = -2
    输出：0.25000
解释：2<sup>-2</sup> = 1/2<sup> 2</sup>  = 1/4 = 0.25
 

提示：

* -100.0 < x < 100.0
* -2<sup>31</sup> <= n <= 2<sup>31</sup>-1
* -10<sup>4</sup> <= x<sup>n</sup> <= 10<sup>4</sup>



# 参考答案
```c++
class Solution {
public:
    double quickMul(double x, long long N) {
        if (N == 0) {
            return 1.0;
        }
        double y = quickMul(x, N / 2);
        return N % 2 == 0 ? y * y : y * y * x;
    }

    double myPow(double x, int n) {
        long long N = n;
        return N >= 0 ? quickMul(x, N) : 1.0 / quickMul(x, -N);
    }
};
