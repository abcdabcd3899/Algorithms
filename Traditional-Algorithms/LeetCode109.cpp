// 解法一：快慢呢指针 + 递归
// 该方法实际上需要 logn 的栈空间
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
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        return buildBST(head, nullptr);
    }
    
    TreeNode* buildBST(ListNode* first, ListNode* last){
        if(first == last) return nullptr;
        ListNode* mid = findMedian(first, last);
        TreeNode* root = new TreeNode(mid->val);
        root->left = buildBST(first, mid);
        root->right = buildBST(mid->next, last);
        return root;
    }
    
    // 找到中间节点作为根节点
    ListNode* findMedian(ListNode* head, ListNode* tail){
        ListNode* fast = head;
        ListNode* slow = head;
        while(fast != tail){
            fast = fast->next;
            if(fast != tail)
                slow = slow->next, fast = fast->next;
        }
        return slow;
    }
};

// 解法二：同 LeetCode108，利用了多余的 O(n) 数组空间
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        vector<int>nums;
        ListNode* current = head;
        while(current != nullptr){
            nums.push_back(current->val);
            current = current->next;
        }
        return BST(nums, 0 , nums.size()-1);
    }
    TreeNode* BST(vector<int> nums, int left, int right){
        if(left > right){
            return nullptr;
        }
        int mid = left + (right-left)/2;
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = BST(nums, left, mid-1);
        root->right = BST(nums, mid+1, right);
        return root;
    }
};
