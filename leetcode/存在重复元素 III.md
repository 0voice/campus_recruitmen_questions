# 题目
给你一个整数数组 nums 和两个整数 k 和 t 。请你判断是否存在 两个不同下标 i 和 j，使得 abs(nums[i] - nums[j]) <= t ，同时又满足 abs(i - j) <= k 。

如果存在则返回 true，不存在返回 false。

示例 1：

    输入：nums = [1,2,3,1], k = 3, t = 0
    输出：true
示例 2：

    输入：nums = [1,0,1,1], k = 1, t = 2
    输出：true
示例 3：

    输入：nums = [1,5,9,1,5,9], k = 2, t = 3
    输出：false
 

提示：

* 0 <= nums.length <= 2 * 10<sup>4</sup>
* -2<sup>31</sup> <= nums[i] <= 2<sup>31</sup> - 1
* 0 <= k <= 10<sup>4</sup>
* 0 <= t <= 2<sup>31</sup> - 1

# 参考答案
```c++
class Solution {
public:
    int getID(int x, long w) {
        return x < 0 ? (x + 1ll) / w - 1 : x / w;
    }

    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        unordered_map<int, int> mp;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            long x = nums[i];
            int id = getID(x, t + 1ll);
            if (mp.count(id)) {
                return true;
            }
            if (mp.count(id - 1) && abs(x - mp[id - 1]) <= t) {
                return true;
            }
            if (mp.count(id + 1) && abs(x - mp[id + 1]) <= t) {
                return true;
            }
            mp[id] = x;
            if (i >= k) {
                mp.erase(getID(nums[i - k], t + 1ll));
            }
        }
        return false;
    }
};
