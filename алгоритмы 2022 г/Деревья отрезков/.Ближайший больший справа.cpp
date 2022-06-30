#include <iostream>
#include <vector>
#include <random>

class TreeMax {
 public:
  explicit TreeMax(const std::vector<int>& data) {
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
    pos += size / 2 - 1;
    if (pos >= size / 2) {
      tree[pos] = value;
      pos /= 2;
    }
    while(pos > 0) {
      tree[pos] = std::max(tree[pos * 2], tree[pos * 2 + 1]);
      pos /= 2;
    }
  }

  int GetMax (int left, int right) {
    int answer = GetMax(1, size / 2, size - 1, left + size / 2 - 1, right + size / 2 - 1);
    return answer;
  }

  int Larger (int pos, int value) {
    int left = pos;
    int right = size / 2;
    if (GetMax(left, right) < value) {
      return -1;
    }
    while (right - left > 1) {
      int median = (left + right) / 2;
      //std::cout << left << " " << median << " " << right << " " << GetMax(left, median) << "\n";
      if (GetMax(left, median) < value) {
        left = median;
      } else {
        right = median;
      }
    }
    if (tree[left - 1 + size / 2] >= value) {
      return left;
    } else {
      return  right;
    }
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

  static int Pow(size_t value) {
    int degree = 0;
    int pow = 1;
    while (pow < value) {
      pow *= 2;
      degree += 1;
    }
    return pow;
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

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int length;
  int quantity;
  std::vector<int> data;
  std::cin >> length >> quantity;
  for (int i = 0; i < length; ++i) {
    int value;
    std::cin >> value;
    data.push_back(value);
  }
  TreeMax tree_max(data);
  for (int i = 0; i < quantity; ++i) {
    int type;
    int pos;
    int value;
    std::cin >> type >> pos >> value;
    if (type == 0) {
      tree_max.update(pos, value);
    }
    if (type == 1) {
      std::cout << tree_max.Larger(pos, value) << "\n";
    }
    if (type == -1) {
      tree_max.Show();
    }
  }
  return 0;
}