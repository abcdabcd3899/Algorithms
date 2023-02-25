
// 插入排序，时间复杂度为O(n^2)，空间复杂度为O(1)，TLE 后续对插入排序优化之后能 AC
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
    ListNode* dummy = new ListNode(INT_MIN); //结果链表
    
    ListNode* sortList(ListNode* head) {
        if(head == nullptr) return nullptr;
        
        dummy->next = new ListNode(head->val);
        
        ListNode* current = head->next;
        while(current){
            ListNode* before = dummy->next;  //从头遍历找到合适的位置
            ListNode* after = before->next;
            if(dummy->next->val >= current->val){
                //将当前head的值插入到dummy节点之后
                //在虚拟头结点后面插入数据
                ListNode* tmp = new ListNode(current->val);
                tmp->next = dummy->next;
                dummy->next = tmp;
            }else{
                //否则应该从dummy开始遍历当前节点，找到合适的位置插入
                while(before && after){
                    if(current->val >= before->val && current->val <= after->val){
                        ListNode* tmp = new ListNode(current->val);
                        tmp->next = after;
                        before->next = tmp;  
                        break;
                    }else{
                        before = after;
                        after= before->next;
                    }
                }
                //否则直接插入到before节点之后
                if(after == nullptr){
                    ListNode* tmp = new ListNode(current->val);
                    before->next = tmp;
                }
                
            }
            current = current->next;
        }
        return dummy->next;
    }
};

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

// 插入排序，时间复杂度为O(n^2)，空间复杂度为O(1)，AC，AC的原因是对两种情况做了插入优化：（1）直接在头部插入（第119行）；（2）直接在尾部插入（第128行）。
class Solution {
public:
    ListNode* before;//从头遍历找到合适的位置
    ListNode* last;  //记录最后一个指针
    int maxElement;  //记录一下最大值
    ListNode* sortList(ListNode* head) {
        if(head == nullptr) return nullptr;  
        ListNode* dummy = new ListNode(INT_MIN, new ListNode(head->val)); //结果链表
        head = head->next;
        while(head){
            before = dummy;
            
            //直接在头部插入
            if(head->val <= dummy->next->val){
                ListNode* tmp = new ListNode(head->val, dummy->next);
                dummy->next = tmp;
                head = head->next;
                continue;
            }
            
            //浪费一些空间记录尾部指针，并且用max记录当前的最大值，如果新插入值head->val大于当前
            //最大值，则直接在尾部插入，这样子也免去了下面超长while的遍历过程，从而节省时间
            if(head->val > maxElement && last){
                //直接在最后位置插入
                ListNode* tmp = new ListNode(head->val);
                last->next = tmp;
                last = tmp;
                maxElement = head->val;
                head = head->next;
                continue;
            }
            
            //正常情况，这些值基本都在当前已排好序的链表中间插入，到底插入到哪里，需要遍历查找
            while(before->next){
                if(head->val <= before->next->val){
                    before->next = new ListNode(head->val, before->next);  
                    break;
                }
                before = before->next;
            }
            
            //说明上述while循环遍历到排好序链表的最后，则记录last指针，并且记录最大值
            if(before->next == nullptr){
                last = new ListNode(head->val);
                before->next = last;
                maxElement = head->val;
                 
            }
                
            head = head->next;
        }
        return dummy->next;
    }
};

// 链表的选择排序 时间复杂度为 O(n^2) 空间复杂度为 O(1) Time Limit Exceeded 无优化空间
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
    ListNode* sortList(ListNode* head) {
        if(head == nullptr) return nullptr;
        ListNode* current;
        ListNode* low = head;
        while(low->next != nullptr){
            current = low->next;
            while(current != nullptr){
                if(low->val > current->val)
                    swap(low->val, current->val);
                current = current->next;
            }
            low = low->next;
        }
        return head;
    }
};

// 链表的归并排序 递归 + merge 链表最好的排序方法
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
    ListNode* sortList(ListNode* head) {
        if(head == nullptr || head->next == nullptr) return head;  // 基本递归结束点
        ListNode* slow = head, *fast = head, *pre = head;
        while(fast && fast->next){
            pre = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        pre->next = nullptr; // 断开为两个链表
        ListNode* left = sortList(head);
        ListNode* right = sortList(slow);
        return mergeTwoLists(left, right);
    }
    
    // 直接复用了了合并两个有序链表的代码
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(-1), *cur = dummy;
        while(l1 && l2){
            if(l1->val < l2->val)  cur->next = l1, l1 = l1->next;
            else cur->next = l2, l2 = l2->next;
            cur = cur->next;
        }
        if(l1) cur->next = l1;
        if(l2) cur->next = l2;
        return dummy->next;
    }
};

// 链表的归并排序 递归 + merge
// 划分方法出自《数据结构与算法-C++语言实现》中
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
    ListNode* sortList(ListNode* head) {
        if(head == nullptr || head->next == nullptr) return head;
        ListNode* slow = head, *fast = slow->next;
        while(fast != nullptr){
            fast = fast->next;
            if(fast != nullptr){
                slow = slow->next;
                fast = fast->next;
            }
        }
        ListNode* ListRightHead = slow->next;
        slow->next = nullptr;
        ListNode* left = sortList(head);
        ListNode* right = sortList(ListRightHead);
        return mergeTwoLists(left, right);
    }
    
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(-1), *cur = dummy;
        while(l1 && l2){
            if(l1->val < l2->val)  cur->next = l1, l1 = l1->next;
            else cur->next = l2, l2 = l2->next;
            cur = cur->next;
        }
        if(l1) cur->next = l1;
        if(l2) cur->next = l2;
        return dummy->next;
    }
};


// 链表快速排序 Time Limit Exceeded 可能有优化空间
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
    ListNode* sortList(ListNode *head) {
        quicksort(head, nullptr);
        return head;
    }
    void quicksort(ListNode *head, ListNode *tail) 
    {
    	if(head == tail || head->next == nullptr)
        	return;
        ListNode *mid = partition(head,tail);
    	quicksort(head, mid);
    	quicksort(mid->next, tail);
    }
    ListNode* partition(ListNode *head, ListNode *tail)
    {
        int pivot = head->val;
        ListNode *left = head, *cur = head->next;
        while(cur != nullptr && cur != tail)
        {
            if(cur->val < pivot)
            {
                left = left->next;
                swap(cur->val, left->val);
            }
            cur = cur->next;
        }
        swap(left->val, head->val);
        return left;
    }
};
