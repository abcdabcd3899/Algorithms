// 反转链表的前 n 个节点
#include <iostream>
using namespace std;

struct ListNode{
    int val;
    ListNode* next;
    ListNode(int x):val(x), next(nullptr){};
};


// 反转链表前 n 个元素
ListNode* reverseList(ListNode* head, int n){
    ListNode* nNext = head;
    for(int i = 0; i < n; ++i){
        nNext = nNext->next;
    }
    ListNode* prev = nullptr;
    ListNode* current = head;
    ListNode* tmp;
    while(current->next != nNext){
        tmp = current->next;
        current->next = prev;
        prev = current;
        current = tmp;
    }
    current->next = prev;
    // 将链表接起来
    ListNode* dummy = current;
    while(dummy->next != nullptr){
        dummy = dummy->next;
    }
    dummy->next = nNext;
    return current;
}

int main() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    head->next->next->next->next->next = new ListNode(6);

    ListNode* dummy = reverseList(head, 4);
    ListNode* current = dummy;
    while(current){
    	cout << current->val << " ";
	current = current->next;
    }
    cout << endl;
    return 0;
}
