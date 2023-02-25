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
// 递归实现交换
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if(root == nullptr) return nullptr;
        TreeNode* ansLeft = invertTree(root->left);
        TreeNode* ansRight = invertTree(root->right);
        root->left = ansRight;
        root->right = ansLeft;
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
// 迭代实现二叉树的镜像,使用宽度优先搜索
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if(root == nullptr) return nullptr;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            TreeNode* current = q.front();
            q.pop();
            if(current->left) q.push(current->left);
            if(current->right) q.push(current->right);
            
            // 交换当前节点的左右节点
            TreeNode* tmp = current->right;
            current->right = current->left;
            current->left = tmp;
        }
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
// 迭代实现二叉树的镜像,使用宽度优先搜索
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if(root == nullptr) return nullptr;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            TreeNode* current = q.front();
            q.pop();
            if(current->left) q.push(current->left);
            if(current->right) q.push(current->right);
            
            // 交换当前节点的左右节点
            // TreeNode* tmp = current->right;
            // current->right = current->left;
            // current->left = tmp;
            swap(current->left, current->right);  // 使用algorithm提供的swap函数
        }
        return root;
    }
};