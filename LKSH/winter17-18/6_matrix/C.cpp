#include <iostream>
#include <vector>
#include <string>

const long long M = 1e9 + 7;

template<typename T>
using Row = std::vector<T>;

template<typename T>
using MatrixMap = std::vector<Row<T>>;

template <typename T>
T binpow(T obj, long long pow) {
  if (pow == 1) {
    return obj;
  } else {
    if (pow % 2) {
      return binpow(obj, pow - 1) * obj;
    } else {
      T tmp = binpow(obj, pow / 2);
      return tmp * tmp;
    }
  }
}

template <typename T>
struct Matrix {
  long long row_count;
  long long column_count;
  MatrixMap<T> matrix;

  Matrix() {
    row_count = 0;
    column_count = 0;
    matrix = {};
  }

  Matrix(long long _row_count, long long _column_count) {
    row_count = _row_count;
    column_count = _column_count;
    matrix = Row<Row<T>>(_row_count, Row<T>(_column_count, 0));
  }

  Matrix(long long _row_count, long long _column_count, const MatrixMap<T>& _matrix) {
    row_count = _row_count;
    column_count = _column_count;
    matrix = _matrix;
  }
};

template <typename T>
Matrix<T> operator*(const Matrix<T>& first, const Matrix<T>& second) {
  if (first.column_count != second.row_count) {
    return {0, 0, {}};
  }
  
  MatrixMap<T> resulting_matrix = std::vector<Row<T>> (first.column_count, Row<T>(second.row_count));
  Matrix<T> result(first.row_count, second.column_count);

  for (int i = 0; i < first.row_count; ++i) {
    for (int j = 0; j < second.column_count; ++j) {
      for (int k = 0; k < first.column_count; ++k) {
        result.matrix[i][j] += (first.matrix[i][k] * second.matrix[k][j]) % M;
      }
    }
  }
  return result;
}

template <typename T>
std::ostream& operator<<(std::ostream& output_stream, const Matrix<T>& matrix) {
  for (int i = 0; i < matrix.row_count; ++i) {
    for (int j = 0; j < matrix.column_count; ++j) {
      output_stream << matrix.matrix[i][j] << ' ';
    }
    output_stream << '\n';
  }
  return output_stream;
}

template <typename T>
std::istream& operator>>(std::istream& input_stream, Matrix<T>& matrix) {
  for (int i = 0; i < matrix.row_count; ++i) {
    for (int j = 0; j < matrix.column_count; ++j) {
      input_stream >> matrix.matrix[i][j];
    }
  }
  return input_stream;
}

int main() {
  freopen("three-ones.in", "r", stdin);
  freopen("three-ones.out", "w", stdout);
  long long n = 0;
  std::cin >> n;
  if (n == 1) {
    std::cout << 2 << '\n';
    return 0;
  }
  Matrix<long long> mat{3, 3, {{1, 1, 1}, {1, 0, 0}, {0, 1, 0}}};
  Matrix<long long> base{3, 1, {{1}, {1}, {0}}};
  Matrix<long long> res = binpow(mat, n - 1) * base;
  //std::cout << res;
  std::cout << (res.matrix[0][0] + res.matrix[1][0] + res.matrix[2][0]) % M << '\n';

  return 0;
}