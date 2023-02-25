//快速排序，该版本的代码在partition部分很清晰，能够被用在find kth element问题求解中，见LeetCode215.cpp
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        quicksort(nums,0 , nums.size()-1);
        return nums;
    }
    int partition(vector<int>& nums, int left, int right){
        int key = nums[left];
        while(left < right){
            while(left < right && nums[right] >= key){
                right--;
            }
            if(left < right){
                nums[left] = nums[right];
                left++;
            }
            while(left < right && nums[left] < key){
                left++;
            }
            if(left < right){
                nums[right] = nums[left];
            }
        }
        nums[left] = key;
        return left;
    }
    void quicksort(vector<int>& nums, int left, int right){
		if (left >= right) return;
		int p = partition(nums, left, right);
		quicksort(nums, left, p-1);
		quicksort(nums, p+1, right);
    }
};

//很简练的快排模板
#include <bits/stdc++.h>
using namespace std;

void quicksort(vector<int>& nums, int left, int right){
    if(left >= right) return;
    int i = left - 1;
    int j = right + 1;
    int pivot = nums[left + right + 1 >> 1];
    while(i < j){
        do ++i; while(nums[i] < pivot);
        do --j; while(nums[j] > pivot);
        if(i < j) swap(nums[i], nums[j]);
    }
    quicksort(nums, left, i-1);
    quicksort(nums, i, right);
}

int main(){
    int n;
    scanf("%d", &n);
    vector<int>nums(n);
    int tmp;
    for(int i = 0; i < n; i++){
        scanf("%d", &nums[i]);
    }
    quicksort(nums, 0 , n-1);
    for(int i = 0; i< n; i++){
        printf("%d ", nums[i]);
    }
    return 0;
}

//堆排序
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        priority_queue<int, vector<int>, greater<int>>q;
        int len = nums.size();
        for(int i = 0; i < len; i++){
            q.push(nums[i]);
        }
        nums.clear();
        while(!q.empty()){
            int tmp = q.top();
            nums.push_back(tmp);
            q.pop();
        }
        return nums;
    }
};

//merge sort  AC 速度不如快排，快排内存排序之王。
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        mergesort(nums, 0 , nums.size()-1);
        return nums;
    }
    
    void mergesort(vector<int>& nums, int l, int r){
        if(l >= r) return;
        int mid = l + r >> 1;
        mergesort(nums, l, mid), mergesort(nums, mid+1, r);
        int i = l, j = mid+1, k = 0;
        vector<int>ans(r-l+1);   //这里如果ans(nums.size()) 代码通不过，特别注意
        while(i <= mid && j <= r){
            if(nums[i] <= nums[j]){
                ans[k++] = nums[i++];
            }else
                ans[k++] = nums[j++];
        }
        while(i <= mid){
            ans[k++] = nums[i++];
        }
        while(j <= r){
            ans[k++] = nums[j++];
        }
        for(int i = l, j = 0; i <= r; i++, j++){
            nums[i] = ans[j];
        }    
    }
};

//堆排序
class Solution {
private:
    vector<int>nums;
    int n;
public:
    vector<int> sortArray(vector<int>& _nums) {
        nums = _nums;
        n = nums.size();
        for(int i = n/2-1; i >= 0; i--){
            down(i);
        }
        int len = n;
        vector<int>ans;
        while(n--){
            ans.push_back(nums[0]);
            nums[0] = nums[len-1];
            len--;
            down(0);
        }
        return ans;
    }
    void down(int u){
        int min = u;
        if(u * 2+1 < n && nums[u * 2+1] < nums[min]) min = u * 2+1;
        if(u * 2 + 2 < n && nums[u * 2+2] < nums[min]) min = u * 2 +2;
        if(u != min){
            swap(nums[u], nums[min]);
            down(min);
        }
    }
	
	void up(int u){  //循环的方法写
		while(u / 2 >= 1 && h[u/2] > h[u]]){
			swap(h[u/2], h[u]);
			u /= 2;
		}
	}
	void up(int u){  //递归方法写
		if(u / 2 >= 1 && h[u/2] > h[u]]){
			swap(h[u/2], h[u]);
			u /= 2;
			up(u);
		}
	}
	
	
};

//堆排序
class Solution {
private:
    static const int N = 1e5+10;
    int h[N], len;  //全局变量
public:
    vector<int> sortArray(vector<int>& nums) {
        for(int i = 1; i <= nums.size(); i++){
            h[i] = nums[i-1];
        }
        len = nums.size();
        
        //调整h数组，使之成为一个heap
        for(int i = nums.size()/2; i >=1; i--){
            down(i);
        }
        
        vector<int>ans;
        int n  = len;
        while(n--){
            ans.push_back(h[1]);
            h[1] = h[len];
            len--;
            down(1);
        }
        
        return ans;
        
    }
    void down(int u){
        int min = u;  //min看成是最小位置的坐标
        if(u * 2 <= len && h[u * 2] < h[min]) min = u * 2;
        if(u * 2 + 1 <= len && h[u * 2 + 1] < h[min]) min = u * 2 + 1;
        if(u != min){
            swap(h[u], h[min]);
            down(min);
        }
    }
};

// 冒泡排序 Time Limit Exceeded
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        int len = nums.size();
        for(int i = 0; i < len - 1; ++i)
            for(int j = 0; j < len - 1 - i; ++j)
                if(nums[j] > nums[j+1]) swap(nums[j], nums[j+1]);
        return nums;
    }
};

// 插入排序 Time Limit Exceeded
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        int len = nums.size();
        for(int i = 1; i < len; ++i){
            int key = nums[i];
            int j = i - 1;
            while(j >= 0 && nums[j] > key){
                nums[j+1] = nums[j];
                --j;
            }
            nums[j+1] = key;
        }
        return nums;
    }
};

// 选择排序 Time Limit Exceeded
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        int len = nums.size();
        for(int i = 0; i < len - 1; ++i){
            int min = i;
            for(int j = i + 1; j < len; ++j)
                if(nums[j] < nums[min])
                    min = j;
            swap(nums[i], nums[min]);
        }
        return nums;
    }
};

// 希尔排序 希尔排序不适合使用链表作为底层数据结构，因此不能用到 https://leetcode.com/problems/sort-list/ 中
// 链表不能使用 shell 排序的原因是 shell 排序需要数据结构支持很强的随机访问特性
// AC
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        int gap, i, j, tmp;
        int len = nums.size();
        for(gap = len >> 1; gap > 0; gap >>= 1){
            for(i = gap; i < len; ++i){  // i 和 j 循环这里是经典的插入排序
                tmp = nums[i];
                for(j = i - gap; j >= 0 && nums[j] > tmp; j -= gap)
                    swap(nums[j+gap], nums[j]);
                nums[j+gap] = tmp;
            }       
        }
        return nums;
    }
};
