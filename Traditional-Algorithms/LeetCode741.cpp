// 方格取数 双路径DP
// 这道题目下标从 0 开始，下标从 1 开始只能通过 51/59 个测试用例
// 实际上 “方格取数” 和 “传纸条” 其数组的下标都是从 1 开始 “行和列编号从 1 开始。”，而本题的下标从 0 开始。
// 该段代码应该是 LeetCode 741 最简洁的实现，也是最接近于“方格取数” 和 “传纸条” 的实现。
class Solution {
    static const int N = 60, INF= 0x3f3f3f3f;
    int f[N*2][N][N];
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size();
        
        // 初始化状态数组
        for(int k = 1; k <= n * 2 - 2; k++){
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    f[k][i][j] = -INF;
                }
            }
        }
        f[0][0][0] = grid[0][0];
        // 方格取数
        for(int k = 1; k <= n * 2 - 2; k++){
            for(int i1 = 0; i1 < n; i1++){
                for(int i2 = 0; i2 < n; i2++){
                    int j1 = k - i1, j2 = k - i2;
                    if(j1 < 0 || j1 >= n || j2 < 0 || j2 >= n) continue;
                    if(grid[i1][j1] == -1 || grid[i2][j2] == -1) continue;  // 遇到障碍物
                    int t = grid[i1][j1];
                    if(i1 != i2) t += grid[i2][j2];
                    if(i1 && i2) f[k][i1][i2] = max(f[k][i1][i2], f[k-1][i1-1][i2-1]+t); 
                    if(i1) f[k][i1][i2] = max(f[k][i1][i2], f[k-1][i1-1][i2]+t);
                    if(i2) f[k][i1][i2] = max(f[k][i1][i2], f[k-1][i1][i2-1]+t);
                    f[k][i1][i2] = max(f[k][i1][i2], f[k-1][i1][i2]+t);
                }
            }
        }
        return max(0, f[n*2 - 2][n-1][n-1]);
    }
};
