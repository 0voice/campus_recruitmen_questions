# 题目
给定一个Excel表格中的列名称，返回其相应的列序号。

例如，

    A -> 1
    B -> 2
    C -> 3
    ...
    Z -> 26
    AA -> 27
    AB -> 28 
    ...
示例 1:

    输入: "A"
    输出: 1
示例 2:

    输入: "AB"
    输出: 28
示例 3:

    输入: "ZY"
    输出: 701

# 参考答案
```c++
class Solution {
public:
    int titleToNumber(string columnTitle) {
        int number = 0;
        long multiple = 1;
        for (int i = columnTitle.size() - 1; i >= 0; i--) {
            int k = columnTitle[i] - 'A' + 1;
            number += k * multiple;
            multiple *= 26;
        }
        return number;
    }
};
