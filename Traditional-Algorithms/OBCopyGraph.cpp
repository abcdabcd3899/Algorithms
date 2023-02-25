/**给定一个有向无环图，如何拷贝这个图

a -> b -> c
|    |
|--->d

e --> f


a' -> b' -> c'
|     |
|-->  d'
  
e' --> f'

struct Node 
{
	int64_t val_;   // 节点的标记
  
    Node *next_[64];  // 节点的出边
	int64_t cnt_;  // 有几条边
};

void copy_graph(Node *nodes[64], int64_t cnt, Node *new_nodes[64])
{

};
*/


#include <climits>
#include <vector>
#include "unordered_map"
#include "iostream"

using namespace std;

struct Node
{
    int64_t val_;   // 节点的标记

    Node *next_[64];  // 节点的出边
    int64_t cnt_;  // 有几条边

    Node();
    Node(int64_t val) {
        val_ = val;
        cnt_ = 0;
    }
};

Node* copy_graph(Node* node);

void copy_graph(Node *nodes[64], int64_t cnt, Node *new_nodes[64]) {
    Node* root = new Node(-1);
    for(int i = 0; i < cnt; ++i) {
        root->next_[i] = nodes[i];
    }
    Node* new_graph = copy_graph(root);
    // 如何将返回值填入new_nodes
}

unordered_map<Node*, Node*> map;

Node* copy_graph(Node* node) {
    if(node == nullptr) {
        return nullptr;
    }
    if(map[node] == nullptr) {
        Node* new_node = new Node(node->val_);
        map[node] = new_node;
        for(int i = 0; i < node->cnt_; ++i) {
            new_node->next_[i] = copy_graph(node->next_[i]);
            ++new_node->cnt_;
        }
    }
    return map[node];
}

void dfs(Node* node) {
    if(node == nullptr) {
        return;
    }
    cout << node->val_ << endl;
    for(int i = 0; i < node->cnt_; ++i) {
        dfs(node->next_[i]);
    }
}

int main() {
    Node* a = new Node(1);
    Node* b = new Node(2);
    Node* c = new Node(3);
    Node* d = new Node(4);
    Node* e = new Node(5);
    a->next_[0] = b;
    a->next_[1] = d;
    a->next_[2] = e;
    b->next_[0] = c;
    b->next_[1] = d;
    d->next_[0] = e;

    a->cnt_ = 3;
    b->cnt_ = 2;
    d->cnt_ = 1;

    dfs(a);
    Node* node = copy_graph(a);
    cout << "=======" << endl;
    dfs(node);
}

