# 题目
输入一个数组和一个数字 s，在数组中查找两个数，使得它们的和正好是 s。

如果有多对数字的和等于 s，输出任意一对即可。

你可以认为每组输入中都至少含有一组满足条件的输出。

样例
```
输入：[1,2,3,4] , sum=7

输出：[3,4]
```
# 参考答案
```c++
class Solution {
public:
    vector<int> findNumbersWithSum(vector<int>& nums, int target) 
    {
        unordered_map<int, int> hash;//创建哈希表
        for (int i = 0; i < nums.size(); ++i) {
            if(hash[target - nums[i]] == 0)//如果哈希表中没有target - nums[i]
                hash[nums[i]]++;//nums[i]出现次数加1
            else//如果哈希表中有target - nums[i]
                return {nums[i], target - nums[i]};//返回答案
        }
        return {};

    }
};
