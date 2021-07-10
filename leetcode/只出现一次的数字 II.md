# 题目
给你一个整数数组 nums ，除某个元素仅出现 一次 外，其余每个元素都恰出现 三次 。请你找出并返回那个只出现了一次的元素。

示例 1：

    输入：nums = [2,2,3,2]
    输出：3
示例 2：

    输入：nums = [0,1,0,1,0,1,99]
    输出：99
 
提示：

* 1 <= nums.length <= 3 * 10<sup>4</sup>
* -2<sup>31</sup> <= nums[i] <= 2<sup>31</sup> - 1
* nums 中，除某个元素仅出现 一次 外，其余每个元素都恰出现 三次

# 参考答案
```c++
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int a = 0, b = 0;
        for (int num: nums) {
            b = ~a & (b ^ num);
            a = ~b & (a ^ num);
        }
        return b;
    }
};
