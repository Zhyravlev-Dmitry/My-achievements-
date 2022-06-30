#include <iostream>
#include <vector>

class DinamicProgramming {
 public:
  void Write_ans() {
    std::cout << static_cast<long long>((dp[dp.size() - 1]) - 1) % magic;
  }

  DinamicProgramming(std::vector<long long> &a) : prev(a.size() + 1, -1), dp(a.size() + 1, -2) {
    dp[0] = 1;
    create_dp(a);
  };

 private:
  const long long magic = 1000000007;
  std::vector<long long> prev;
  std::vector<long long> dp;

  void create_dp(std::vector<long long> &a) {
    for (int pos = 1; pos <= a.size(); ++pos) {
      dp[pos] = (dp[pos - 1] * 2) % magic;
      prev[a[pos - 1]] != -1 && (dp[pos] = (dp[pos] - dp[prev[a[pos - 1]]]));
      dp[pos] < 0 && (dp[pos] += magic);
      prev[a[pos - 1]] = pos - 1;
    }
  }
};


int main() {

  long long quantity;
  std::cin >> quantity;

  std::vector<long long> a(quantity);
  for (int i = 0; i < quantity; ++i) {
    std::cin >> a[i];
  }

  DinamicProgramming dp(a);
  dp.Write_ans();

}