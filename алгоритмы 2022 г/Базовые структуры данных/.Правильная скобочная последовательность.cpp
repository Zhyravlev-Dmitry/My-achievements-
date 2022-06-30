#include <iostream>
#include <stack>

int main() {
    std::stack<char> st;
    std::string str;
    std::cin >> str;
    bool f = 1;
    for (int i = 0; i < str.size(); i++) {
        char symbol = str[i];
        if (symbol == '{' || symbol == '(' || symbol == '[')
            st.push(symbol);
        else {
            if (!st.empty() && (abs(st.top() - symbol) <= 2))
                st.pop();
            else {
                f = 0;
                break;
            }
        }
    }
    if (f && (st.empty()))
        std::cout << "yes";
    else
        std::cout << "no";
    return 0;
}
