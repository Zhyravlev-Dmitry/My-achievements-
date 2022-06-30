#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<long long> Edit(std::string &first, std::string &second);

std::string CommonLine(const std::string& first_str, const std::string& second_str);

std::string CaseSecond(std::string first_str, std::string second_str) {
  std::string first_half;
  std::string second_half;

  std::vector<long long> first_edit;
  std::vector<long long> second_edit;

  long long first_pos = static_cast<int>(first_str.length()) / 2;

  first_half = first_str.substr(0, first_pos);
  second_half = first_str.substr(first_pos, static_cast<int>(first_str.length()) - first_pos);

  first_edit = Edit(first_half, second_str);

  std::reverse(second_half.begin(), second_half.end());
  std::reverse(second_str.begin(), second_str.end());

  second_edit = Edit(second_half, second_str);
  std::reverse(second_edit.begin(), second_edit.end());

  std::reverse(second_half.begin(), second_half.end());
  std::reverse(second_str.begin(), second_str.end());

  std::vector<long long> Sum;
  long long max = first_edit[0] + second_edit[0], pos = 0;
  for (int i = 0; i < second_edit.size(); ++i) {
    Sum.push_back(first_edit[i] + second_edit[i]);
    if (Sum[i] > max) {
      max = Sum[i];
      pos = i;
    }
  }

  std::string first_res = second_str.substr(0, pos);
  std::string second_res = second_str.substr(pos, second_str.length() - pos);
  std::string answer = CommonLine(first_half, first_res) + CommonLine(second_half, second_res);
  return answer;
}

std::string CommonLine(const std::string& first_str, const std::string& second_str) {

  if (first_str.length() == 0) {
    return "";
  }

  if (first_str.length() == 1) {
    bool flag = false;
    for (char c: second_str) {
      if (c == first_str[0]) {
        flag = true;
        break;
      }
    }

    if (flag)
      return first_str;
    else
      return "";
  }

  return CaseSecond(first_str, second_str);
}

std::vector<long long> Edit(std::string &first, std::string &second) {
  std::vector<long long> answer(second.length() + 1, 0);
  for (auto &x: first) {
    std::vector<long long> prev = answer;
    for (int i = 0; i < second.length(); ++i) {
      if (x == second[i]) {
        answer[i + 1] = prev[i] + 1;
      } else {
        answer[i + 1] = std::max(answer[i], prev[i + 1]);
      }
    }
  }
  return answer;
}

int main() {

  std::string first_str;
  std::string second_str;

  std::cin >> first_str;
  std::cin >> second_str;

  std::cout << CommonLine(first_str, second_str);
}