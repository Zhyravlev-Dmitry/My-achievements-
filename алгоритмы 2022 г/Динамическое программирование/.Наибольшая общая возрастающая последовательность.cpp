#include <iostream>
#include <vector>

long long LcisSize(std::vector<long long>& first, std::vector<long long>& second) {
  std::vector<std::vector<long long>> dp (first.size() + 1, std::vector<long long>(second.size() + 1));
  for (int i = 0; i <= first.size(); ++i) {
    dp[i][0] = 0;
  }
  for (int i = 0; i <= second.size(); ++i) {
    dp[0][i] = 0;
  }
  for (int i = 1; i <= first.size(); ++i) {
    long long dp_best = 0;
    for (int j = 1; j <= second.size(); ++j) {
      dp[i][j] = dp[i - 1][j];
      if (first[i - 1] == second[j - 1] && dp[i - 1][j] < dp_best + 1) {
        dp[i][j] = dp_best + 1;
      }
      if (first[i - 1] > second[j - 1] && dp[i - 1][j] > dp_best) {
        dp_best = dp[i - 1][j];
      }
    }
  }

  long long pos = 0;
  for (int j = 1; j <= second.size(); ++j) {
    if (dp[first.size()][pos] < dp[first.size()][j]) {
      pos = j;
    }
  }

  return dp[first.size()][pos];
}

int main() {
  int n, m;
  std::vector<long long> first, second;
  std::cin >> n >> m;

  for (int i = 0; i < n; ++i) {
    long long value;
    std::cin >> value;
    first.push_back(value);
  }

  for (int i = 0; i < m; ++i) {
    long long value;
    std::cin >> value;
    second.push_back(value);
  }

  std::cout << LcisSize(first, second);
  return 0;
}