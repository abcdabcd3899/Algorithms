// 方法一： 使用递归树得到的解法
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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        // 下面的三个 if 都是最基本的边界情况，是否能够合并呢？
        if(p == nullptr && q == nullptr) return true;
        if(p == nullptr || q == nullptr) return false;
        if(p->val == q->val && p->left == nullptr && p->right == nullptr && q->left== nullptr && q->right == nullptr){
            return true;
        }
        bool left_flag = isSameTree(p->left, q->left);
        bool right_flag = isSameTree(p->right, q->right);
        return (p->val == q->val && left_flag && right_flag);
    }
};

// 方法一简化了递归结束的条件
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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        // 下面的三个 if 都是最基本的边界情况，是否能够合并呢？
        if(p == nullptr && q == nullptr) return true;
        if(p == nullptr || q == nullptr) return false;
        // if(p->val == q->val && p->left == nullptr && p->right == nullptr && q->left== nullptr && q->right == nullptr){
        //     return true;
        // } // 这个条件实际上不需要
        bool left_flag = isSameTree(p->left, q->left);
        bool right_flag = isSameTree(p->right, q->right);
        return (p->val == q->val && left_flag && right_flag);
    }
};


// 方法二：不是很规范的递归写法
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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if(p == nullptr && q == nullptr){
            return true;
        }
        
        if(q!= nullptr && p != nullptr && p->val == q->val ){
            bool leftChildren = isSameTree(p->left, q->left);
            if(leftChildren){
                bool rightChildren = isSameTree(p->right, q->right);
                if(rightChildren){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }else
            return false;
    }
};
