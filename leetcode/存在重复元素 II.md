# 题目
给定一个整数数组和一个整数 k，判断数组中是否存在两个不同的索引 i 和 j，使得 nums [i] = nums [j]，并且 i 和 j 的差的 绝对值 至多为 k。

示例 1:

    输入: nums = [1,2,3,1], k = 3
    输出: true
示例 2:

    输入: nums = [1,0,1,1], k = 1
    输出: true
示例 3:

    输入: nums = [1,2,3,1,2,3], k = 2
    输出: false

# 参考答案
```c++
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_set<int> existed;
        int n = nums.size();
        int curr = 0;
        for (int i = 0; i < n; ++i)
        {
            curr = nums[i];
            if (existed.find(curr) == existed.end())
            {
                existed.insert(curr);
                if (existed.size() > k)
                {
                    existed.erase(nums[i-k]);
                }
            }
            else
            {
                return true;
            }
        }

        return false;
    }
};
