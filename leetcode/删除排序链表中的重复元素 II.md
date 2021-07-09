# 题目
存在一个按升序排列的链表，给你这个链表的头节点 head ，请你删除链表中所有存在数字重复情况的节点，只保留原始链表中 没有重复出现 的数字。

返回同样按升序排列的结果链表。

示例 1：

![image](https://user-images.githubusercontent.com/59190045/125073658-e2646280-e0ee-11eb-8265-36d059aafa7e.png)

    输入：head = [1,2,3,3,4,4,5]
    输出：[1,2,5]
示例 2：

![image](https://user-images.githubusercontent.com/59190045/125073675-e7c1ad00-e0ee-11eb-81af-a794762f8eff.png)

    输入：head = [1,1,1,2,3]
    输出：[2,3]

提示：

* 链表中节点数目在范围 [0, 300] 内
* -100 <= Node.val <= 100
* 题目数据保证链表已经按升序排列

# 参考答案
```c++
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head) {
            return head;
        }
        
        ListNode* dummy = new ListNode(0, head);

        ListNode* cur = dummy;
        while (cur->next && cur->next->next) {
            if (cur->next->val == cur->next->next->val) {
                int x = cur->next->val;
                while (cur->next && cur->next->val == x) {
                    cur->next = cur->next->next;
                }
            }
            else {
                cur = cur->next;
            }
        }

        return dummy->next;
    }
};
