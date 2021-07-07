# 题目
给定一棵二叉搜索树，请找出其中的第 k 小的结点。

你可以假设树和 k 都存在，并且 1≤k≤ 树的总结点数。

样例
```
输入：root = [2, 1, 3, null, null, null, null] ，k = 3

    2
   / \
  1   3

输出：3
```
# 参考答案
```c++
/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
class Solution {
    private TreeNode ans = new TreeNode(-1);
    private int a = 0;//值调用的问题，所以要定义全局变量
    public TreeNode kthNode(TreeNode root, int k) {
        a = k;
        dfs(root);
        return ans;
    }
    public void dfs(TreeNode root){
        if(root == null) return;
        dfs(root.left);
        if(--a == 0) ans = root;
        dfs(root.right);
    }
}
