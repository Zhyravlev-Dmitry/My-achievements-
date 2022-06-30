#include <iostream>
#include <vector>

class Heap {
 public:
  long long int GetMin() {
    data.push_back({0, 0});
    return data[heap.at(1)].meaning;
  }

  void Insert(int value) {
    data.push_back({heap.size(), value});
    heap.push_back(data.size() - 1);
    SiftUp(static_cast<int>(heap.size()) - 1);
  }

  void  ExtractMin() {
    data.push_back({0, 0});
    heap[1] = heap.back();
    data[heap.back()].link_min = 1;
    SiftDown(1);
    heap.pop_back();
  }

  void DecreaseKey(long long int key, long long int decrease) {
    data.push_back({0, 0});
    data[key].meaning -= decrease;
    SiftUp(data[key].link_min);
  }

  void Show() {
    for (int i: heap) {
      std::cout << data[i].meaning << " ";
    }
    std::cout << "\n";
  }

 private:
  struct Info {
    size_t link_min;
    long long int meaning;
  };
  std::vector<int> heap = {0};
  std::vector<Info> data = {{0,0}};

  void SiftUp(int node) {
    while (node != 1) {
      if (data[heap.at(node)].meaning < data[heap.at(node / 2)].meaning) {
        std::swap(data[heap[node]].link_min, data[heap[node / 2]].link_min);
        std::swap(heap[node], heap[node / 2]);
        node /= 2;
      } else {
        break;
      }
    }
  }

  void SiftDown(int node) {
    while (2 * node <= heap.size() - 1) {
      int node_change = 2 * node;
      if (2 * node + 1 <= heap.size() - 1
          && data[heap[2 * node + 1]].meaning < data[heap[2 * node]].meaning) {
        node_change = 2 * node + 1;
      }
      if (data[heap[node_change]].meaning < data[heap[node]].meaning) {
        std::swap(data[heap[node_change]].link_min, data[heap[node]].link_min);
        std::swap(heap[node_change], heap[node]);
        node = node_change;
      } else {
        break;
      }
    }
  }
};

void Emulation(int quantity, Heap& heap) {
  std::string request;
  for (int iter = 0; iter < quantity; ++iter) {
    std::cin >> request;
    if (request == "getMin"){
      std::cout << heap.GetMin() << "\n";
    } else if (request == "extractMin") {
      heap.ExtractMin();
    } else if (request == "decreaseKey") {
      int pos, delta;
      std::cin >> pos >> delta;
      heap.DecreaseKey(pos, delta);
    } else if (request == "insert") {
      int value;
      std::cin >> value;
      heap.Insert(value);
    }
  }
}
void Emulation(Heap& heap) {
  std::string request;
  std::cin >> request;
  while (request != "exit") {
    if (request == "getMin"){
      std::cout << heap.GetMin() << "\n";
    } else if (request == "extractMin") {
      heap.ExtractMin();
    } else if (request == "decreaseKey") {
      int pos, delta;
      std::cin >> pos >> delta;
      heap.DecreaseKey(pos, delta);
    } else if (request == "insert") {
      int value;
      std::cin >> value;
      heap.Insert(value);
    } else if (request == "show") {
      heap.Show();
    } else {
      std::cout << "error\n";
    }
    std::cin >> request;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  Heap heap;
  int quantity;
  std::cin >> quantity;
  Emulation(quantity, heap);
  //Emulation(heap);
  return 0;
}