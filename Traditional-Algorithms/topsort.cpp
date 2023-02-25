#include <iostream>
#include <cstring>
using namespace std;

const int N = 1e5+10;
int h[N], e[N], ne[N], idx; // 链式前向星
int q[N], d[N]; //q为队列，d表示图中节点的入度集合
int n,m;

void add(int a , int b){
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

bool topsort(){
    int hh = 0, tt = -1;
    for(int i = 1; i <=n; i++){
        if(!d[i]){
            q[++tt] = i;   //如果这里需要将输出的结果序列按照某种次序排序，可以该用priority_queue来存储
        }
    }
    while(hh <= tt){
        int u = q[hh++];
        for(int i = h[u]; i != -1; i = ne[i]){
            int j = e[i];
            d[j]--;
            if(d[j] == 0){
                q[++tt] = j;
            }
        }
    }
    if(tt == n-1){
        return true;
    }else return false;
}

int main(){
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);  //初始化链式前向星
    while(m--){
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);
        d[b]++;
    }
    if(topsort()){
        for(int i = 0; i < n; i++){
            printf("%d ", q[i]);
        }
    }else printf("-1\n");
}

// 基于 BFS 的拓扑排序
// C++ 常规实现，采用临界表方式
#include<iostream>
#include <list>
#include <queue>
using namespace std;

/************************类声明************************/
class Graph
{
    int V;             // 顶点个数
    list<int> *adj;    // 邻接表
    queue<int> q;      // 维护一个入度为0的顶点的集合
    int* indegree;     // 记录每个顶点的入度
public:
    Graph(int V);                   // 构造函数
    ~Graph();                       // 析构函数
    void addEdge(int v, int w);     // 添加边
    bool topological_sort();        // 拓扑排序
};

/************************类定义************************/
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];

    indegree = new int[V];  // 入度全部初始化为0
    for(int i=0; i<V; ++i)
        indegree[i] = 0;
}

Graph::~Graph()
{
    delete [] adj;
    delete [] indegree;
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); 
    ++indegree[w];
}

bool Graph::topological_sort()
{
    for(int i=0; i<V; ++i)
        if(indegree[i] == 0)
            q.push(i);         // 将所有入度为0的顶点入队

    int count = 0;             // 计数，记录当前已经输出的顶点数 
    while(!q.empty())
    {
        int v = q.front();      // 从队列中取出一个顶点
        q.pop();

        cout << v << " ";      // 输出该顶点
        ++count;
        // 将所有v指向的顶点的入度减1，并将入度减为0的顶点入栈
        list<int>::iterator beg = adj[v].begin();
        for( ; beg!=adj[v].end(); ++beg)
            if(!(--indegree[*beg]))
                q.push(*beg);   // 若入度为0，则入栈
    }

    if(count < V)
        return false;           // 没有输出全部顶点，有向图中有回路
    else
        return true;            // 拓扑排序成功
}

int main()
{
    Graph g(6);   // 创建图
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    g.topological_sort();
    return 0;
}


// 基于 DFS 的 拓扑排序
// A C++ program to print topological sorting of a DAG 
#include <iostream> 
#include <list> 
#include <stack> 
using namespace std; 

class Graph 
{ 
	int V; 

	list<int> *adj; 


	void topologicalSortUtil(int v, bool visited[], stack<int> &Stack); 
public: 
	Graph(int V); 
	void addEdge(int v, int w); 

	
	void topologicalSort(); 
}; 

Graph::Graph(int V) 
{ 
	this->V = V; 
	adj = new list<int>[V]; 
} 

void Graph::addEdge(int v, int w) 
{ 
	adj[v].push_back(w);  
} 
 
void Graph::topologicalSortUtil(int v, bool visited[], 
								stack<int> &Stack) 
{ 
	
	visited[v] = true; 

	list<int>::iterator i; 
	for (i = adj[v].begin(); i != adj[v].end(); ++i) 
		if (!visited[*i]) 
			topologicalSortUtil(*i, visited, Stack); 

	Stack.push(v); 
} 


void Graph::topologicalSort() 
{ 
	stack<int> Stack; 

	// Mark all the vertices as not visited 
	bool *visited = new bool[V]; 
	for (int i = 0; i < V; i++) 
		visited[i] = false; 
 
	for (int i = 0; i < V; i++) 
	if (visited[i] == false) 
		topologicalSortUtil(i, visited, Stack); 

	
	while (Stack.empty() == false) 
	{ 
		cout << Stack.top() << " "; 
		Stack.pop(); 
	} 
} 

 
int main() 
{ 
	
	int n,v1,v2;
	cin>>n;
	Graph g(n); 
	for(int i=1;i<=n;i++)
    {	cin>>v1>>v2;
	g.addEdge(v1, v2);} 
	

	cout << " Topological Sort of the given graph \n"; 
	g.topologicalSort(); 

	return 0; 
}
