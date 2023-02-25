// 状态集合： f[i][j] 表示从（1，1）到（i，j）的路径
// 状态属性： 上述路径集合中走到（n, m）最短， min
// 状态计算：f[i][j] = min(f[i-1][j], f[i][j-1]) + a[i][j]
class Solution {
    static const int N = 210;
    int f[N][N];
public:
    int minPathSum(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        // 第一行计算
        for(int j = 1; j <= m; j++){
            f[1][j] = f[1][j-1] + grid[0][j-1];
        }
        // 第一列计算
        for(int i = 1; i <= n; i++){
            f[i][1] = f[i-1][1] + grid[i-1][0];
        }

        // 其它位置
        for(int i = 2; i <= n; i++){
            for(int j = 2; j <= m; j++){
                 f[i][j] = min(f[i-1][j], f[i][j-1]) + grid[i-1][j-1];
            }
        }
        // 输出结果
        return f[n][m];w
    }
};

//坐标型动态规划
// 定义状态,这里我们将状态定义为 dp[i][j] 表示到达 i,j 的最短路径和
// 因此,1. 状态转移方程为 dp[i][j] = min(dp[i-1][j]+grid[i][j], dp[i][j-1]+grid[i][j])
// 将整个 dp[i][j] 表示路径和,初始化为 0
// 边界就是第一行和第一列,它们不适合状态转移方程
// 处理除第一行第一列以外的其它部分
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        int dp[m][n];

        dp[0][0] = grid[0][0];
        // 处理边界,第一行
        for(int j = 1; j < n; j++)
            dp[0][j] = dp[0][j-1] + grid[0][j];

        // 处理边界,第一列
        for(int i = 1; i < m; i++){
            dp[i][0] = dp[i-1][0] + grid[i][0];
        }

        // 处理其它位置
        for(int i = 1; i < m; i++)
            for(int j = 1; j < n; j++){
                dp[i][j] = min(dp[i-1][j] + grid[i][j], dp[i][j-1] + grid[i][j]);
            }


        return dp[m-1][n-1];
    }
};
