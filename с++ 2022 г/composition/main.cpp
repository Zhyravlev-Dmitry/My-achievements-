#include <iostream>

long long FullEnumeration(int** data, int number_arrays, char** main_data,
                          int number_args, int* indexes) {
  long long answer = 0;
  if (number_args != 0) {
    int number = number_arrays - number_args;
    int quantity = std::stoi(main_data[number + 1]);
    for (int i = 0; i < quantity; ++i) {
      indexes[number] = i;
      answer += FullEnumeration(data, number_arrays, main_data, number_args - 1,
                                indexes);
    }
  } else {
    bool replay = false;
    for (int i = 0; !replay && (i < number_arrays - 1); ++i) {
      for (int j = i + 1; j < number_arrays; ++j) {
        if (indexes[i] == indexes[j]) {
          replay = true;
          break;
        }
      }
    }
    if (!replay) {
      long long product = 1;
      for (int i = 0; i < number_arrays; ++i) {
        product *= data[i][indexes[i]];
      }
      answer += product;
    }
  }
  return answer;
}

int main(int argc, char* argv[]) {
  int** data = new int*[argc - 1];
  int* indexes = new int[argc - 1];
  for (int number = 1; number < argc; ++number) {
    int quantity = std::stoi(argv[number]);
    data[number - 1] = new int[quantity];
    for (int i = 0; i < quantity; ++i) {
      int value;
      std::cin >> value;
      data[number - 1][i] = value;
    }
  }
  long long answer = FullEnumeration(data, argc - 1, argv, argc - 1, indexes);
  if (argc - 1 == 0) {
    answer = 0;
  }
  std::cout << answer << "\n";
  for (int number = 0; number < argc - 1; ++number) {
    delete[] data[number];
  }
  delete[] data;
  delete[] indexes;
  return 0;
}
