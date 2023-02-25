//hash table
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        unordered_map<int,int> m;
        int len = nums.size();
        for(int i = 0 ; i< len;i++){
            if(m.find(nums[i]) != m.end()){
                m[nums[i]] = m[nums[i]]+1;
            }else{
                m[nums[i]] = 1;
            }
        }
        int ans ;
        for(auto &n : m){
            if(n.second != 1){
                ans = n.first;
            }
        }
        return ans;
    }
};


//二分，抽屉原理
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int len = nums.size();
        int left = 1; 
        int right = len-1;   
        while(left < right){
            int mid = left + (right - left)/2;
            int count = 0;
            for(auto & n : nums){
                if(n >= left && n <= mid){
                    count++;
                }
            }
            
            if(count > mid-left+1){
                right = mid;
            }else{
                left = mid+1;
            }
        }
        return left;
    }
};

//cyclic sort
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int len = nums.size();
        int i = 0;
        while(i < len){
            int j = nums[i];
            if(j < len && nums[i] != nums[j-1]){
                swap(nums[i], nums[j-1]);
            }else{
                ++i;
            }
        }
        int ans = -1;
        for(int i = 0; i < len; i++){
            if(nums[i] != i+1){
                ans = i;
                break;
            }
        }
        return nums[ans];
    }
};

//快慢指针
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int len = nums.size();
        int slow = nums[0] ;
        int fast = nums[0];
        while(true){
            slow = nums[slow];
            fast = nums[nums[fast]];
            if(slow == fast){
                fast = nums[0];
                while(slow != fast){
                    slow = nums[slow];
                    fast = nums[fast];
                }
                return slow;
            }
        }
        return -1;
    }
};

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        vector<int> ans(nums.size());
        for(int i = 0 ; i < nums.size(); i++){
            ans[nums[i]] += 1;
        }
        for(int i = 0 ; i < nums.size(); i++){
            if(ans[i] > 1){
                return i;
            }
        }
        return -1;
    }
};


//counting sort
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        vector<int> ans(nums.size());
        for(int i = 0 ; i < nums.size(); i++){
            ans[nums[i]] += 1;
        }
        vector<int>res;
        for(int i = 0 ; i < ans.size(); i++){
            if(ans[i] > 0){
                int count = ans[i];
                while(count > 0){
                    res.push_back(i);
                    count--;
                }
            }
        }
        for(int i = 0 ; i < res.size(); i++){
            cout << res[i] << " ";  //count sortde 结果
        }
        for(int i = 0 ; i < nums.size(); i++){
            if(ans[i] > 1){
                return i;
            }
        }
        return -1;
    }
};

// 使用 bloom filter，同时使用 count 标记为，count 的值只能为 0 或 1
// 如果 count == 1 表示该数字还没出现过，count = 0 表示该数字已出现过
// 将 count = 0 所在的 nums[i] 输出即可
class Solution {
public:
    int hashes = 5;
    static const int size = 1e7;
    int primes[10] = {31, 37, 41, 43, 47, 53, 59, 61, 67, 71}; // 常用素数集合
public:
    int findDuplicate(vector<int>& nums) {
        bool bitMap[size] = {false};
        int len = nums.size();
        for(int i = 0; i < len; ++i){
            int count = 0;
            long long int hash = 0;   // 这里使用 long long int 否则会出现 int 越界
            for(int h = 0; h < hashes; ++h){
                string s = to_string(nums[i]);
                for(int c = 0; c < s.size(); ++c){
                    hash = primes[h] * hash + s.at(c) - '0';
                }
                hash = hash % size;
                if(hash < 0)
                    hash = (size + hash) % size;
                if(!bitMap[hash])
                    count++;
                bitMap[hash] = true;
            }
            if(count == 0)
                return nums[i];
        }
        return -1;
    }
};
