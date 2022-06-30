#include <iostream>
#include <fstream>
 
void merge(int &inverse, int *&data, int begin_1, int end_1, int begin_2, int end_2) {
  int iter_1 = begin_1;
  int iter_2 = begin_2;
  int dop_invers = 0;
  int *help = new int[end_2 - begin_1];
  int iter = 0;
  while (iter_1 < end_1) {
    while ((data[iter_2] < data[iter_1]) && (iter_2 < end_2)) {
      ++dop_invers;
      help[iter] = data[iter_2];
      ++iter;
      ++iter_2;
    }
    inverse += dop_invers;
    help[iter] = data[iter_1];
    ++iter;
    ++iter_1;
  }
  for (int i = begin_1, j = 0; j < iter; ++i, ++j) {
    data[i] = help[j];
  }
  delete[] help;
}
void merge_sort(int *&data, int size, int &inverse) {
  int step = 2;
  while (step / 2 < size) {
    int i = 0;
    for (; i < size / step; ++i) {
      merge(inverse, data, step * i, step * i + (step / 2), step * i + (step / 2), step * i + step);
    }
    if (size % step > (step / 2)) {
      merge(inverse, data, step * i, step * i + (step / 2),
            +step * i + (step / 2), size);
    }
    step *= 2;
  }
}
int main() {
  std::ofstream file_output ("inverse.out");
  std::ifstream file_input ("inverse.in");
  int quantity;
  file_input >> quantity;
  int *data = new int[quantity];
  for (int i = 0; i < quantity; ++i) {
    int element;
    file_input >> element;
    data[i] = element;
  }
  int inverse = 0;
  merge_sort(data, quantity, inverse);
  file_output << inverse << "\n";
  file_output.close();
  file_input.close();
  delete[] data; //
  return 0;
}