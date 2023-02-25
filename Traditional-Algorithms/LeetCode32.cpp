class Solution {
public:
    int longestValidParentheses(string s) {
        int len = s.size();
        int longest = 0;
        stack<int>st;
        for(int i = 0; i < len; ++i){
            if(s[i] == '(') st.push(i);
            else{
                // 说明此时一定是 )
                if(!st.empty()){
                    if(s[st.top()] == '(')
                        st.pop();
                    else 
                        st.push(i);
                }
                else{
                    // 说明栈是空的，只能 push
                    st.push(i);
                }
            }
        }
           
        if(st.empty()) longest = len;
        else{
            // 说明栈内有元素
            int a = len, b = 0;
            while(!st.empty()){
                b = st.top();
                st.pop();
                longest = max(longest, a-b-1);
                a = b;
            }
            longest = max(longest, a);
        }
        return longest;
    }
};
