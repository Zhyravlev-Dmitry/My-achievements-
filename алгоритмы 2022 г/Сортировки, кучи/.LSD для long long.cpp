#include <iostream>
#include <vector>
#include <cmath>
 
void LsdSort(std::vector<long long int>& data, int byte) {
  std::vector<int> counting(65536, 0);
  for (long long int i: data) {
    long long int value = i / static_cast<long long int>(std::pow(65536, byte - 1)) % 65536;
    counting[value] += 1;
  }
  for (int i = 1; i < counting.size(); ++i) {
    counting[i] += counting[i - 1];
  }
  std::vector<long long int> answer(data.size());
  for (int i = static_cast<int>(data.size()) - 1; i >= 0; --i) {
    long long int value = data[i] / static_cast<long long int>(std::pow(65536, byte - 1)) % 65536;
    answer[--counting[value]] = data[i];
  }
  for (int i = 0; i < data.size(); ++i) {
    data[i] = answer[i];
  }
}
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int quantity;
  std::cin >> quantity;
  std::vector<long long int> data;
  for (int i = 0; i < quantity; ++i) {
    long long int value;
    std::cin >> value;
    data.push_back(value);
  }
  for (int byte = 1; byte <= 4; ++byte) {
    LsdSort(data, byte);
  }
  for (long long int i: data) {
    std::cout << i << " ";
  }
  return 0;
}