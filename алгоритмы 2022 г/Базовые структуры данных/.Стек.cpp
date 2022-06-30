#include <iostream>
#include <string>

using std::cin;
using std::cout;

int size = 0;
struct node {
    int val;
    node* prev;
};
void push(node* &stack, int n) {
    node* new_node = new node;
    new_node -> val = n;
    new_node -> prev = stack -> prev;
    size++;
    stack -> prev = new_node;
    cout << "ok" << "\n";
}
void pop(node* &stack) {
    if (stack -> prev) {
        cout << stack -> prev -> val << "\n";
        node* intermediary = stack -> prev -> prev;
        delete stack -> prev;
        stack -> prev = intermediary;
        size--;
    } else {
        cout << "error" << "\n";
    }
}
void back(node* &stack) {
    if (stack -> prev) {
        cout << stack -> prev -> val << "\n";
    } else {
        cout << "error" << "\n";
    }
}
void clear(node* &stack) {
    while (stack -> prev) {
        node* intermediary = stack -> prev -> prev;
        delete stack -> prev;
        stack -> prev = intermediary;
        size--;
    }
    cout << "ok\n";
}
int main() {
    node* stack = new node;
    stack -> prev = nullptr;
    std::string str;
    cin >> str;
    while (str != "exit") {
        if (str == "pop") {
            pop(stack);
        }  else if (str == "back") {
            back(stack);
        } else if (str == "size") {
            cout << size << "\n";
        } else if (str == "clear") {
            clear(stack);
        } else {
            int n;
            cin >> n;
            push(stack, n);
        }
        cin >> str;
    }
    cout << "bye";
    return 0;
}