#include <iostream>
#include <vector>
using std::cin;

int bp(std::vector<int> &A, std::vector<int> &B) {
    int l = 0;
    int r = A.size() - 1;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (B[m] - A[m] >= 0) {
            l = m;
        } else {
            r = m;
        }
    }
    if (std::max(A[l], B[l]) <= std::max(A[r], B[r])) {
        return l + 1;
    } else {
        return  r + 1;
    }
}
int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, l;
    cin >> n >> m >> l;
    std::vector<std::vector<int>> A;
    std::vector<std::vector<int>> B;
    for (int i = 0; i < n; i++) {
        std::vector<int> new_A;
        for (int j = 0; j < l; j++) {
            int a;
            cin >> a;
            new_A.push_back(a);
        }
        A.push_back(new_A);
    }
    for (int i = 0; i < m; i++) {
        std::vector<int> new_B;
        for (int j = 0; j < l; j++) {
            int b;
            cin >> b;
            new_B.push_back(b);
        }
        B.push_back(new_B);
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        std::cout << bp(A[a-1], B[b-1]) << "\n";
    }
    return 0;
}