// 根据递归树写出的递归版本
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
    vector<int> preorderTraversal(TreeNode* root) {
        if(root == nullptr) return {};
        vector<int> ans_left = preorderTraversal(root->left);
        vector<int> ans_right = preorderTraversal(root->right);
        vector<int> ans;
        ans.push_back(root->val);
        ans.insert(ans.end(), ans_left.begin(), ans_left.end());
        ans.insert(ans.end(), ans_right.begin(), ans_right.end());
        return ans;
    }
};


// 先序遍历，递归版本，也是标准呢的递归树解法
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
    vector<int> preorderTraversal(TreeNode* root) {
        TreeNode* current = root;
        vector<int> ans;
        if(current == nullptr){
            return {};
        }
        ans.push_back(current->val);
        vector<int> ans_left = preorderTraversal(current->left);
        vector<int> ans_right = preorderTraversal(current->right);
        
        ans.insert(ans.end(),ans_left.begin(),ans_left.end());
        ans.insert(ans.end(),ans_right.begin(),ans_right.end());
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

//先序遍历，根左右，迭代版本
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        if(root == nullptr) return {};
        vector<int> ans;
        stack<TreeNode*> s;
        
        while(root || !s.empty()){
            while(root){
                s.push(root);
                ans.push_back(root->val);
                root = root->left;
            }
            root = s.top();
            s.pop();
            root = root->right;
        }
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
// morris遍历
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
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
                    mostRight->right = cur;
                    res.push_back(cur->val);
                    cur = cur->left;
                    continue;
                }else{ // 这个分支说明返回到cur节点上，则此时应该指向右孩子
                    mostRight->right = nullptr;
                    cur = cur->right;
                }
            }else{// 这个分支说明当前cur节点没有左孩子，对于先序遍历而言应该输出
                res.push_back(cur->val);
                cur = cur->right;
            }
        }
        return res;
    }
};
