//解法一： Time limited min_heap
struct queue_node{
    vector<int> node;
    double fraction;
    queue_node(vector<int>& a , double f): node(a), fraction(f){};
};

struct cmp{
    bool operator()(queue_node* a, queue_node*b){
        return a->fraction > b->fraction;   //min_heap
    }
};

class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& A, int K) {
        int len = A.size();
        priority_queue<queue_node*, vector<queue_node*>, cmp> q;
        sort(A.begin(), A.end());
        for(int i = 0 ; i < len-1; i++){
            for(int j = i+1; j < len; j++){
                vector<int> tmp;
                tmp.push_back(A[i]);
                tmp.push_back(A[j]);
                double frac = double(A[i])/double(A[j]);
                queue_node * q_node = new queue_node(tmp,frac);
                q.push(q_node);
            }
            
        }
        
        vector<int> ans;
        while(K > 0){
            ans = q.top()->node;
            q.pop();
            K--;
        }
        return ans;
    }
};


struct queue_node{
    vector<int> node;
    double fraction;
    queue_node(vector<int>& a , double f): node(a), fraction(f){};
};

struct cmp{
    bool operator()(queue_node* a, queue_node*b){
        //return a->fraction > b->fraction;   //min_heap
        return a->fraction < b->fraction;  //max_heap
    }
};


//解法二 time limited max_heap 53 / 62 test cases passed.
class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& A, int K) {
        int len = A.size();
        priority_queue<queue_node*, vector<queue_node*>, cmp> q;
        int count = 0 ;
        for(int i = 0 ; i < len; i++){
            for(int j = i+1; j < len; j++){
                vector<int> tmp;
                tmp.push_back(A[i]);
                tmp.push_back(A[j]);
                double frac = double(A[i])/double(A[j]);
                if (count < K){ 
                    queue_node * q_node = new queue_node(tmp,frac);
                    q.push(q_node);
                }else{
                    if(frac < q.top()->fraction){
                        q.pop();
                        queue_node * q_node = new queue_node(tmp,frac);
                        q.push(q_node);       
                    }
                }
                count++;
            }
        }
        
        vector<int> ans;
        ans = q.top()->node;
        return ans;
    }
};