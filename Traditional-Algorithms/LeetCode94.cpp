// 中序遍历，递归版本
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
    vector<int> inorderTraversal(TreeNode* root) {
        if(root == nullptr) return {};
        
        vector<int> ans;
        vector<int> ans_left;
        
        if(root->left != nullptr) ans_left = inorderTraversal(root->left);
        ans.insert(ans.end(), ans_left.begin(), ans_left.end());   // 插入左孩子
        ans.push_back(root->val);  //插入根节点
        
        vector<int> ans_right;
        if(root->right != nullptr) ans_right = inorderTraversal(root->right);
        ans.insert(ans.end(), ans_right.begin(), ans_right.end()); //插入右孩子
        
        return ans;
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
// 中序遍历，迭代版本，左根右
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        if(root == nullptr) return vector<int>{};
        vector<int> res;
        stack<TreeNode*> s;
        while(root != nullptr || !s.empty()){
            while(root != nullptr){
                s.push(root);
                root = root->left;
            }
            root = s.top();
            s.pop();
            res.push_back(root->val);
            root = root->right;
        }
        return res;
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
// morris遍历
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        if(!root) return {};
        TreeNode* cur = root;
        TreeNode* mostRight = nullptr;
        vector<int>res;
        while(cur){
            mostRight = cur->left;
            if(mostRight){
                while(mostRight->right && mostRight->right != cur){
                    mostRight = mostRight->right;
                }
                if(mostRight->right == nullptr){
                    // 第一次访问到该节点
                    mostRight->right = cur;
                    cur = cur->left;
                    continue;
                }else{
                    // 说明当前mostRight->right = cur
                    mostRight->right = nullptr;
                    res.push_back(cur->val);
                    cur = cur->right;
                }
                
            }else{
                // 说明当前cur节点没有左子树
                res.push_back(cur->val);
                cur = cur->right;
            }
        }
        return res;
    }
};
