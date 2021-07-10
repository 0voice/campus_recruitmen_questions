# 题目
给定一个非负索引 k，其中 k ≤ 33，返回杨辉三角的第 k 行。

![image](https://user-images.githubusercontent.com/59190045/125155104-455a0600-e190-11eb-91a7-502d191b7134.png)

在杨辉三角中，每个数是它左上方和右上方的数的和。

示例:

    输入: 3
    输出: [1,3,3,1]

# 参考答案
```c++
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> row(rowIndex + 1);
        row[0] = 1;
        for (int i = 1; i <= rowIndex; ++i) {
            row[i] = 1LL * row[i - 1] * (rowIndex - i + 1) / i;
        }
        return row;
    }
};
