# 题目
输入 n 个整数，找出其中最小的 k 个数。

注意：

输出数组内元素请按从小到大顺序排序;<br>
数据范围<br>
1≤k≤n≤1000<br>
样例
```
输入：[1,2,3,4,5,6,7,8] , k=4

输出：[1,2,3,4]
```
# 参考答案
```c++
class Solution {
public:
    vector<int> getLeastNumbers_Solution(vector<int> input, int k) {
        vector<int> res;
        priority_queue<int> heap;
        for(auto x : input)
        {
            heap.push(x);
            if(heap.size() > k) heap.pop(); 
        }
        while(heap.size())
        {
            res.push_back(heap.top());
            heap.pop();
        }
        reverse(res.begin(),res.end());
        return res;
    }
};

