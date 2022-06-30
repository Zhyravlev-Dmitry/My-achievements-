#include <iostream>
#include <vector>

struct Pair {
  long long value;
  long long index;
};

long long FirstSmaller(const std::vector<Pair>& sequence, long long value) {
  long long left = 0;
  long long right = sequence.size() - 1;
  while (right - left > 1) {
    long long middle = (right + left) / 2;
    if (sequence[middle].value < value) {
      right = middle;
    } else {
      left = middle;
    }
  }
  return right;
}

void Recovery(const std::vector<long long>& prev, long long start_index, std::vector<long long>& indexes) {
  if(start_index != -1) {
    indexes.push_back(start_index);
    Recovery(prev, prev[start_index], indexes);
  }
}

void Recovery(const std::vector<long long>& prev, long long start_index) {
  std::vector<long long> indexes;
  Recovery(prev, start_index, indexes);
  for (int i = static_cast<long long>(indexes.size()) - 1; i >= 0; --i) {
    std::cout << indexes[i] + 1 << " ";
  }
}

int main() {
  const long long inf = 1'000'000'000'000'000;
  long long quantity;
  std::vector<long long> sequence;
  std::cin >> quantity;
  for (int i = 0; i < quantity; ++i) {
    long long value;
    std::cin >> value;
    sequence.push_back(value);
  }

  std::vector<Pair> dp(quantity + 1);
  std::vector<long long> prev(quantity + 1);
  std::vector<long long> parent(quantity);
  dp[0].value = inf;
  dp[0].index = -1;
  for (int i = 1; i <= quantity; ++i) {
    dp[i].value = -inf;
  }
  long long length = 0;
  for (int i = 0; i < sequence.size(); ++i) {
    long long smaller_index = FirstSmaller(dp, sequence[i]);
    if (dp[smaller_index].value == -inf) {
      length += 1;
    }
    dp[smaller_index].value = sequence[i];
    dp[smaller_index].index = i;
    prev[i] = dp[smaller_index - 1].index;
  }

  std::cout << length << "\n";
  Recovery(prev, dp[length].index);

  return 0;
}