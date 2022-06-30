#include <iostream>
#include <vector>

class Fenwick_Tree {
 public:
  Fenwick_Tree(int size) {
    size_ = size + 2;
    sum_array_.resize(size_);
    for (int i = 0; i < size_; ++i) {
      sum_array_[i].resize(size_);
      for (int j = 0; j < size_; ++j) {
        sum_array_[i][j].resize(size_);
        for (int k = 0; k < size_; ++k) {
          sum_array_[i][j][k] = 0;
        }
      }
    }

  }

  void Update(int x, int y, int z, int add) {
    x += 1; y += 1; z += 1;
    for (int i = x; i < size_; i = i | (i + 1)) {
      for (int j = y; j < size_; j = j | (j + 1)) {
        for (int k = z; k < size_; k = k | (k+1)) {
          sum_array_[i][j][k] += add;
        }
      }
    }

  }

  long long Get(int x1, int y1, int z1, int x2, int y2, int z2) {
    x1 += 1; y1 += 1; z1 += 1; x2 += 1; y2 += 1; z2 += 1;
    long long res = GetSumPrefix(x2, y2, z2);
    res -= GetSumPrefix(x1 - 1, y2, z2);
    res -= GetSumPrefix(x2, y1 - 1, z2);
    res -= GetSumPrefix(x2, y2, z1 - 1);
    res += GetSumPrefix(x1 - 1, y1 - 1, z2);
    res += GetSumPrefix(x2, y1 - 1, z1 - 1);
    res += GetSumPrefix(x1 - 1, y2, z1 - 1);
    res -= GetSumPrefix(x1 - 1, y1 - 1, z1 - 1);
    return res;
  }

 private:
  std::vector<std::vector<std::vector<int>>> sum_array_;
  int size_;

  long long GetSumPrefix(int x, int y, int z) {
    long long res = 0;
    //if (x == 0 || y == 0 || z == 0)
    //  return res;
    for (int i = x; i > 0; i = (i & (i + 1)) - 1) {
      for (int j = y; j > 0; j = (j & (j + 1)) - 1) {
        for (int k = z; k > 0; k = (k & (k + 1)) - 1) {
          res += sum_array_[i][j][k];
        }
      }
    }
    return res;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int size;
  std::cin >> size;
  Fenwick_Tree tree(size);
  int request;
  std::cin >> request;
  while (request != 3) {
    if (request == 2) {
      int x1, x2, y1, y2, z1, z2;
      std::cin >> x1 >> x2 >> y1 >> y2 >> z1 >> z2;
      std::cout << tree.Get(x1, x2, y1, y2, z1, z2) << "\n";
    }
    if (request == 1) {
      int x, y, z, add;
      std::cin >> x >> y >> z >> add;
      tree.Update(x, y, z, add);
    }
    std::cin >> request;
  }
  return 0;
}