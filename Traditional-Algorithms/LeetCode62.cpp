class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n)); 
        int i, j;
        for(i = 0; i < m; i++){
            for(j = 0; j < n; j++){
                if(i == 0 || j == 0){
                    dp[i][j] = 1;
                    continue;
                }
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        return dp[m-1][n-1];
    }
};


// 动态规划 f[i][j] = f[i-1][j] + f[i][j-1]
// 该类型动态规划问题既可以归类为坐标型，也可以归类的线性DP
// 凡是在求解动态规划问题时，能够从左往右、从上到校求解的问题都能归结为线性DP
class Solution {
    static const int N = 110;
    int f[N][N];
public:
    int uniquePaths(int m, int n) {
        for(int j = 1; j <=m; j++){
            f[1][j] = 1;
        }
        for(int i = 1; i <= n; i++){
            f[i][1] = 1;
        }
        
        for(int i = 2; i <= n; i++){
            for(int j = 2; j <= m; j++){
                f[i][j] = f[i-1][j] + f[i][j-1];
            }
        }
        
        return f[n][m];
    }
    
};


class Solution {
public:
    int uniquePaths(int m, int n) {
        int dp[m][n];
        dp[0][0] = 1;
        for(int j = 0; j < n; j++)
            dp[0][j] = 1;
        for(int i = 0; i < m; i++)
            dp[i][0] = 1;
        
        for(int i = 1; i < m; i++)
            for(int j = 1; j < n; j++)
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
        return dp[m-1][n-1];
    }
};
