// 斐波那契模型
class Solution {
public:
    int climbStairs(int n) {
        int dp[n+1];  // 爬到 n 层楼梯的方法数
        if (n == 1) {
            return 1;
        }
        if (n == 2) {
            return 2;
        }
        dp[0] = 0; // 这个初始化可以去掉，碰不到这里
        dp[1] = 1;
        dp[2] = 2;
        for (int i = 3; i <= n; i++) {
          dp[i] = dp[i-1] + dp[i - 2];
        }
        return dp[n];
    }
};


// 线性动态规划
// dp[i] 表示爬到 i 需要的方法数
// dp[i] = dp[i-1] + dp[i-2]
class Solution {
public:
    int climbStairs(int n) {
        if(n == 0)
            return 0;
        if(n == 1)
            return 1;
        if(n == 2)
            return 2;
        int dp[n+1];
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 2;
        for(int i = 3; i <= n; i++)
            dp[i] = dp[i-1] + dp[i-2];
        return dp[n];
    }
};