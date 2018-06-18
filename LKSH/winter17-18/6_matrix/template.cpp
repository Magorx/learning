#include <iostream>
#include <vector>
#include <string>

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
      pow -= 1;
      return binpow(obj, pow);
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
    matrix = Row<Row<int>> (_row_count, Row<int>(_column_count, 0));
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
        result.matrix[i][j] += first.matrix[i][k] * second.matrix[k][j];
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
  freopen("mmul.in", "r", stdin);
  freopen("mmul.out", "w", stdout);
  int a, b, c;
  std::cin >> a >> b >> c;
  MatrixMap<int> mm = Row<Row<int>>(a, Row<int>(b, 0));
  Matrix<int> m1(a, b);
  Matrix<int> m2(b, c);
  std::cin >> m1 >> m2;
  std::cout << m1 * m2;

  return 0;
}