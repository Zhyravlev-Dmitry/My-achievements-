#include <iostream>
#include <vector>

class Fenwick_Tree {
 public:
  Fenwick_Tree(std::vector<int> data) : data_(data) {
    for (int i = 0; i < data.size(); ++i) {
      if (i % 2 == 0)
        data_[i] = data[i];
      if (i % 2 != 0)
        data_[i] = -data[i];
    }
    sum_array_.resize(data_.size() + 1);
    for (int i = 1; i < sum_array_.size(); ++i) {
      Build(i, data_[i - 1]);
    }

  }

  void Update(int pos, int value) {
    if (pos % 2 == 0)
      value = -value;
    for (int i = pos; i < sum_array_.size(); i = i | (i + 1)) {
      sum_array_[i] += value - data_[pos - 1];
    }
    data_[pos - 1] = value;

  }

  int Get(int left, int right) {
    int res = GetSumPrefix(right);
    res -= GetSumPrefix(left - 1);
    if (left % 2 == 0)
      res *= -1;
    return res;

  }

 private:
  std::vector<int> sum_array_;
  std::vector<int> data_;

  void Build(int pos, int value) {
    for (int i = pos; i < sum_array_.size(); i = i | (i + 1)) {
      sum_array_[i] += value;
    }
  }

  int GetSumPrefix(int pos) {
    int res = 0;
    for (int i = pos; i > 0; i = (i & (i + 1)) - 1) {
      res += sum_array_[i];
    }
    return res;
  }
};

std::vector<int> Reading() {
  int length;
  std::cin >> length;
  std::vector<int> data;
  for (int i = 0; i < length; ++i) {
    int value;
    std::cin >> value;
    data.push_back(value);
  }
  return data;
}


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  Fenwick_Tree tree(Reading());
  int quantity;
  std::cin >> quantity;
  for (int i = 0; i < quantity; ++i) {
    int flag;
    std::cin >> flag;
    if (flag == 0) {
      int pos;
      int value;
      std::cin >> pos >> value;
      tree.Update(pos, value);
    }
    if (flag == 1) {
      int left;
      int right;
      std::cin >> left >> right;
      std::cout << tree.Get(left, right) << "\n";
    }
  }
  return 0;
}