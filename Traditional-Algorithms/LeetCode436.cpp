class Solution {
public:
    vector<int> findRightInterval(vector<vector<int>>& intervals) {
        vector<int>ans;
        map<int,int>m;
        for(int i = 0; i < intervals.size(); ++i){
            m[intervals[i][0]] = i;
        }
        for(auto &n : intervals){
            auto it = m.lower_bound(n[1]);  //对于每一个end，找到他的下一个最接近的start，lower_bound表示大于等于n[1]
            if(it == m.end()){
                ans.push_back(-1);
            }else{
                ans.push_back(it->second);
            }
        }
        return ans;
    }
};