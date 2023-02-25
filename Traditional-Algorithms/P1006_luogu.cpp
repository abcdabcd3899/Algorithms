// https://www.luogu.com.cn/problem/P1006
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 50+10;
int m, n;
int w[N][N];
int f[N*2][N][N];

int main(){
    scanf("%d%d", &m, &n);
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            scanf("%d", &w[i][j]);
        }
    }
    // 下面代码和方格取数完全相同
    for(int k = 2; k <= n+m; k++){
        for(int i1 = 1; i1 <= m; i1++){
            for(int i2 = 1; i2 <= m; i2++){
                int j1 = k - i1, j2 = k - i2;
                if(j1 >= 1 && j1 <= n && j2 >= 1 && j2 <= n){
                    int t = w[i1][j1];
                    if(i1 != i2) t += w[i2][j2];
                    f[k][i1][i2] = max(f[k][i1][i2], f[k-1][i1-1][i2-1] + t);  // 下 下
                    f[k][i1][i2] = max(f[k][i1][i2], f[k-1][i1-1][i2] + t);  // 下 右
                    f[k][i1][i2] = max(f[k][i1][i2], f[k-1][i1][i2-1] + t);  // 右 下
                    f[k][i1][i2] = max(f[k][i1][i2], f[k-1][i1][i2] + t);// 右 右
                }
            }
        }
    }
    
    printf("%d\n", f[n + m][m][m]);
    return 0;
}
