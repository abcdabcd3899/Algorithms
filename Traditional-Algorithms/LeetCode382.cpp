/** 解法一 标准解法：蓄水池抽样
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
// 大小为 1 的蓄水池
// 第一步： 第一个元素直接放入到蓄水池中
// 接下来从第二个元素开始迭代，生成一个随机数 [1,2,...n],如果随机数位1，就需要替换蓄水池中的元素
// 当遍历完所有的元素后，蓄水池中所有元素被选择的概率相等

class Solution {
public:
    Solution(ListNode* head) {
        this->head = head;
    }
    
    int getRandom() {
        int count = 1;
        ListNode* current = head->next;
        int res = head->val;
        while(current){  // 重复直到遍历完所有的数据
            count++;
            int rd = (rand() % count) + 1; //[1, count]
            if(rd == 1) res = current->val;
            current = current->next;
        }
        return res;
    }
private:
    ListNode* head;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */

/** 解法二
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
    Solution(ListNode* head) {
        h = head;
    }
    
    int getRandom() {
        ListNode* current = h;
        int len = 0;
        while(current){
            len++;
            current = current->next;
        }
        int i = rand() % len;
        // 找到第 i 个 node
        int count = 0;
        current = h;
        while(current){
            if(i == count) return current->val;
            else{
                current = current ->next;
                count++;
            }
        }
        return 0;
    }
public:
    ListNode* h;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */

