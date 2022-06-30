#include <iostream>
#include <vector>
#include <windows.h>
#include <random>

long long int QuickSelect(std::vector<long long int>& data, int k_ordinal, uint32_t left, uint32_t right);

std::pair<int, int> Partition(std::vector<long long int>& data, long long int pivot,
               const uint32_t& left_initial, const uint32_t& right_initial) {
  uint32_t left = left_initial;
  uint32_t right = right_initial;
  while (right - left > 0) {
    if (data[right] > pivot) {
      right -= 1;
      continue;
    }
    if (data[left] <= pivot) {
      left += 1;
      continue;
    }
    std::swap(data[left], data[right]);
  }
  int size_min_equal = right; // right indicates the maximum of the left elements
  left = left_initial;
  while (right - left > 0) {
    if (data[right] == pivot) {
      right -= 1;
      continue;
    }
    if (data[left] < pivot) {
      left += 1;
      continue;
    }
    std::swap(data[left], data[right]);
  }
  return std::make_pair(right, size_min_equal);
}

long long int SortAndMedian(const std::vector<long long int>& data, uint32_t left, uint32_t right) {
  std::vector<long long int> five_values;
  for (int i = left; i <= right; ++i) {
    five_values.push_back(data[i]);
  }
  for (int i = 0; i < five_values.size() - 1; ++i) {
    for (int j = i + 1; j < five_values.size(); ++j) {
      if (five_values[i] > five_values[j]) {
        std::swap(five_values[i], five_values[j]);
      }
    }
  }
  return five_values[five_values.size() / 2];
}

long long int MedianOfMedian(const std::vector<long long int>& data, uint32_t left, uint32_t right) {
  std::vector<long long int> array_of_medians;
  for (uint32_t i = left + 4; i <= right; i += 5) {
    array_of_medians.push_back(SortAndMedian(data, i - 4, i));
  }
  if ((right - left + 1) % 5 != 0) {
    left += (right - left + 1) / 5 * 5;
    array_of_medians.push_back(SortAndMedian(data, left, right));
  }
  if (array_of_medians.size() == 1) {
    return array_of_medians.back();
  }
  return QuickSelect(array_of_medians, static_cast<int>(array_of_medians.size() / 2),
                     0, array_of_medians.size() - 1);
  // return MedianOfMedian(array_of_medians, 0, array_of_medians.size() - 1);
}

long long int MedianOfMedian(const std::vector<long long int>& data, uint32_t left,
                             uint32_t right, const std::string& flag) {
  SYSTEMTIME st;
  GetLocalTime(&st);
  long long int seed = st.wMinute * 6000 + st.wSecond * 100 + st.wMilliseconds;
  std::mt19937 gen(seed);
  uint32_t pivot_index = gen() % (right - left + 2) + left;
  return data[pivot_index];
}

long long int QuickSelect(std::vector<long long int>& data, int k_ordinal, uint32_t left, uint32_t right) {
  if (right - left == 0) {
    return data[left];
  }
  long long int pivot = MedianOfMedian(data, left, right);
  std::pair<int, int> sizes = Partition(data, pivot, left, right);
  int size_min = sizes.first;
  int size_min_equal = sizes.second;
  if (k_ordinal <= size_min) {
    return QuickSelect(data, k_ordinal, left, size_min);
  }
  if (k_ordinal <= size_min_equal) {
    return pivot;
  }
  return QuickSelect(data, k_ordinal, size_min_equal + 1, right);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int quantity;
  int k_ordinal;
  std::cin >> quantity >> k_ordinal;
  std::vector<long long int> data;
  for (int i = 0; i < quantity; ++i) {
    long long int value;
    std::cin >> value;
    data.push_back(value);
  }
  std::cout << QuickSelect(data, k_ordinal, 0, data.size() - 1);
  return 0;
}