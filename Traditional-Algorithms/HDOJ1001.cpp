#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
int main(int agrc, char *agrv[]){
	string s;  //����ÿ������
	while (true){
		vector<int> v;
		while (getline(cin, s)){
			if (!s.empty()){
				int sum = 0;
				int a = 0;
				stringstream ss(s);
				while (ss >> a){
					for (int i = 0; i <= a; i++){
						sum += i;
					}
				}
				v.push_back(sum);
			}//if����
			else{
				//˵����ʱ�����Ѿ�������ϣ���Ҫ������
				for (int i = 0; i < v.size(); i++){
					cout << v[i] << endl;
					if (i != v.size() - 1){
						cout << endl;
					}
				}//for
				break;
			}
		}
	}
	
	system("pause"); 
	return 0;
}