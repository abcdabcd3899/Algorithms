// 经典双指针算法，维护一段区间，并且这段区间内不能有重复数字，找到这个区间数字和的最大值
class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        int len = nums.size();
        int res = 0;
        unordered_map<int, int> m;
        int max = 0; 
        for(int i = 0, j = 0; i < len; i++){
            m[nums[i]]++;
            res += nums[i];
            while(j < i && m[nums[i]] > 1){
                m[nums[j]]--;
                res -= nums[j];
                j++;
            }
            if(res > max) max = res;
        }
        return max;
    }
};
