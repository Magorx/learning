#include <bits/stdc++.h>
using namespace std;

template<typename T>
using Row = vector<T>;

template<typename T>
using MatrixMap = vector<Row<T>>;

long long M;

template <typename T>
T binpow(T& obj, long long pow) {
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

  Matrix(int _row_count, int _column_count) {
    row_count = _row_count;
    column_count = _column_count;
    matrix = Row<Row<T>> (_row_count, Row<T>(_column_count, 0));
  }

  Matrix(int _row_count, int _column_count, const MatrixMap<T>& _matrix) {
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

  for (int i = 0; i < first.row_count; ++i) {
    for (int j = 0; j < second.column_count; ++j) {
      for (int k = 0; k < first.column_count; ++k) {
        result.matrix[i][j] = (result.matrix[i][j] + (first.matrix[i][k] * second.matrix[k][j])) % M;
      }
    }
  }
  return result;
}

template <typename T>
bool operator==(const Matrix<T>& first, const Matrix<T>& second) {
  if (first.row_count != second.row_count || first.column_count != second.column_count) {
    return false;
  }
  for (int i = 0; i < first.row_count; ++i) {
    for (int j = 0; j < first.column_count; ++j) {
      if (first.matrix[i][j] != second.matrix[i][j]) {
        return false;
      }
    }
  }
  return true;
}

template <typename T>
ostream& operator<<(ostream& output_stream, const Matrix<T>& matrix) {
  for (int i = 0; i < matrix.row_count; ++i) {
    for (int j = 0; j < matrix.column_count; ++j) {
      output_stream << matrix.matrix[i][j] << ' ';
    }
    output_stream << '\n';
  }
  return output_stream;
}

template <typename T>
istream& operator>>(istream& input_stream, Matrix<T>& matrix) {
  for (int i = 0; i < matrix.row_count; ++i) {
    for (int j = 0; j < matrix.column_count; ++j) {
      input_stream >> matrix.matrix[i][j];
    }
  }
  return input_stream;
}

Matrix<long long> zeroMatrix(int n) {
  Matrix<long long> mat(n, n);
  for (int i = 0; i < n; ++i) {
    mat.matrix[i][i] = 1;
  }
  return mat;
}

vector<int> to_bin(int n) {
  vector<int> ret;
  // cout << n << " = [";
  while (n) {
    ret.push_back(n % 2);
    n /= 2;
  }
  /*for (auto x : ret) {
    cout << x;
  }
  cout << "]\n";*/
  return ret;
}

Matrix<int> mask_to_matrix(int mask) {
  auto masked = to_bin(mask);
  while (masked.size() < 16) {
    masked.push_back(0);
  }
  Matrix<int> ret(4, 4);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      ret.matrix[i][j] = masked[i * 4 + j];
    }
  }
  return ret;
}

int main() {
  M = 2;
  Matrix<int> matrix(4, 4);
  cin >> matrix;
  for (int i = 0; i < (1 << 16); ++i) {
    Matrix<int> tmp = mask_to_matrix(i);
    if (tmp * tmp == matrix) {
      cout << tmp;
      return 0;
    } 
  }
  cout << "NO SOLUTION\n";

  return 0;
}