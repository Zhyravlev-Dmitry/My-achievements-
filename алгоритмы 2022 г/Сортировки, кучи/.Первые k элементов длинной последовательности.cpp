#include <iostream>
#include <vector>
#include <algorithm>

class Heap {
 public:
  std::vector<long long int> heap = {0};

  void Insert(long long int value) {
    heap.push_back(value);
    SiftUp(static_cast<int>(heap.size()) - 1);
  }

  void  ExtractMin() {
    heap[1] = heap.back();
    SiftDown(1);
    heap.pop_back();
  }

 private:
    void SiftUp(long long int node) {
    while (node != 1) {
      if (heap.at(node) > heap.at(node / 2)) {
        std::swap(heap[node], heap[node / 2]);
        node /= 2;
      } else {
        break;
      }
    }
  }

  void SiftDown(long long int node) {
    while (2 * node <= heap.size() - 1) {
      long long int node_change = 2 * node;
      if (2 * node + 1 <= heap.size() - 1
          && heap[2 * node + 1] > heap[2 * node]) {
        node_change = 2 * node + 1;
      }
      if (heap[node_change] > heap[node]) {
        std::swap(heap[node_change], heap[node]);
        node = node_change;
      } else {
        break;
      }
    }
  }
};

int main() {
  long long int n, k;
  long long int a, x, y;
  std::cin >> n >> k >> a >> x >> y;
  Heap heap;
  long long int d = 1;
  for (int i = 0; i < 30; ++i) {
    d *=2;
  }
  for (long long int i = 0; i < k; ++i) {
    a = (x * a + y) % d;
    heap.Insert(a);
  }
  for (long long int i = k; i < n; ++i) {
    a = (x * a + y) % d;
    heap.Insert(a);
    heap.ExtractMin();
  }
  std::sort(heap.heap.begin() + 1, heap.heap.end());
  for (long long int i = 1; i <= k; ++i) {
    std::cout << heap.heap[i] << " ";
  }
  return 0;
}