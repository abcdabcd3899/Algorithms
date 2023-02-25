// 这种构建 BST 的方法具有致命的缺点，必须提前知道节点的总数，当数据保存在文件中等时，我们无法预先知道节点总数，所以这种方法不是很有用
// Kruse - Data Structures Program Design in C++-Prentice Hall PTR (2001) 10.3 节给出了一个更实用的方法，但是这种方法的缺点是可能不能保证 BST 高度平衡，实际应用中需要取舍
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
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return BST(nums, 0, nums.size()-1);
    }
    TreeNode* BST(vector<int>& nums, int left, int right){
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
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        int len = nums.size();
        int left = 0;
        int right = len - 1;
        return constructBST(nums, left, right);
    }
    TreeNode* constructBST(vector<int>& nums, int left, int right){
        if(left > right) return nullptr;
        int mid = left + (right-left) >> 1;
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = constructBST(nums,left, mid-1);
        root->right = constructBST(nums, mid+1, right);
        return root;
    }
};
