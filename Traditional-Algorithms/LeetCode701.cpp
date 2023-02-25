// 解法一：递归方法
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
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(root == nullptr){
            root = new TreeNode(val);
            return root;
        }
        
        if(val > root->val){
            root->right = insertIntoBST(root->right,val);
        }else{
            root->left = insertIntoBST(root->left,val);
        }
        return root;
    }
};


// 解法二：迭代方法插入 BST
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
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(root == nullptr) return new TreeNode(val);
        TreeNode* dummy = root;  // 用于查找
        TreeNode* pre = nullptr;  // 用于记录父节点
        while(dummy != nullptr){
            if(val < dummy->val) pre = dummy, dummy = dummy->left;
            else pre = dummy, dummy = dummy->right;
        }
        if(pre->val > val) pre->left = new TreeNode(val);
        else pre->right = new TreeNode(val);
        return root;
    }
};

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
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        insertNode(root, val);
        return root;
    }
    void insertNode(TreeNode*& root, int val){
        if(!root){
            root = new TreeNode(val);
            return;
        }
        if(val < root->val) insertNode(root->left, val);
        else insertNode(root->right, val);
    }
};
