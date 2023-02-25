/*
The following algorithm generates the next permutation lexicographically after a given permutation. It changes the given permutation in-place.

1. Find the largest index k such that a[k] < a[k + 1]. If no such index exists, the permutation is the last permutation.
2. Find the largest index l greater than k such that a[k] < a[l].
3. Swap the value of a[k] with that of a[l].
4. Reverse the sequence from a[k + 1] up to and including the final element a[n].
*/
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int len = nums.size();
        int i = nums.size()-1;
        while(i > 0 && nums[i-1] >= nums[i]){
            --i;
        }
        if(i == 0){
            reverse(nums.begin(), nums.end());
            return;
        }
        int j = nums.size()-1;
        while(j > i-1 && nums[j] <= nums[i-1]){
            --j;
        }
        swap(nums[i-1], nums[j]);
        reverse(nums.begin()+i, nums.end());
        return;
    }
};

// 使用 C++ Algorithm 中的 next_permutation(begin, end) 可以求出内存位置 [start, end) 区间的下一个排列 (按照字典序)
// 最近疯狂喜欢 C++ 的库特性
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        if(!next_permutation(nums.begin(), nums.end()))
            sort(nums.begin(), nums.end());
    }
};
