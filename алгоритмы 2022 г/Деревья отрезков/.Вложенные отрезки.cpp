#include <iostream>
#include <vector>
#include <algorithm>

class Tree {
 public:
  Tree(int length) {
    int pow = Pow(length);
    tree = new int[2 * pow];
    size = 2 * pow;
    for (int i = pow; i < size; ++i) {
      if (i - pow < length) {
        tree[i] = 0;
      } else {
        tree[i] = 1;
      }
    }
    for (int i = size - 1; i > 1; i -= 2) {
      tree[i/2] = tree[i] + tree[i - 1];
    }
  }

  void update (int pos) {
    int value = 1;
    pos += size / 2 - 1;
    //while (tree[pos] == 1) {
    //  pos -= 1;
    //}
    if (pos >= size / 2) {
      tree[pos] += value;
      pos /= 2;
    }
    while(pos > 0) {
      tree[pos] = tree[pos * 2] + tree[pos * 2 + 1];
      pos /= 2;
    }
  }

  int GetSum (int left, int right) {
    int answer = GetSum(1, size / 2, size - 1, left + size / 2 - 1, right + size / 2 - 1);
    return answer;
  }

  void Show() {
    for (int i = 1; i < size; ++i) {
      std::cout << tree[i] << " ";
    }
    std::cout << "\n";
  }

  ~Tree() {
    delete [] tree;
  }

 private:
  int* tree;
  int size;

  static int Pow(size_t value) {
    int degree = 0;
    int pow = 1;
    while (pow < value) {
      pow *= 2;
      degree += 1;
    }
    return pow;
  }

  int GetSum (int top, int tree_left, int tree_right, int left, int right) {
    if (tree_left == left && tree_right == right) {
      return tree[top];
    }
    int tm = (tree_left + tree_right) / 2;
    int ans = 0;
    if (left <= tm) {
      ans += GetSum(top * 2, tree_left, tm, left, std::min(right, tm));
    }
    if (right >= tm + 1) {
      ans += GetSum(top * 2 + 1, tm + 1, tree_right, std::max(left, tm + 1), right);
    }
    return ans;
  }
};

int Bp(const std::vector<long long>& data, int value) {
  int left = -1;
  int right = data.size();
  while (right - left > 1) {
    int median = (right + left) / 2;
    if (data[median] <= value) {
      left = median;
    } else {
      right = median;
    }
  }
  left += 1;
  return left;
}

bool comp(std::pair<long long, long long> first, std::pair<long long, long long> second) {
  bool flag = (first.first <= second.first);
  if (first.first == second.first) {
    flag = (first.second > second.second);
  }
  return flag;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  std::vector<std::pair<long long, long long>> pairs;
  std::vector<long long> right;
  for (int i = 0; i < n; ++i) {
    long long a, b;
    std::cin >> a >> b;
    pairs.push_back(std::make_pair(a, b));
    right.push_back(b);
  }
  Tree tree(pairs.size());
  std::sort(pairs.begin(), pairs.end(), comp);
  std::sort(right.begin(), right.end());

  //for (auto i: pairs)
  //  std::cout << i.first << " " << i.second << "\n";
  //for (auto i: right)
  //  std::cout << i << " ";
  //std::cout << "\n";
  //tree.Show();

  long long int sum = 0;
  int coefficient = 1;
  for (int i = 0; i < n; ++i) {
    int pos = Bp(right, pairs[i].second);
    tree.update(pos);
    if(i + 1 < n && pairs[i+1].first == pairs[i].first && pairs[i+1].second == pairs[i].second) {
      coefficient += 1;
      continue;
    }
    //tree.Show();
    //std::cout << pos << " " << tree.GetSum(1, pos) << "\n";
    sum += (pos - tree.GetSum(1, pos)) * coefficient;
    coefficient = 1;
  }
  std::cout << sum;
  return 0;
}