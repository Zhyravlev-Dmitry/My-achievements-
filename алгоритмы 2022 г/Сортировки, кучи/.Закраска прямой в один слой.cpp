#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  std::vector<std::pair<int, int>> data;
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    int in;
    std::cin >> in;
    data.push_back(std::make_pair(in, 1)); // 1 - open
    std::cin >> in;
    data.push_back(std::make_pair(in, 0));
  }
  std::sort(data.begin(), data.end());
  int previous = 0;
  int open = 0;
  int sum = 0;
  for (int i = 0; i < 2 * n; ++i) {
    if (open == 1) {
      sum += data[i].first - previous;
    }
    previous = data[i].first;
    if (data[i].second) {
      open += 1;
    } else {
      open -= 1;
    }
  }
  std::cout << sum;
  return 0;
}