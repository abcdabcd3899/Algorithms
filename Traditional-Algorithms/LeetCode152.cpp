class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int len = nums.size();
        if(len == 0){
            return 0;
        }
        
        vector<int> maxArray(len);
        vector<int> minArray(len);
        int ans = INT_MIN;
        for(int i = 0; i < len; ++i){
            maxArray[i] = nums[i];
            if(i > 0){
                maxArray[i] = max(nums[i], max(nums[i]*maxArray[i-1], nums[i]*minArray[i-1]));
            }
            
            minArray[i] = nums[i];
            if(i > 0){
                minArray[i] = min(nums[i], min(nums[i]*maxArray[i-1], nums[i]*minArray[i-1]));
            }
            ans = max(ans, maxArray[i]);
        }
        return ans;
    } 
};

// 典型的最值型动态规划
// 仍然考虑到最后一步可能是 nums[i]
// 此时需要考虑 i - 1 的值,如果 nums[i] 和 前一个同号,那么取最大值
// 如果异号,则取最小值,因此这里我们需要同时更新最大值和最小值
class Solution {
    const int MIN = -0x3f3f3f3f;
public:
    int maxProduct(vector<int>& nums) {
        int len = nums.size();
        int dp_min[len];
        int dp_max[len];
        
        for(int i = 0; i < len; ++i)
        {
            dp_max[i] = nums[i];
            if(i > 0)
                dp_max[i] = max(dp_max[i], max(dp_max[i-1]*nums[i], dp_min[i-1]* nums[i]));
            dp_min[i] = nums[i];
            if(i > 0)
                dp_min[i] = min(dp_min[i], min(dp_max[i-1]* nums[i], dp_min[i-1]* nums[i]));
        }
        int res = MIN;
        for(int i = 0; i < len; i++)
            if(res < dp_max[i])
                res = dp_max[i];
        return res;
    }
};
