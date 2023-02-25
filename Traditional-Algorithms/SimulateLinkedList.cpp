/**
实现一个单链表，链表初始为空，支持三种操作：
(1) 向链表头插入一个数；
(2) 删除第k个插入的数后面的数；
(3) 在第k个插入的数后插入一个数
现在要对该链表进行M次操作，进行完所有操作后，从头到尾输出整个链表。
注意:题目中第k个插入的数并不是指当前链表的第k个数。例如操作过程中一共插入了n个数，则按照插入的时间顺序，这n个数依次为：第1个插入的数，第2个插入的数，…第n个插入的数。
输入格式
第一行包含整数M，表示操作次数。
接下来M行，每行包含一个操作命令，操作命令可能为以下几种：
(1) “H x”，表示向链表头插入一个数x。
(2) “D k”，表示删除第k个输入的数后面的数（当k为0时，表示删除头结点）。
(3) “I k x”，表示在第k个输入的数后面插入一个数x（此操作中k均大于0）。
输出格式
共一行，将整个链表从头到尾输出。
数据范围
1≤M≤100000
所有操作保证合法。
输入样例：
10
H 9
I 1 1
D 1
D 0
H 6
I 3 6
I 4 5
I 4 5
I 3 4
D 6
输出样例：
6 4 6 5
*/

#include <iostream>
using namespace std;

const int N = 1e5+10;
int e[N], ne[N], head, idx;

void init(){
    head = -1;  //头结点
    idx = 0;   //待插入位置
}

//在头结点之后插入新的点
void add_to_head(int x){
    e[idx] = x;
    ne[idx] = head;
    head = idx;
    idx++;
}

//在K位置之后插入一个新的点
void add(int k, int x){
    e[idx] = x;
    ne[idx] = ne[k];
    ne[k] = idx;
    idx++;
}

//删除k位置之后的点
void del(int k){
    ne[k] = ne[ne[k]];
}

int main(){
    int n;
    scanf("%d", &n);
    init();
    while(n--){
        char c;
        int k ,x;
        scanf(" %c", &c);   //输入字符时，一定要在%c前面加空格，跳过空格
        if(c == 'H'){
            scanf("%d", &x);
            add_to_head(x);
        }else if (c == 'I'){
            scanf("%d%d", &k, &x);
            add(k-1,x);
        }else if(c == 'D'){
            scanf("%d", &k);
            if(!k) head = ne[head];
            else del(k-1);
        }
    }
    for(int i=head;i!=-1;i=ne[i])
      cout<<e[i]<<" ";
    return 0;
}