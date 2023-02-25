class Solution {
public:
    int divide(int x, int y) {
        bool sig = false;
        if((x > 0 && y < 0) || (x < 0 && y > 0)) sig = true;
        typedef long long LL;
        vector<LL> exp;
        LL a = abs(LL(x)), b = abs(LL(y));
        for(LL i = b; i <= a; i = i + i){
            exp.push_back(i);
        }
        LL res = 0;
        for(int i = exp.size()-1; i >= 0; i--){
            if(a >= exp[i]){
                a -= exp[i];
                res += 1ll << i;      
            }
        }
        if(sig) res = -res;
        if(res > INT_MAX || res < INT_MIN) return INT_MAX;
        return res;
    }
};

// 更好的解决方法
class Solution {
public:
    int divide(int dividend, int divisor) {
        if (dividend == INT_MIN && divisor == -1) {
            return INT_MAX;
        }
        long dvd = labs(dividend), dvs = labs(divisor), ans = 0;
        int sign = dividend > 0 ^ divisor > 0 ? -1 : 1;
        while (dvd >= dvs) {
            long temp = dvs, m = 1;
            while (temp << 1 <= dvd) {
                temp <<= 1;
                m <<= 1;
            }
            dvd -= temp;
            ans += m;
        }
        return sign * ans;
    }
};

// 高效位运算 
class Solution {
public:
    int divide(int dividend, int divisor) {
        if((dividend == INT_MIN? 1:0) & (divisor == -1? 1:0))
            return INT_MAX;
        long dvd = labs(dividend), dvs = labs(divisor), ans = 0;
        int sign = dividend > 0 ^ divisor > 0 ? -1 : 1;
        while (dvd >= dvs) {
            long temp = dvs, m = 1;
            while (temp << 1 <= dvd) {
                temp <<= 1;
                m <<= 1;
            }
            dvd -= temp;
            ans += m;
        }
        return sign * ans;
    }
};
