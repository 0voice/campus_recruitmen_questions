# 题目
给你一个链表，每 k 个节点一组进行翻转，请你返回翻转后的链表。

k 是一个正整数，它的值小于或等于链表的长度。

如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。

进阶：

* 你可以设计一个只使用常数额外空间的算法来解决此问题吗？
* 你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。
 
示例 1：

![image](https://user-images.githubusercontent.com/59190045/125039307-ec736a80-e0c8-11eb-8b30-08b1fd9ac65d.png)

```
输入：head = [1,2,3,4,5], k = 2
输出：[2,1,4,3,5]
```
示例 2：

![image](https://user-images.githubusercontent.com/59190045/125039367-fac18680-e0c8-11eb-8454-68cc45e3931e.png)
```
输入：head = [1,2,3,4,5], k = 3
输出：[3,2,1,4,5]
```
示例 3：
```
输入：head = [1,2,3,4,5], k = 1
输出：[1,2,3,4,5]
```
示例 4：
```
输入：head = [1], k = 1
输出：[1]
```
提示：

* 列表中节点的数量在范围 sz 内
* 1 <= sz <= 5000
* 0 <= Node.val <= 1000
* 1 <= k <= sz

# 参考答案
```c++
class Solution {
public:
    // 翻转一个子链表，并且返回新的头与尾
    pair<ListNode*, ListNode*> myReverse(ListNode* head, ListNode* tail) {
        ListNode* prev = tail->next;
        ListNode* p = head;
        while (prev != tail) {
            ListNode* nex = p->next;
            p->next = prev;
            prev = p;
            p = nex;
        }
        return {tail, head};
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* hair = new ListNode(0);
        hair->next = head;
        ListNode* pre = hair;

        while (head) {
            ListNode* tail = pre;
            // 查看剩余部分长度是否大于等于 k
            for (int i = 0; i < k; ++i) {
                tail = tail->next;
                if (!tail) {
                    return hair->next;
                }
            }
            ListNode* nex = tail->next;
            // 这里是 C++17 的写法，也可以写成
            // pair<ListNode*, ListNode*> result = myReverse(head, tail);
            // head = result.first;
            // tail = result.second;
            tie(head, tail) = myReverse(head, tail);
            // 把子链表重新接回原链表
            pre->next = head;
            tail->next = nex;
            pre = tail;
            head = tail->next;
        }

        return hair->next;
    }
};
