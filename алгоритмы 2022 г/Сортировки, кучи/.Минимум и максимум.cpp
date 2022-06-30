#include <iostream>
#include <vector>

class Heap {
 public:
  long long int GetMin() {
    long long int ans = data[heap_min.at(1)].meaning;
    ExtractMin();
    return ans;
  }

  long long int GetMax() {
    long long int ans = data[heap_max.at(1)].meaning;
    ExtractMax();
    return ans;
  }

  void Insert(long long int value) {
    data.push_back({heap_min.size(), heap_max.size(), value});
    heap_min.push_back(data.size() - 1);
    heap_max.push_back(data.size() - 1);
    SiftUpMin(static_cast<int>(heap_min.size()) - 1);
    SiftUpMax(static_cast<int>(heap_max.size()) - 1);
  }

  void Show() {
    for (int i: heap_min)
      std::cout << data[i].meaning << " ";
    std::cout << "\n";
  }
 private:
  struct Info {
    size_t link_min;
    size_t link_max;
    long long int meaning;
  };
  std::vector<int> heap_min = {0};
  std::vector<int> heap_max = {0};
  std::vector<Info> data = {{0, 0, 0}};

  void SiftUpMin(int node) {
    while (node != 1) {
      if (data[heap_min.at(node)].meaning < data[heap_min.at(node / 2)].meaning) {
        std::swap(data[heap_min[node]].link_min, data[heap_min[node / 2]].link_min);
        std::swap(heap_min[node], heap_min[node / 2]);
        node /= 2;
      } else {
        break;
      }
    }
  }

  void SiftUpMax(int node) {
    while (node != 1) {
      if (data[heap_max.at(node)].meaning > data[heap_max.at(node / 2)].meaning) {
        std::swap(data[heap_max[node]].link_max, data[heap_max[node / 2]].link_max);
        std::swap(heap_max[node], heap_max[node / 2]);
        node /= 2;
      } else {
        break;
      }
    }
  }

  void SiftDownMin(int node) {
    while (2 * node <= heap_min.size() - 1) {
      int node_change = 2 * node;
      if (2 * node + 1 <= heap_min.size() - 1
          && data[heap_min[2 * node + 1]].meaning < data[heap_min[2 * node]].meaning) {
        node_change = 2 * node + 1;
      }
      if (data[heap_min[node_change]].meaning < data[heap_min[node]].meaning) {
        std::swap(data[heap_min[node_change]].link_min, data[heap_min[node]].link_min);
        std::swap(heap_min[node_change], heap_min[node]);
        node = node_change;
      } else {
        break;
      }
    }
  }

  void SiftDownMax(int node) {
    while (2 * node <= heap_max.size() - 1) {
      int node_change = 2 * node;
      if (2 * node + 1 <= heap_max.size() - 1
          && data[heap_max[2 * node + 1]].meaning > data[heap_max[2 * node]].meaning) {
        node_change = 2 * node + 1;
      }
      if (data[heap_max[node_change]].meaning > data[heap_max[node]].meaning) {
        std::swap(data[heap_max[node_change]].link_max, data[heap_max[node]].link_max);
        std::swap(heap_max[node_change], heap_max[node]);
        node = node_change;
      } else {
        break;
      }
    }
  }

  void  ExtractMin() {
    Extract(heap_min[1]);
  }

  void  ExtractMax() {
    Extract(heap_max[1]);
  }

  void Extract(int namber_element) {
    int namber_min = data[namber_element].link_min;
    int namber_max = data[namber_element].link_max;
    ExtractMin(namber_min);
    ExtractMax(namber_max);
  }

  void  ExtractMin(int node) {
    heap_min[node] = heap_min.back();
    data[heap_min.back()].link_min = node;
    SiftDownMin(node);
    SiftUpMin(node);
    heap_min.pop_back();
  } // Значения в массиве остаются

  void  ExtractMax(int node) {
    heap_max[node] = heap_max.back();
    data[heap_max.back()].link_max = node;
    SiftDownMax(node);
    SiftUpMax(node);
    heap_max.pop_back();
  } // Значения в массиве остаются
};

void Emulation(int iter) {
  std::string request;
  Heap heap;
  for (int i = 0; i < iter; ++i) {
    std::cin >> request;
    if (request[0] == 'I') {
      request = request.substr(7, request.size() - 8);
      heap.Insert(std::stoi(request));
    } else if (request == "GetMin") {
      std::cout << heap.GetMin() << "\n";
    } else if (request == "GetMax") {
      std::cout << heap.GetMax() << "\n";
    }
  }
}

int main() {
  int iter;
  Heap heap;
  std::cin >> iter;
  Emulation(iter);
  return 0;
}