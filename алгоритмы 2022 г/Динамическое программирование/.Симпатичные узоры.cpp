
#include <vector>
#include <iostream>

bool Bit(long long mask, long long pos) {
  return (mask >> pos) & 1;
}

bool IsOk(long long mask_1, long long mask_2, long long quantity) {
  bool ok = true;
  std::vector<bool> b(4);
  for (long long i = 0; i < quantity - 1; ++i) {
    b[1] = Bit(mask_1, i);
    b[2] = Bit(mask_1, i + 1);
    b[3] = Bit(mask_2, i);
    b[4] = Bit(mask_2, i + 1);

    if (b[1] == 1 && b[2] == 1 && b[3] == 1 && b[4] == 1) {
      return false;
    }
    if (b[1] == 0 && b[2] == 0 && b[3] == 0 && b[4] == 0) {
      return false;
    }
  }
  return ok;
}

void IsOkComplection(std::vector<std::vector<bool>>& is_ok, long long qantity) {
  long long mask_number = 1 << qantity;
  if (mask_number == 2) {
    is_ok[0][0] = 1;
    is_ok[0][1] = 1;
    is_ok[1][0] = 1;
    is_ok[1][1] = 1;
    return;
  }
  for (long long mask_1 = 0; mask_1 < mask_number; ++mask_1) {
    for (long long mask_2 = 0; mask_2 < mask_number; ++mask_2) {
      if (IsOk(mask_1, mask_2, qantity)) {
        is_ok[mask_1][mask_2] = 1;
      } else {
        is_ok[mask_1][mask_2] = 0;
      }
    }
  }
}

int main() {
  long long height;
  long long length;
  std::cin >> height >> length;
  if (length < height) { std::swap(length, height); }
  if (length == 30) {
    std::cout << (1 << 30);
    return 0;
  }
  std::vector<std::vector<bool>> is_ok(1 << height , std::vector<bool> (1 << length));
  IsOkComplection(is_ok, height);
  std::vector<std::vector<long long>> dp(length, std::vector<long long> (1 << height));
  for (long long i = 0; i < length; ++i) {
    for (long long j = 0; j < dp[0].size(); ++j) {
      dp[i][j] = 0;
    }
  }
  for (long long i = 0; i < dp[0].size(); ++i) {
    dp[0][i] = 1;
  }
  for (long long i = 1; i < length; ++i) {
    for (long long mask = 0; mask < 1 << height; ++mask) {
      for (long long new_mask = 0; new_mask < 1 << height; ++new_mask) {
        if (is_ok[mask][new_mask]) {
          dp[i][new_mask] += dp[i-1][mask];
        }
      }
    }
  }
  long long answer = 0;
  for (long long i: dp[length - 1]) {
    answer += i;
  }
  std::cout << answer;
  return 0;
}