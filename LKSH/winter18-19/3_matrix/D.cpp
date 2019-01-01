#include <bits/stdc++.h>
using namespace std;

template<typename T>
using Row = vector<T>;

template<typename T>
using MatrixMap = vector<Row<T>>;

long double M;


template <typename T>
struct Matrix {
  long double row_count;
  long double column_count;
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

  vector<T>& operator[](T index) {
    return matrix[index];
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

Matrix<long double> zeroMatrix(int n) {
  Matrix<long double> mat(n, n);
  for (int i = 0; i < n; ++i) {
    mat.matrix[i][i] = 1;
  }
  return mat;
}

const int ONE = 1;
const int INF = 2;
const int ZERO = 3;

long long gcd(long long a, long long b) {
  while (b) {
    swap(a, b);
    b = a % b;
  }
  return a;
}

long long GCD(vector<long long>& arr) {
  long long ans = arr[0];
  for (int i = 0; i < arr.size(); ++i) {
    ans = gcd(ans, arr[i]);
  }
  return ans;
}

template <typename T>
pair<int, vector<long double>> zareshat(Matrix<T> a, Matrix<T> b) {
  int row = 0;
  int column = 0;
  int can_be_free = 0;
  while (row < a.row_count && column < a.column_count) {
    bool free = true;
    long double minimum = 10000000000;
    int min_index = -1;
    for (int i = row; i < a.row_count; ++i) {
      if (a[i][column] != 0) {
        free = false;
        if (abs(minimum) > abs(a[i][column])) {
          minimum = a[i][column];
          min_index = i;
        }
      }
    }
    if (!free) {
      swap(a[min_index], a[row]);
      swap(b[min_index], b[row]);
      // cout << "r = " << row << " c = " << column << '\n';
      for (int j = 0; j < a.row_count; ++j) {
        if (j != row) {
          int t = a[j][column];
          for (int k = 0; k < a.column_count; ++k) {
            a[j][k] = a[j][k] * a[row][column] - a[row][k] * t;
          }
          b[j][0] = b[j][0] * a[row][column] - b[row][0] * t;
        }
      }
      row++;
    } else {
      can_be_free += 1;
    }
    column++;
  }
  while (row < a.row_count) {
    if (b[row][0] != 0) {
      return {ZERO, {}};
    }
    row++;
  }
  if (can_be_free) {
    return {INF, {}};
  }

  vector<long double> ans(a.column_count);
  for (int i = 0; i < a.column_count; ++i) {
    ans[i] = b[i][0] / a[i][i];
  }
  return {ONE, ans};
}

int main() {
  int n;
  cin >> n;
  Matrix<long double> a(n, n);
  Matrix<long double> b(n, 1);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> a.matrix[i][j];
    }
    cin >> b.matrix[i][0];
  }
  auto ans = zareshat(a, b);
  int flag = ans.first;
  if (flag == ZERO) {
    cout << "impossible\n";
    return 0;
  } else if (flag == INF) {
    cout << "infinity\n";
    return 0;
  } else {
    cout << "single\n";
    for (long double x : ans.second) {
      cout << x << ' ';
    }
    cout << '\n';
  }

  return 0;
}