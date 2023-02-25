/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// 通过先序遍历实现
class Codec {
public:
    // Encodes a tree to a single string.
    //递归序列化
    // string serialize(TreeNode* root) {
    //     if(!root) return "#!";
    //     string res = to_string(root->val) + "!";
    //     res += serialize(root->left);
    //     res += serialize(root->right);
    //     return res;
    // }
    
    // 迭代序列化
    string serialize(TreeNode* root) {
        if(!root) return "#!";
        stack<TreeNode*> s;
        string res;
        while(root || !s.empty()){
            while(root){
                string tmp = to_string(root->val) + "!";
                res += tmp;
                s.push(root);
                root = root->left;
            }
            // 走到最左边
            root = s.top();
            if(!root->left) res += "#!";
            if(!root->right) res += "#!";
            s.pop();
            root = root->right;
        }
        return res;
    }
    
    // Decodes your encoded data to tree.
    // 递归反序列化
    TreeNode* deserialize(string data) {
        queue<string>q;
        vector<string> str = split(data, "!");
        int len = str.size();
        for(int i = 0; i < len; i++){
            q.push(str[i]);
        }
        return constructBST(q);
    }
    
    TreeNode* constructBST(queue<string>& q){
        string s = q.front();
        q.pop();
        if(s == "#") return nullptr;
        TreeNode* root = new TreeNode(stoi(s));
        root->left = constructBST(q);
        root->right = constructBST(q);
        return root;
    }
    
    // 将字符串按照分隔符拆分成字符数组
    vector<string> split(string str, string delimiter){
        vector<string> res;
        string token;
        int pos = 0;
        while ((pos = str.find(delimiter)) != std::string::npos) {
            token = str.substr(0, pos);
            res.push_back(token);
            str.erase(0, pos + delimiter.size());
        }
        return res;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;