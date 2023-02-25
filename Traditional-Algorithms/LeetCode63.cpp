// 坐标型动态规划题目，也可以叫做线性DP
// 状态集合：从（1，1）到（n，m）的路径
// 状态属性：路径和sum
// 状态计算： f[i][j] = f[i-1][j] + f[i][j-1]，更新状态要注意，如果是障碍物，则不必更新f数组
// 一定要注意在初始化第一行和第一列时，循环结束的条件，一旦遇到障碍物，后面所有的路都走不通
class Solution {
    static const int N = 110;
    int f[N][N];  // 状态数组
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int n = obstacleGrid.size();
        int m = obstacleGrid[0].size();
        
        // 更新第一行数据
        for(int j = 1; j <= m; j++){
            if(!obstacleGrid[0][j-1]) f[1][j] = 1;
            else break;
        }
        
        // 更新第一列数据
        for(int i = 1; i <= n; i++){
           if(!obstacleGrid[i-1][0]) f[i][1] = 1;
            else break;
        }
        
        // 其他位置
        for(int i = 2; i <= n; i++){
            for(int j = 2; j <= m; j++){
                if(!obstacleGrid[i-1][j-1]) f[i][j] = f[i-1][j] + f[i][j-1];
            }
        }
        
        return f[n][m];
    }
};


// 带障碍的坐标型动态规划问题
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& nums) {
        int m = nums.size();
        int n = nums[0].size();
        
        int dp[m][n];
        
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++){
                if(nums[i][j] == 1){
                    dp[i][j] = 0;
                    continue;
                }
                
                if(i == 0 && j == 0){
                    dp[i][j] = 1;
                    continue;
                }
                dp[i][j] = 0;
                if(i > 0)
                    dp[i][j] += dp[i-1][j];
                if(j > 0)
                    dp[i][j] += dp[i][j-1];
            }
        return dp[m-1][n-1];
    }
};

// 有障碍的坐标型动态规划问题,目前我觉得最明了的方法
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& nums) {
        int m = nums.size();
        int n = nums[0].size();
        
        int dp[m][n];
        // 初始化
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
                dp[i][j] = 0;
        
        // 处理第一行
        for(int j = 0; j < n; j++){
            if(nums[0][j] == 0) dp[0][j] = 1;
            else break;  // 不可达
        }
        
        // 处理第一列
        for(int i = 0; i < m; i++){
            if(nums[i][0] == 0) dp[i][0] = 1;
            else break;
        }
        
        // 什么时候不更新 dp[i][j]? 转移方程
        for(int i = 1; i < m; i++)
            for(int j = 1; j < n; j++){
                if(nums[i][j] == 0) dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        return dp[m-1][n-1];
    }
};
