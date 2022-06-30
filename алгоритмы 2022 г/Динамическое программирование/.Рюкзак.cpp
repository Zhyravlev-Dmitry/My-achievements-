#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <random>

class Backpack {
 public:
  Backpack() = default;
  Backpack(long long n, std::vector<long long>& data, long long weight) {
    this->n = n;
    this->weight = weight;
    for (int i = 0; i < n; ++i) {
      this->data.push_back(data[i]);
    }
  }

  void PrintSum() {
    for (long long i: sum) {
      std:: cout << i << " ";
    }
    std::cout << std::endl;
  }

  int ReturnAnswer() {
    execute();
    return answer;
  }

 private:
  long long n;
  std::vector<long long> data;
  long long weight;
  long long answer = 0;
  std::vector<long long> sum;

  long long fSum(std::vector<long long>& data, long long mask, long long leftPos) {
    long long sum = 0;
    long long iter = leftPos - 1;
    while (mask > 0) {
      if (mask % 2 != 0) {
        sum += data[iter];
      }
      mask /= 2;
      iter -= 1;
    }
    return sum;
  }

  int upper_bound(std::vector<long long>& data, long long value) {
    long long l = -1;
    long long r = data.size();
    while (r - l > 1) {
      long long m = (l + r) / 2;
      if (data[m] > value)
        r = m;
      else
        l = m;
    }
    return r;
  }

  void execute() {
    for (long long mask = 0; mask < (1 << n/2); ++mask) {
      sum.push_back(fSum(data, mask, n/2));
    }
    std::sort(sum.begin(), sum.end());

    for (long long mask = 0; mask < (1 << (n - n / 2)); ++mask) {
      long long localSum = fSum(data, mask, n);
//    std::cout << weight - localSum << "\n";
      long long methods = upper_bound(sum, weight - localSum);
      answer += methods;
    }
  }

  friend std::istream& operator>>(std::istream& in, Backpack& node);
};

std::istream& operator>>(std::istream& in, Backpack& node) {
  std::cin >> node.n;
  node.data.resize(0);
  for (int i = 0; i < node.n; ++i) {
    int value;
    std::cin >> value;
    node.data.push_back(value);
  }
  std::cin >> node.weight;
  return in;
}

int main() {
  Backpack backpack;
  std::cin >> backpack;
  std::cout << backpack.ReturnAnswer();
  return 0;
}