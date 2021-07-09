# 题目
给你单链表的头指针 head 和两个整数 left 和 right ，其中 left <= right 。请你反转从位置 left 到位置 right 的链表节点，返回 反转后的链表 。
 
示例 1：

![image](https://user-images.githubusercontent.com/59190045/125076422-784dbc80-e0f2-11eb-93ef-e7203e300489.png)

    输入：head = [1,2,3,4,5], left = 2, right = 4
    输出：[1,4,3,2,5]
示例 2：

    输入：head = [5], left = 1, right = 1
    输出：[5]
 
提示：

* 链表中节点数目为 n
* 1 <= n <= 500
* -500 <= Node.val <= 500
* 1 <= left <= right <= n


# 参考答案
```c++
class Solution {
public:
    ListNode *reverseBetween(ListNode *head, int left, int right) {
        // 设置 dummyNode 是这一类问题的一般做法
        ListNode *dummyNode = new ListNode(-1);
        dummyNode->next = head;
        ListNode *pre = dummyNode;
        for (int i = 0; i < left - 1; i++) {
            pre = pre->next;
        }
        ListNode *cur = pre->next;
        ListNode *next;
        for (int i = 0; i < right - left; i++) {
            next = cur->next;
            cur->next = next->next;
            next->next = pre->next;
            pre->next = next;
        }
        return dummyNode->next;
    }
};
