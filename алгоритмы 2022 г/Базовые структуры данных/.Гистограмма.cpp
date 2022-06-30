#include <iostream>
#include <stack>
#include <vector>

using std::cin;

struct tride {
    long long int content;
    int min_left;
    int min_right;
};

int main() {
    cin.sync_with_stdio(0);
    int quantity;
    cin >> quantity;
    std::vector<tride> data(quantity);
    for (int i = 0; i < quantity; i++) {
        long long int element;
        cin >> element;
        data[i] = {element, 0, 0};
    }
    std::stack<int> min_left_index;
    for (int i = 0; i < quantity; i++) {
        while (!min_left_index.empty() && data[min_left_index.top()].content >= data[i].content) {
            min_left_index.pop();
        }
        if (min_left_index.empty()) {
            data[i].min_left = -1;
        } else {
            data[i].min_left = min_left_index.top();
        }
        min_left_index.push(i);
    }
    std::stack<int> min_right_index;
    long long int max = 0;
    for (int i = quantity - 1; i >= 0; i--) {
        while (!min_right_index.empty() && data[min_right_index.top()].content >= data[i].content) {
            min_right_index.pop();
        }
        if (min_right_index.empty()) {
            data[i].min_right = quantity;
        } else {
            data[i].min_right = min_right_index.top();
        }
        min_right_index.push(i);
        long long int if_max = (data[i].min_right - data[i].min_left - 1) * data[i].content;
        if (if_max > max) {
            max = if_max;
        }
    }
    std::cout << max;
    return 0;
}