# 题目
将一个给定字符串 s 根据给定的行数 numRows ，以从上往下、从左到右进行 Z 字形排列。

比如输入字符串为 "PAYPALISHIRING" 行数为 3 时，排列如下：
```
P   A   H   N
A P L S I I G
Y   I   R
```
之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如："PAHNAPLSIIGYIR"。

请你实现这个将字符串进行指定行数变换的函数：
```
string convert(string s, int numRows);
```

示例 1：
```
输入：s = "PAYPALISHIRING", numRows = 3
输出："PAHNAPLSIIGYIR"
```
示例 2：
```
输入：s = "PAYPALISHIRING", numRows = 4
输出："PINALSIGYAHRPI"
解释：
P     I    N
A   L S  I G
Y A   H R
P     I
```
示例 3：
```
输入：s = "A", numRows = 1
输出："A"
```

提示：

1 <= s.length <= 1000<br>
s 由英文字母（小写和大写）、',' 和 '.' 组成<br>
1 <= numRows <= 1000

# 参考答案
```c++
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows <= 1) {
            return s;
        }

        string new_s;
        for (int row = 0; row < numRows; row++) {
            int delta;
            int interval1 = numRows + (numRows - 2) - row * 2;
            int interval2 = 2 * row;
            bool flag = false;
            for (int i = row; i < s.length(); i += delta) {
                new_s.push_back(s[i]);
                do {
                    delta = !flag ? interval1 : interval2;
                    flag = !flag;
                } while (delta == 0);
            }
        }

        return new_str;
    }
};
