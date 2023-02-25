// 动态规划解决数字三角形问题
// 最小值状态转移： f[i][j] = min(f[i-1][j-1] + a[i][j], f[i-1][j] + a[i][j])
class Solution {
     static const int INF = 0x3f3f3f3f;
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        const int n = triangle.size();  // 计算出数字三角形总共包含多少行总共有多少行
        int f[n+1][n+2];   // 这里表示每一行要多两个状态，边界处理复杂
        
        for(int i = 0; i <= n; i++){
            for(int j = 0; j <= i+1; j++){
                f[i][j] = INF;
            }
        }
  
        f[1][1] = triangle[0][0];
        
        // dp过程
        for(int i = 2; i <= n; i++){ // 状态从第3行开始算，第一行之有一个数字
            for(int j = 1; j <= i; j++){
              f[i][j] = min(f[i-1][j-1] + triangle[i-1][j-1], f[i-1][j] + triangle[i-1][j-1]);
            }
        }
        
        // 遍历最后一行找到最小值
        int res = INF;
        for(int i = 1; i <= n; i++) res = min(res, f[n][i]);
        return res;
    }
};
