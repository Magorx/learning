#include <bits/stdc++.h>
using namespace std;

template<typename T>
using Row = vector<T>;

template<typename T>
using MatrixMap = vector<Row<T>>;

long long M;

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
    matrix = Row<Row<T>> (_row_count, Row<T>(_column_count, 0));
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
  
  MatrixMap<T> resulting_matrix = vector<Row<T>> (first.column_count, Row<T>(second.row_count));
  Matrix<T> result(first.row_count, second.column_count);

  for (long long i = 0; i < first.row_count; ++i) {
    for (long long j = 0; j < second.column_count; ++j) {
      for (long long k = 0; k < first.column_count; ++k) {
        result.matrix[i][j] = (result.matrix[i][j] + (first.matrix[i][k] * second.matrix[k][j]) % M) % M;
      }
    }
  }
  return result;
}

template <typename T>
ostream& operator<<(ostream& output_stream, const Matrix<T>& matrix) {
  for (long long i = 0; i < matrix.row_count; ++i) {
    for (long long j = 0; j < matrix.column_count; ++j) {
      output_stream << matrix.matrix[i][j] << ' ';
    }
    output_stream << '\n';
  }
  return output_stream;
}

template <typename T>
istream& operator>>(istream& input_stream, Matrix<T>& matrix) {
  for (long long i = 0; i < matrix.row_count; ++i) {
    for (long long j = 0; j < matrix.column_count; ++j) {
      input_stream >> matrix.matrix[i][j];
    }
  }
  return input_stream;
}

Matrix<long long> zeroMatrix(long long n) {
  Matrix<long long> mat(n, n);
  for (long long i = 0; i < n; ++i) {
    mat.matrix[i][i] = 1;
  }
  return mat;
}


Matrix<long long> binpow(Matrix<long long>& obj, long long pow) {
  if (pow <= 0) {
    return zeroMatrix(obj.row_count);
  }
  if (pow == 1) {
    return obj;
  } else {
    if (pow % 2) {
      return binpow(obj, pow - 1) * obj;
    } else {
      Matrix<long long> tmp = binpow(obj, pow / 2);
      return tmp * tmp;
    }
  }
}

int main() {
  long long n, k;
  cin >> k >> n;
  M = 1e9+7;
  Matrix<long long> shift(k + 1, k + 1);
  for (long long i = 0; i < k + 1; ++i) {
    for (long long j = i - 1; j <= i + 1; j += 2) {
      if (j >= 0 && j < k + 1) {
        shift.matrix[i][j] = 1;
      }
    }
  }
  // cout << shift << "\n";
  Matrix<long long> base(k + 1, 1);
  base.matrix[0][0] = 1;

  shift = binpow(shift, 2 * n);
  // cout << shift * base << "\n";

  cout << (shift * base).matrix[0][0] << '\n';
  
  return 0;
}