// 方法一：先序遍历 + string.find
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
    string preorderTraversal(TreeNode* root) {
        if(root == nullptr) return "";
        string ans;
        stack<TreeNode*> s;
        
        while(root || !s.empty()){
            while(root){
                s.push(root);
                ans += "_";
                ans += to_string(root->val);
                root = root->left;
                if(root == nullptr)
                    ans += "#";
            }
            root = s.top();
            s.pop();
            root = root->right;
            if(root == nullptr)
                ans += "#";
        }
        return ans;
    }
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        string r = preorderTraversal(root);
        cout << r << endl;
        string subr = preorderTraversal(subRoot);
        cout << subr << endl;
        if(r.find(subr) == string::npos)
            return false;
        return true;
    }
};

// 方法二： 标准递归方法
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
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if(root == nullptr) return false;
        if(isSameTree(root, subRoot))
            return true;
        return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
    }
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if(p == nullptr && q == nullptr) return true;
        if(p == nullptr || q == nullptr) return false;
        bool left_flag = isSameTree(p->left, q->left);
        bool right_flag = isSameTree(p->right, q->right);
        return (p->val == q->val && left_flag && right_flag);
    }
};

// 方法三：递归方法（非标准递归思路）
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
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        // 先序遍历节点即可
        if(root && isSameTree(root, subRoot)){
            return true;
        }
        bool leftFlag = false;
        if(root->left){
            leftFlag = isSubtree(root->left, subRoot);
        }
        
        bool rightFlag = false;
        if(!leftFlag && root->right){
            rightFlag = isSubtree(root->right, subRoot);
        }
        
        return leftFlag || rightFlag;
        
    }

    
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
