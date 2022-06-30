#include <iostream>
#include <vector>

int Lcs(const std::vector<int>& sequence_first, const std::vector<int>& sequence_second) {
  std::vector<std::vector<int>> lcs (sequence_first.size() + 1, std::vector<int>(sequence_second.size() + 1));
  for (int i = 0; i <= sequence_first.size(); ++i) {
    lcs[i][0] = 0;
  }
  for (int j = 0; j <= sequence_second.size(); ++j) {
    lcs[0][j] = 0;
  }
  for (int i = 1; i <= sequence_first.size(); ++i) {
    for (int j = 1; j <= sequence_second.size(); ++j) {
      if (sequence_first[i - 1] == sequence_second[j - 1]) {
        lcs[i][j] = lcs[i - 1][j - 1] + 1;
      } else {
        if (lcs[i - 1][j] >= lcs[i][j - 1]) {
          lcs[i][j] = lcs[i - 1][j];
        } else {
          lcs[i][j] = lcs[i][j - 1];
        }
      }
    }
  }
  return lcs[sequence_first.size()][sequence_second.size()];
}

int main() {
  int length_first;
  int length_second;
  std::vector<int> sequence_first;
  std::vector<int> sequence_second;
  std::cin >> length_first;
  for (int i = 0; i < length_first; ++i) {
    int value;
    std::cin >> value;
    sequence_first.push_back(value);
  }
  std::cin >> length_second;
  for (int i = 0; i < length_second; ++i) {
    int value;
    std::cin >> value;
    sequence_second.push_back(value);
  }
  std::cout << Lcs(sequence_first, sequence_second);
  return 0;
}