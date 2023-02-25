// 逆波兰表达式求值
class Solution {
public:
    bool cmp(string s1, string s2){
        if(s1.compare(s2) == 0)
            return true;
        return false;
    }
    int evalRPN(vector<string>& tokens) {
        stack<int>st;
        for(string &s: tokens){
            if(cmp(s, "+") || cmp(s, "-") || cmp(s, "*") || cmp(s, "/")){
                // 如果是操作符，则弹出元素，并将计算后的结果重新压入栈中
                int right = st.top();  // right 表示右操作数
                st.pop();
                int left = st.top(); // 表示左操作数
                st.pop();
                char c = s[0]; //取出操作符
                switch(c){
                    case '+':
                        st.push(left + right);
                        break;
                    case '-':
                        st.push(left - right);
                        break;
                    case '*':
                        st.push(left * right);
                        break;
                    case '/':
                        st.push(left / right);
                        break;
                }
            }else{
                // 说明它为数字，直接压入栈中
                st.push(stoi(s));
            }
        }
        return st.top();
    }
};
