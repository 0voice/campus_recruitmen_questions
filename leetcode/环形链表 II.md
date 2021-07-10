# 题目
给定一个链表，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。

为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 如果 pos 是 -1，则在该链表中没有环。注意，pos 仅仅是用于标识环的情况，并不会作为参数传递到函数中。

说明：不允许修改给定的链表。

示例 1：

![image](https://user-images.githubusercontent.com/59190045/125155938-66712580-e195-11eb-98e9-ae2d1af26570.png)

    输入：head = [3,2,0,-4], pos = 1
    输出：返回索引为 1 的链表节点
    解释：链表中有一个环，其尾部连接到第二个节点。
示例 2：

![image](https://user-images.githubusercontent.com/59190045/125155939-6a04ac80-e195-11eb-907c-d43e124c331c.png)

    输入：head = [1,2], pos = 0
    输出：返回索引为 0 的链表节点
    解释：链表中有一个环，其尾部连接到第一个节点。
示例 3：

![image](https://user-images.githubusercontent.com/59190045/125155942-6cff9d00-e195-11eb-803e-dddc452e957c.png)

    输入：head = [1], pos = -1
    输出：返回 null
    解释：链表中没有环。
 
提示：

* 链表中节点的数目范围在范围 [0, 10<sup>4</sup>] 内
* -10<sup>5</sup> <= Node.val <= 10<sup>5</sup>
* pos 的值为 -1 或者链表中的一个有效索引

# 参考答案
```c++
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *slow = head, *fast = head;
        while (fast != nullptr) {
            slow = slow->next;
            if (fast->next == nullptr) {
                return nullptr;
            }
            fast = fast->next->next;
            if (fast == slow) {
                ListNode *ptr = head;
                while (ptr != slow) {
                    ptr = ptr->next;
                    slow = slow->next;
                }
                return ptr;
            }
        }
        return nullptr;
    }
};
