// 方法：递归 + hash
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
    vector<int> findFrequentTreeSum(TreeNode* root) {
        vector<int> sum = allNodeSum(root);  // 保存每个节点的子树和
        unordered_map<int, int>m;
        int max = 0;
        for(int &u: sum){
            cout << u << endl;
            if(m.find(u) != m.end()){
                // 说明 u 存在，此时其个数 + 1
                m[u]++;
            }else{
                m[u] = 1;
            }
            if(m[u] > max){
                max = m[u];
            }
        }
        
        // 将次数等于 max 的全部结果放入到输出结果中
        vector<int> ans;
        for(auto &v : m){
            if(v.second == max) ans.push_back(v.first);
        }
        return ans;
    }
    
    // 返回所有节点的子树和
    vector<int> allNodeSum(TreeNode* root){
        if(root == nullptr) return {};
        vector<int> ans;
        // 先序遍历，然后求每个节点的子树和
        int left_sum = nodeSum(root->left);
        int right_sum = nodeSum(root->right);
        
        ans.push_back(root->val + left_sum + right_sum);
        
        vector<int> leftV = allNodeSum(root->left);
        vector<int> rightV = allNodeSum(root->right);
        
        ans.insert(ans.end(), leftV.begin(), leftV.end());
        ans.insert(ans.end(), rightV.begin(), rightV.end());
        return ans;
    }
    
    // 返回 root 的子树和，标准写法，对应结果递归树
    int nodeSum(TreeNode* root){
        if(root == nullptr) return 0;
        int left_sum = nodeSum(root->left);
        int right_sum = nodeSum(root->right);
        return root->val + left_sum + right_sum;
    }
};
