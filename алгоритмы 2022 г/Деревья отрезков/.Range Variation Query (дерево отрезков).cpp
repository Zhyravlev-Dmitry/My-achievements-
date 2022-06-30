#include <fstream>
#include <iostream>
#include <vector>

class TreeMax {
 public:
  TreeMax(const std::vector<int>& data) {
    int pow = Pow(data.size());
    tree = new int[2 * pow];
    size = 2 * pow;
    for (int i = pow; i < size; ++i) {
      if (i - pow < data.size()) {
        tree[i] = data[i - pow];
      } else {
        tree[i] = emptiness;
      }
    } // заполнение пустых клеток нулями
    for (int i = size - 1; i > 1; i -= 2) {
      tree[i/2] = std::max(tree[i], tree[i - 1]);
    }
  }

  void update (int pos, int value) {
    update(1, size / 2, size - 1, pos + size / 2 - 1, value);
  }

  int GetMax (int left, int right) {
    int answer = GetMax(1, size / 2, size - 1, left + size / 2 - 1, right + size / 2 - 1);
    return answer;
  }

  void Show() {
    for (int i = 1; i < size; ++i) {
      std::cout << tree[i] << " ";
    }
    std::cout << "\n";
  }

  ~TreeMax() {
    delete [] tree;
  }

 private:
  int* tree;
  int size;
  const int emptiness = -2'147'483'647;

  int Pow(size_t value) {
    int degree = 0;
    int pow = 1;
    while (pow < value) {
      pow *= 2;
      degree += 1;
    }
    return pow;
  }

  void update (int top, int tree_left, int tree_right, int pos, int value) {
    if (pos >= size / 2) {
      tree[pos] = value;
      pos /= 2;
    }
    while(pos > 0) {
      tree[pos] = std::max(tree[pos * 2], tree[pos * 2 + 1]);
      pos /= 2;
    }
  }

  int GetMax (int top, int tree_left, int tree_right, int left, int right) {
    if (tree_left == left && tree_right == right) {
      return tree[top];
    }
    int tm = (tree_left + tree_right) / 2;
    int ans = emptiness;
    if (left <= tm) {
      ans = GetMax(top * 2, tree_left, tm, left, std::min(right, tm));
    }
    if (right >= tm + 1) {
      int ans_2;
      ans_2 = GetMax(top * 2 + 1, tm + 1, tree_right, std::max(left, tm + 1), right);
      ans = std::max(ans, ans_2);
    }
    return ans;
  }
};

class TreeMin {
 public:
  TreeMin(const std::vector<int>& data) {
    int pow = Pow(data.size());
    tree = new int[2 * pow];
    size = 2 * pow;
    for (int i = pow; i < size; ++i) {
      if (i - pow < data.size()) {
        tree[i] = data[i - pow];
      } else {
        tree[i] = emptiness;
      }
    } // заполнение пустых клеток нулями
    for (int i = size - 1; i > 1; i -= 2) {
      tree[i/2] = std::min(tree[i], tree[i - 1]);
    }

  }

  void update (int pos, int value) {
    update(1, size / 2, size - 1, pos + size / 2 - 1, value);
  }

  int GetMin (int left, int right) {
    int answer = GetMin(1, size / 2, size - 1, left + size / 2 - 1, right + size / 2 - 1);
    return answer;
  }

  void Show() {
    for (int i = 1; i < size; ++i) {
      std::cout << tree[i] << " ";
    }
    std::cout << "\n";
  }

  ~TreeMin() {
    delete [] tree;
  }

 private:
  int* tree;
  int size;
  const int emptiness = 2'147'483'647;

  int Pow(size_t value) {
    int degree = 0;
    int pow = 1;
    while (pow < value) {
      pow *= 2;
      degree += 1;
    }
    return pow;
  }

  void update (int top, int tree_left, int tree_right, int pos, int value) {
    if (pos >= size / 2) {
      tree[pos] = value;
      pos /= 2;
    }
    while(pos > 0) {
      tree[pos] = std::min(tree[pos * 2], tree[pos * 2 + 1]);
      pos /= 2;
    }
  }

  int GetMin (int top, int tree_left, int tree_right, int left, int right) {
    if (tree_left == left && tree_right == right) {
      return tree[top];
    }
    int tm = (tree_left + tree_right) / 2;
    int ans = emptiness;
    if (left <= tm) {
      ans = GetMin(top * 2, tree_left, tm, left, std::min(right, tm));
    }
    if (right >= tm + 1) {
      int ans_2;
      ans_2 = GetMin(top * 2 + 1, tm + 1, tree_right, std::max(left, tm + 1), right);
      ans = std::min(ans, ans_2);
    }
    return ans;
  }
};

int main() {
  const int n = 100'000;
  //const int n = 10;
  std::vector<int> data(n);
  for (long long int i = 1; i <= n; ++i) {
    data[i - 1] = (i * i % 12345) + (i * i * i % 23456);
  }
  TreeMax tree_max(data);
  TreeMin tree_min(data);
  int k;
  std::cin >> k;
  for (int i = 0; i < k; ++i) {
    int request_x;
    int request_y;
    std::cin >> request_x >> request_y;
    if (request_x == 0) {
      tree_min.Show();
      std::cout << "-----------------------------------------------------------------------------------------\n";
      tree_max.Show();
    }
    if (request_x > 0) {
      int max = tree_max.GetMax(request_x, request_y);
      int min = tree_min.GetMin(request_x, request_y);
      std::cout << max - min << "\n";
    }
    if (request_x < 0) {
      tree_max.update(-request_x, request_y);
      tree_min.update(-request_x, request_y);
    }
  }
  return 0;
}
