class Solution {
public:
    Solution(vector<int>& nums) {
        res.assign(nums.begin(), nums.end());
    }
    
    int pick(int target) {
        int ans;
        int len = res.size();
        int count = 1;
        // puts number into reservior
        for(int i = 0; i < len; i++){
            if(target == res[i]){
                ans = i;
                break;
            }
        }
        
        // sampling
        for(int i = ans+1; i < len; ++i){
            count++;
            int rd = rand() % count + 1;
            if(rd == 1 && target == res[i])
                ans = i;
        }
        
        return ans;
    }
private:
    vector<int>res;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * int param_1 = obj->pick(target);
 */
