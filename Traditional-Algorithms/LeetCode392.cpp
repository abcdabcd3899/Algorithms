// 经典的双指针问题，也就是说使用双指针算法一定能够找到一个匹配的解
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int lens = s.size();
        int lent = t.size();
        int i = 0, j = 0;
        while(i < lens && j < lent){
            if(s[i] == t[j]) i++;
            j++;
        }
        if(i == lens) return true;
        return false;
    }
};
