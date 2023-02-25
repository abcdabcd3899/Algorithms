// reservior sampling TLE 62/68
class Solution {
public:
    Solution(int n, vector<int>& blacklist) {
        this->n = n;
        for(auto u: blacklist){
            m[u] = true;
        }
    }
    
    int pick() {
        vector<int>res;
        for(int i = 0; i < n; ++i)
            if(m.find(i) == m.end()) res.push_back(i);
        
        // reservior sampling
        int count = 1;
        int ans = res[0];
        int len = res.size();
        for(int i = 1; i < len; ++i){
            count++;
            int rd = (rand() % count) + 1;
            if(rd == 1){
                ans = res[i];
            }
        }
        return ans;
    }
private:
    unordered_map<int, bool> m;
    int n;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(n, blacklist);
 * int param_1 = obj->pick();
 */
