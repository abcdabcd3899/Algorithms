#include <iostream>
#include <sstream>
#include <string>
using namespace std;
int main1(int argv, char *argc[]){
	string s;
	int a = 0;
	while (getline(cin, s)){
		stringstream ss(s);
		int sum = 0;
		while (ss >> a){
			sum += a;
		}
		cout << sum << endl;
	}
	return 0;
}
