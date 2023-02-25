// bytedance
#include <iostream>
using namespace std;

struct ListNode{
    int val;
    ListNode* next;
    ListNode(int x):val(x), next(nullptr){};
};

// 反转指定链表
ListNode* reverse(ListNode* head){
    if(head == nullptr) return nullptr;
    ListNode* prev = nullptr;
    ListNode* current = head;
    ListNode* tmp;
    while(current->next != nullptr){
        tmp = current->next;
        current->next = prev;
        prev = current;
        current = tmp;
    }
    current->next = prev;
    return current;
}

// 反转链表最后 n 个元素
ListNode* reverseList(ListNode* head, int n){
    int len = 0;
    ListNode* current = head;

    // 求出链表长度
    while(current != nullptr){
        len++;
        current = current->next;
    }
    // 如果 n 等于链表长度，此时需要反转整个链表，如果 n > len 这种情况目前没有定义行为，出于完整性考虑，应该增加该部分的处理
    if(n == len){
        return reverse(head);
    }
    // 找到反转的位置，然后将反转的位置的前一个位置，然后将后续节点调用 reverse 反转
    int position = 0;
    current = head;
    ListNode* dummy;
    ListNode* prev;
    while(current != nullptr){
        if(position == len - n - 1){
            prev = current;
            dummy = reverse(prev->next);
            break;
        }
        position++;
        current = current->next;
    }

    // 最后将返回的dummy 与上述找到的位置拼接即可
    prev->next = dummy;
    return head;
}

int main() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    head->next->next->next->next->next = new ListNode(6);

    ListNode* dummy = reverseList(head, 6);
    ListNode* current = dummy;
    while(current){
    	cout << current->val << " ";
	    current = current->next;
    }
    cout << endl;
    return 0;
}
