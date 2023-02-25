#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 110, INF = 0x3f3f3f3f;
int w[N][N], f[N][N];
int n;

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            scanf("%d", &w[i][j]);
        }
    }
    // 特判第一行的状态计算
    for(int j = 1; j <= n; j++){
        f[1][j] = f[1][j-1] + w[1][j];
    }
    
    // 特判第一列的状态计算
    for(int i = 1; i <= n; i++){
        f[i][1] = f[i-1][1] + w[i][1];
    }
    
    // dp 计算其他情况
    for(int i = 2; i <= n; i++){
        for(int j = 2; j <= n; j++){
            f[i][j] = min(f[i][j-1], f[i-1][j]) + w[i][j];
        }
    }
    
    printf("%d\n", f[n][n]);
    
    return 0;
}
