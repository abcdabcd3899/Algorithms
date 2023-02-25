// 使用先序遍历
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
    int findTilt(TreeNode* root) {
        if(!root) return 0;
        // 遍历所有节点，算出每个值，然后加起来
        stack<TreeNode*>s;
        int sum = 0;
        while(root || !s.empty()){
            while(root){
                s.push(root);
                int sumLeft = 0;
                int sumRight = 0;
                computeSum(root->left, sumLeft);
                computeSum(root->right, sumRight);
                sum += abs(sumRight-sumLeft);
                root = root->left;
            }
            root = s.top();
            s.pop();
            root = root->right;
        }
        return sum;
    }
    
    // 给定任意节点的左右子树，求出其子树的节点和
    void computeSum(TreeNode*& root, int& sum){
        if(!root) return;
        if(root) sum += root->val;
        computeSum(root->left, sum);
        computeSum(root->right, sum);
        return;
    }
};


// 使用层次遍历
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
    int findTilt(TreeNode* root) {
        if(!root) return 0;
        // 遍历所有节点，算出每个值，然后加起来
        queue<TreeNode*>q;
        int sum = 0;
        q.push(root);
        while(!q.empty()){
            for(int i = 0, j = q.size(); i < j; i++){
                TreeNode* current = q.front();
                q.pop();
                int sumLeft = 0;
                int sumRight = 0;
                computeSum(current->left, sumLeft);
                computeSum(current->right, sumRight);
                sum += abs(sumRight-sumLeft);
                if(current->left) q.push(current->left);
                if(current->right) q.push(current->right);
            }
        }
        return sum;
    }
    
    // 给定任意节点的左右子树，求出其子树的节点和
    void computeSum(TreeNode*& root, int& sum){
        if(!root) return;
        if(root) sum += root->val;
        computeSum(root->left, sum);
        computeSum(root->right, sum);
        return;
    }
};