// 1. 进制回文数判断
#include <iostream>
#include <stack>
using namespace std;

int N;

bool inspect(int N, int r){
	int len = 0;
	stack<int> s;
	int ans[100010];
	while(N != 0){
		ans[len] = N % r;
		len++;
		N = N / r;
	}
	// 将一半数字压进去
	for(int i = 0; i < len / 2; ++i){
		s.push(ans[i]);
	}
	bool ok = true;
	int a;
	if(len % 2 == 0) a = len / 2;
	else a = len / 2 + 1;
	for(int i = a; i < len; ++i){
		if(s.top() != ans[i]){
			ok = false;
			break;
		}else
			s.pop();
	}
	if(ok) return true;  // 说明这个数字是 回文数
	return false;
}

int main(){
	cin >> N;
	for(int r = 2; r <= 16; ++r){
		if(inspect(N, r)) cout << r << endl;
	}
	return 0;
}
