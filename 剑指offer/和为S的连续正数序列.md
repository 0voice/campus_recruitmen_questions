# 题目
输入一个正数 S，打印出所有和为 S 的连续正数序列（至少含有两个数）。

例如输入 15，由于 1+2+3+4+5=4+5+6=7+8=15，所以结果打印出 3 个连续序列 1∼5、4∼6 和 7∼8。

样例
```
输入：15

输出：[[1,2,3,4,5],[4,5,6],[7,8]]
```
# 参考答案
```c++
class Solution {
public:
    vector<vector<int> > findContinuousSequence(int sum) {
        vector<vector<int>> res;
        vector<int> path;
        for(int i = 1, j = 2; j < sum && i < j; j) {
            int ans = (i + j) * (j - i + 1) / 2;
            if ( ans == sum){//如果相同就加入。
                int k = i;
                while(k <= j)
                    path.push_back(k++);
                res.push_back(path);
                path.clear();
                i ++, j ++;//两个指针同时往后移。
            }
            else if ( ans < sum) {//如果比较小，j就往后移动。
                j ++;
            }
            else 
                i ++;//否则i往后移动
        }
        return res;

    }
};
