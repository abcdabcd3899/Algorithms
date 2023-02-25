// 快慢指针，比较好的办法，其它办法对找到中间节点这件事情都过于麻烦
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* deleteMiddle(ListNode* head) {
        if(head == nullptr || head->next == nullptr) return nullptr;
        ListNode* slow = head;
        ListNode* fast = head->next;
        ListNode* prev = nullptr;
        while(fast){
            prev = slow;
            slow = slow->next;
            fast = fast->next;
            if(fast)
                fast = fast->next;
        }
        prev->next = slow->next;
        return head;
    }
};
