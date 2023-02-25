// 后序遍历，递归版本
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
    vector<int> postorderTraversal(TreeNode* root) {
        TreeNode* current = root;
        if(current == nullptr){
            return {};
        }
        vector<int> ans;
        vector<int> ans_left;
        vector<int> ans_right;
        
        if(current->left != nullptr){
            ans_left = postorderTraversal(current->left);
        }
        if(current->right != nullptr){
            ans_right = postorderTraversal(current->right);
        }
        ans.push_back(current->val);
        ans_left.insert(ans_left.end(), ans_right.begin(),ans_right.end());
        ans_left.insert(ans_left.end(), ans.begin(), ans.end());
        return ans_left;
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
// 迭代版本，后序遍历，后序遍历：左右根，但是实际上可以写成根右左，然后做一个reverse
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        if(root == nullptr) return {};
        vector<int>ans;
        stack<TreeNode*> s;
        
        while(root || !s.empty()){
            while(root){
                s.push(root);
                ans.push_back(root->val);
                root = root->right;
            }
            root = s.top();
            s.pop();
            root = root->left;
        }
        reverse(ans.begin(), ans.end());
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
// morris遍历, 根右左
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        if(!root) return {};
        TreeNode* cur = root;
        TreeNode* mostLeft = nullptr;
        vector<int>res;
        while(cur){
            mostLeft = cur->right;
            if(mostLeft){
                while(mostLeft->left && mostLeft->left != cur){
                    mostLeft = mostLeft->left;  // 找到最右
                }
                if(mostLeft->left == nullptr){
                    mostLeft->left = cur;
                    res.push_back(cur->val);
                    cur = cur->right;
                    continue;
                }else{
                    mostLeft->left = nullptr;
                    cur = cur->left;
                }
            }else{
                res.push_back(cur->val);
                cur = cur->left;
            }
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
