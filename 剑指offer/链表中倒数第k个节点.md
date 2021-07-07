# 题目
输入一个链表，输出该链表中倒数第 k 个结点。

注意：

k >= 1;<br>
如果 k 大于链表长度，则返回 NULL;

样例
```
输入：链表：1->2->3->4->5 ，k=2

输出：4
```
# 参考答案
```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* findKthToTail(ListNode* head, int k) {
        int n = 0;
        for (auto p = head; p; p = p->next) n ++ ;
        if (n < k) return nullptr;
        auto p = head;
        for (int i = 0; i < n - k; i ++ ) p = p->next;
        return p;
    }
};
