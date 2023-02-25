//Dynamic Programming TLE
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int len = nums.size();
        vector<bool>dp(len);
        int i, j;
        dp[0] = true;
        for(i = 1; i < len; i++){
            dp[i] = false;
            for(j = 0; j < i; j++){
               if(dp[j] && j+nums[j] >= i){
                   dp[i] = true;
		   break;
               }
           }
        }
        return dp[len-1];
    }
};

// greedy algorithm AC
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int len = nums.size();
        int currentMaxStep = 0;  //表示能不能跳到i
        for(int i = 0; i < len; ++i){
            if(currentMaxStep < i){
                //到不了
                return false;
            }
            if(currentMaxStep >= len-1){
                //i
                return true;
            }
            currentMaxStep = max(currentMaxStep, i+nums[i]);
        }
        return true;
    }
};

// 动态规划解法 AC
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int len = nums.size();
        bool dp[len];
        dp[0] = true;
        for(int i = 1; i < len; i++)
            dp[i] = false;
        
        for(int i = 0; i < len; i++)
            // 需要注意的是,这里我们从 i-1 往前看,如果从 0 到 i-1 往后看会超时 (TLE)
            // 最好的解法依然是贪心
            for(int j = i-1; j >= 0; j--){
                if(dp[j] && j + nums[j] >= i){
                    dp[i] = true;
                    break;
                }
            }
        return dp[len-1];
    }
};
