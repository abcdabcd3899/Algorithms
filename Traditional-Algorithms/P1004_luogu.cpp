// https://www.luogu.com.cn/problem/P1004
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 20;
int w[N][N];
int f[N*2][N][N];  // f数组全局被初始化为0
int n;

int main(){
    scanf("%d", &n);
    // 处理输入
    int a, b, c;
    while(cin >> a >> b >> c) {
        if(!a && !b && !c) break;  // 如果a b c全部为0，则结束，这是题目中给出的结束条件
        w[a][b] = c;
    }
    
    // dp
    for(int k = 2; k <= n * 2; k++){
        for(int i1 = 1; i1 <= n; i1++){
            for(int i2 = 1; i2 <= n; i2++){
                int j1 = k - i1, j2 = k - i2;
                if(j1 >= 1 && j1 <= n && j2 >= 1 && j2 <= n){
                    int t = w[i1][j1];
                    if(i1 != i2) t += w[i2][j2];  // 如果重合，则i1 == i2 成立；其逆否命题（i1 != i2，则二者一定不重合）也成立。
                    f[k][i1][i2] = max(f[k][i1][i2], f[k-1][i1-1][i2-1] + t); // 最后一步都是从上往下走到
                    f[k][i1][i2] = max(f[k][i1][i2], f[k-1][i1-1][i2] + t); // 最后一步一个从上往下走，一个从左往右走
                    f[k][i1][i2] = max(f[k][i1][i2], f[k-1][i1][i2-1] + t); // 最后一步一个从左往右走，一个从上往下走
                    f[k][i1][i2] = max(f[k][i1][i2], f[k-1][i1][i2] + t); // 最后一步都是从左往右走
                }
            }
        }
    }
    cout << f[n*2][n][n] << endl;
    return 0;
}
