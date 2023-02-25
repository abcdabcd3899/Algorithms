class Solution {
public:
    Solution(vector<int>& nums) {
        v.assign(std::begin(nums), std::end(nums));  // C++ 11
    }
    
    vector<int> reset() {
        return v;
    }
    
    vector<int> shuffle() {
        vector<int> res;
        res.assign(std::begin(v), std::end(v));
        int len = res.size();
        for(int i = 0; i < len; i++){
            int pos = rand() % len;
            swap(res[i], res[pos]);
        }
        return res;
    }
public:
    vector<int> v;   // 内部成员变量，供其他函数使用
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */


// 这个题目实际上能看成一个 蓄水池抽样，但是下面的解法在 vector 超大时超时了
// 所有元素的 next_permutation 的蓄水池
// 蓄水池的大小仍然为 1
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

class Solution {
public:
    Solution(vector<int>& nums) {
        res.assign(nums.begin(), nums.end());
    }

    vector<int> reset() {
        return res;
    }

    vector<int> shuffle() {
        vector<int>tmp(res);
        sort(tmp.begin(), tmp.end());
        vector<int>ans(res);
        int count = 1;
        do{
            count++;
            int rd = (rand() % count) + 1;  // [1, count]
            if(rd == 1) ans = tmp;
        }while(next_permutation(tmp.begin(), tmp.end()));
        return ans;
    }
private:
    vector<int>res;
};

int main(){
   vector<int>nums{1,2,3,4,5,6,7,8,9,10,11,12};
   Solution* obj = new Solution(nums);
   vector<int> param_1 = obj->reset();
   vector<int> param_2 = obj->shuffle();
   for(auto u: param_2){
      cout << u << " ";
   }
   cout << endl;
   return 0;
}


// 解法三 蓄水池抽样 AC
// reservior sampling
// reservior size is 1 
// reservior element is the permutation of vector using std::next_permutation() gets
class Solution {
public:
    Solution(vector<int>& nums) {
        res.assign(nums.begin(), nums.end());
    }
    
    vector<int> reset() {
        return res;
    }
    
    vector<int> shuffle() {
        vector<int>tmp(res);
        sort(tmp.begin(), tmp.end());   // sort the tmp in order to iterate the next_permutation by dictionary sorts
        vector<int>ans(tmp);   // puts the reservior initiator
        int count = 1;
        while(next_permutation(tmp.begin(), tmp.end()) && count < 5e4){  // reservior sampling
            count++;
            int rd = (rand() % count) + 1;
            if(rd == 1) ans = tmp;
        }
        return ans;
    }
private:
    vector<int>res;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */



// reservior sampling
// reservior size is 1 
// reservior element is the permutation of vector using std::next_permutation() gets
class Solution {
public:
    Solution(vector<int>& nums) {
        res.assign(nums.begin(), nums.end());
    }
    
    vector<int> reset() {
        return res;
    }
    
    vector<int> shuffle() {
        vector<int>tmp(res);
        sort(tmp.begin(), tmp.end());   // sort the tmp in order to iterate the next_permutation by dictionary sorts
        vector<int>ans(tmp);   // puts the reservior initiator
        int count = 1;
        while(next_permutation(tmp.begin(), tmp.end()) && count < 525){  // reservior sampling, 525 is stop condition, why?
            count++;
            int rd = (rand() % count) + 1;
            if(rd == 1) ans = tmp;
        }
        return ans;
    }
private:
    vector<int>res;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */
