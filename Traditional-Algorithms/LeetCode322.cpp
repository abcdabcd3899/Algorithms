class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int len = coins.size();
        //dp[0], dp[1], dp[amount]
        vector<int>dp(amount+1);
        dp[0] = 0;
        int i, j;
        for(int i = 1; i <= amount; i++){
            dp[i] = INT_MAX;
            for(int j = 0; j < len; j++){
                if(i >= coins[j] && dp[i-coins[j]] != INT_MAX){
                    dp[i] = min(dp[i], dp[i-coins[j]]+1);
                }
            }
        }
        if(dp[amount] == INT_MAX){
            return -1;
        }
        return dp[amount];
    }
};


// 拼硬币,给定几种面值的硬币,放在 conis 数组中,并且每种硬币有无限枚
// 使用这些硬币拼出 amount 元,给出需要的最少硬币数量,这是最基本的
// 最值型动态规划题目
// 状态转移方程为: dp[i] = min(dp[i], dp[i-coins[j]]+1)
// 采用 dp 数组实现
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int len = coins.size();
        int dp[amount+1];
        dp[0] = 0;
        for(int i = 1; i <= amount; i++){
            dp[i] = 0x3f3f3f3f;
            for(int j = 0; j < len; j++){
                if(i - coins[j] >= 0 && dp[i-coins[j]] != 0x3f3f3f3f)
                    dp[i] = min(dp[i], dp[i-coins[j]]+1);   
            }
        }
        if(dp[amount] == 0x3f3f3f3f)
            return -1;
        return dp[amount];
    }
};
