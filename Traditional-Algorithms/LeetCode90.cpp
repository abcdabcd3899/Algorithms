// 方法一 遍历
// 两点很重要，第一是先首先给 nums 排序，这有利于去重操作
// 第二点是使用搜索
class Solution {
    vector<int> one = {};
    vector<vector<int>> ans;
    stack<vector<int>> st;
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        if(nums.size() == 0){
            return {};
        }
        sort(nums.begin(), nums.end());
        dfs(nums, 0);
        return ans;
    }
    
    void dfs(vector<int>& nums, int start){
        ans.push_back(one);
        
        for(int i = start; i < nums.size(); ++i){
            if(i > start &&nums[i] == nums[i-1])
                continue;
            st.push(one);
            one.push_back(nums[i]);
            dfs(nums, i+1);
            one = st.top();
            st.pop();
        }
    }
};

// 方法二 枚举
// 枚举： 分别枚举大小为 0, 1, 2, 3, 4...n 的所有的排列
// 这是一个能够提交的答案，但是需要更长的时间
class Solution {
public:
    bool compareVectors(std::vector<int> a, std::vector<int> b)
    {
       if (a.size() != b.size())
       {
          return false;
       }
       ::std::sort(a.begin(), a.end());
       ::std::sort(b.begin(), b.end());
       return (a == b);
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>>res;
        res.push_back({});  // 将空集加入到结果集中
        int len = nums.size();
        
        // 分别枚举长度为 i 的子集
        for(int i = 0; i <= len; ++i){
            vector<int> tmp;
            for(int j = 0; j < len - i; ++j) tmp.push_back(0);
            for(int j = 0; j < i; ++j) tmp.push_back(1);
            
            // 然后根据 tmp 的 permutation 的得到子集
            do{
                vector<int> ans;
                bool flag = true;
                for(int k = 0; k < len; ++k){
                    if(tmp[k]) ans.push_back(nums[k]); 
                }
                for(auto u: res){
                    if(compareVectors(ans, u))
                    {
                        flag = false;
                        break;
                    }
                }
                if(flag) res.push_back(ans);
            }while(next_permutation(tmp.begin(), tmp.end()));
        }
        return res;
    }
};

// 方法三 枚举
// 方法三和方法二只是在 compareVectors 时倒着遍历，这样子一定程度上能减少不少判断
// 枚举： 分别枚举大小为 0, 1, 2, 3, 4...n 的所有的排列
class Solution {
public:
    bool compareVectors(std::vector<int> a, std::vector<int> b)
    {
       if (a.size() != b.size())
       {
          return false;
       }
       ::std::sort(a.begin(), a.end());
       ::std::sort(b.begin(), b.end());
       return (a == b);
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>>res;
        res.push_back({});  // 将空集加入到结果集中
        int len = nums.size();
        // 分别枚举长度为 i 的子集
        for(int i = 0; i <= len; ++i){
            vector<int> tmp;
            for(int j = 0; j < len - i; ++j) tmp.push_back(0);
            for(int j = 0; j < i; ++j) tmp.push_back(1);
            
            // 然后根据 tmp 的 permutation 的得到子集
            do{
                vector<int> ans;
                bool flag = true;
                for(int k = 0; k < len; ++k){
                    if(tmp[k]) ans.push_back(nums[k]); 
                }
                for(int i = res.size()-1; i >= 0; --i){
                    if(compareVectors(ans, res[i]))
                    {
                        flag = false;
                        break;
                    }
                }
                if(flag) res.push_back(ans);
            }while(next_permutation(tmp.begin(), tmp.end()));
        }
        return res;
    }
};

// 这里一个非常重要的问题：如何判断两个 vector 是否相等？

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
using namespace std;
int main(){
        vector v1 = {4,4,1,4};
        vector v2 = {4,4,1,4};
        printf("%s %c", v1 == v2 ? "相等": "不相等", '\n');

        vector v3 = {4,4,4,1};
        printf("%s %c", v2 == v3 ? "相等": "不相等", '\n');

        printf("%s %c", std::equal(v2.begin(), v2.end(), v3.begin()) ? "相等": "不相等", '\n');
        return 0;
}

// 上述代码的输出为：
/**
 * 相等
 * 不相等
 * 不相等
**/

/**
 * 只有当 v1 和 v2 有相同的顺序时，才会用上述的比较方法去判断是否两个向量相等
**/
