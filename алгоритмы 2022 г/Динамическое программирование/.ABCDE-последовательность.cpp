#include <iostream>
#include <vector>

template<uint64_t M, uint64_t N = M>
class Matrix {
 public:

  Matrix() {
    std::vector<long long> line(N, 0);

    for (uint64_t i = 0; i < M; ++i) {
      line[i] = (1);
      data.push_back(line);
      line[i] = (0);
    }
  }

  template<class T>
  Matrix(std::vector<std::vector<T>> data_value) {
    std::vector<long long> line(N);
    data.resize(M);
    for (uint64_t i = 0; i < M; ++i) {
      for (uint64_t j = 0; j < N; ++j) {
        line[j] = data_value[i][j];
      }
      data[i] = line;
    }
  }

  void swap(uint64_t line_1, uint64_t line_2) {
    for (uint64_t j = 0; j < data.size(); ++j) {
      std::swap(data[j][line_1], data[j][line_2]);
    }
  }

  std::vector<long long> &operator[](const int i) {
    return data[i];
  }

 public:
  std::vector<std::vector<long long>> data;
};

template<uint64_t N>
class SquareMatrix : public Matrix<N, N> {
 public:
  SquareMatrix<N>() : Matrix<N, N>() {}

  SquareMatrix<N>(std::vector<std::vector<long long>> c) : Matrix<N, N>(c) {}
};

template<uint64_t M, uint64_t N>
Matrix<M, N> &operator*=(Matrix<M, N> &matrix, const long long a) {
  for (uint64_t i = 0; i < matrix.data.size(); ++i) {
    for (uint64_t j = 0; j < matrix.data[0].size(); ++j) {
      matrix.data[i][j] *= a;
    }
  }
  return matrix;
};

template<uint64_t M, uint64_t N, uint64_t K>
Matrix<M, K> operator*(const Matrix<M, N> first, const Matrix<N, K> &another) {
  long long sum = 0;
  Matrix<M, K> mat;
  for (uint64_t i = 0; i < first.data.size(); ++i) {
    for (uint64_t j = 0; j < another.data[0].size(); ++j) {
      for (uint64_t k = 0; k < first.data[0].size(); ++k) {
        sum += first.data[i][k] * another.data[k][j] ;
      }
      mat[i][j] = sum % 999999937;
      sum = 0;
    }
  }
  return mat;
}

template<uint64_t M, uint64_t N, uint64_t K>
Matrix<M, K> &operator*=(Matrix<M, N> &first, const Matrix<N, K> &another) {
  first = first * another;
  return first;
}

Matrix<5> power(Matrix<5> &matrix, long long n ) {
  if (n == 1) {
    return matrix;
  }

  if (n % 2 == 0) {
    Matrix<5> tmp = power(matrix, n / 2);
    tmp *= tmp;
    return tmp;
  }

  Matrix<5> intermediary = power(matrix, n / 2);
  intermediary *= intermediary;
  intermediary *= matrix;
  return intermediary;
}

long long solution(SquareMatrix<5> &matrix, long long n) {
  std::vector<std::vector<long long>> intermediary(5, std::vector<long long> (5, 0));
  Matrix<5> result(intermediary);
  result = power(matrix, n);
  long long sum = 0;
  for (int i = 0; i < 5; ++i)
    for (int j = 0; j < 5; ++j) {
      sum += result[i][j];
    }
  sum %= 999999937;
  return sum;
}

int main() {
  std::vector<std::vector<long long>> base(5, std::vector<long long> (5, 1));
  base[2][3] = 0;
  base[2][4] = 0;
  base[4][3] = 0;
  base[4][4] = 0;
  long long n;
  SquareMatrix<5> matrix(base);

  std::cin >> n;
  while (n != 0) {
    if (n == 1) {
      std::cout << 5 << "\n";
    } else{
      std::cout << solution(matrix, n-1) << "\n";
    }
    std::cin >> n;
  }
  return 0;
}