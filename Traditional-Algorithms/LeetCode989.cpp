class Solution {
public:
    vector<int> addToArrayForm(vector<int>& A, int K) {
        reverse(A.begin(), A.end());
        vector<int>B;
        while(K > 0){
            B.push_back(K%10);
            K /= 10;
        }
        auto C = add(A, B);
        reverse(C.begin(), C.end());
        return C;
    }
    
    vector<int> add(vector<int>& A, vector<int>& B){
        vector<int> C;
        int t = 0;
        for(int i = 0; i < A.size() || i < B.size(); i++){
            if(i < A.size()) t += A[i];
            if(i < B.size()) t += B[i];
            C.push_back(t%10);
            t /= 10;
        }
        if(t) C.push_back(1);
        return C;
    }

};