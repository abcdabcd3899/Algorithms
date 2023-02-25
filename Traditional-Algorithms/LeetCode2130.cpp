// 空间复杂度为 O(n)，虽然浪费了空间，但是方法很简洁
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
    ListNode* tmp;
    int max = 0;
public:
    int pairSum(ListNode* head) {
        tmp = head;
        check(head);
        return max;
    }
    void check(ListNode* p){
        if(p == nullptr) return;
        check(p->next);
        if(max < p->val+tmp->val)
            max = p->val + tmp->val;
        tmp = tmp->next;
        return;
    }
};
