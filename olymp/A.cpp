#include <bits/stdc++.h>
using namespace std;

bool col(vector<vector<long long>>& arr, int c, int x) {
  if (!x) return true;
  bool to_ret = true;
  for (int i = 0; i < arr.size(); ++i) {
    arr[i][c] -= x;
    if (arr[i][c] < 0) {
      to_ret =  false;
    }
  }
  return to_ret;
}

bool roww(vector<vector<long long>>& arr, int r, int x) {
  if (!x) return true;
  bool to_ret = true;
  for (int i = 0; i < arr[0].size(); ++i) {
    arr[r][i] -= x;
    if (arr[r][i] < 0) {
      to_ret =  false;
    }
  }
  return to_ret;
}

int min_delta = 1e9;
int min_x = -1;
int min_y = -1;

vector<string> get_ans(vector<vector<long long>>& arr, int to_column) {
  vector<string> ans;
  vector<vector<long long>> arr_cp = arr;
  int n = arr.size();
  int m = arr[0].size();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cout << arr[i][j] << ' ';
    }
    cout << '\n';
  }
  if (to_column) {
      ans.push_back("C " + to_string(min_y + 1)  + ' ' + to_string(arr[min_x][min_y]) + '\n');
    }

    bool ret = col(arr_cp, min_y, min_delta);
    if (!ret) {
      return {};
    }

    for (int row = 0; row < n; ++row) {
      if (arr_cp[row][min_y]) {
        ans.push_back("R " + to_string(row + 1)  + ' ' + to_string(arr[row][min_y]) + '\n');
        bool ret = roww(arr_cp, row, arr[row][min_y]);
        if (!ret) {
          roww(arr_cp, row, arr[row][min_y]);
          ans.pop_back();
        }
      }
    }
    
    for (int column = 0; column < m; ++column) {
      int first = -1;
      for (int row = 0; row < n; ++row) {
        if (first < 0) {
          first = arr_cp[row][column];
        } else if (first != arr_cp[row][column]) {
          return {};
        }
      }
      if (first > 0)
        ans.push_back("C " + to_string(column + 1)  + ' ' + to_string(first) + '\n');
        col(arr_cp, column, first);
    }

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cout << arr_cp[i][j] << ' ';
      }
      cout << '\n';
    }
    return ans;
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<long long>> arr1(n, vector<long long>(m, 0));
  vector<vector<long long>> arr2(n, vector<long long>(m, 0));
  vector<vector<long long>> arr(n, vector<long long>(m, 0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> arr1[i][j];
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> arr2[i][j];
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      arr[i][j] = arr2[i][j] - arr1[i][j];
      if (arr[i][j] < 0) {
        cout << -1 << '\n';
        return 0;
      }
      if (arr[i][j] < min_delta) {
        min_delta = arr[i][j];
        min_x = i;
        min_y = j;
      }
    }
  }

  vector<string> ans;
  for (int to_column = 0; to_column <= min_delta; ++to_column) {
    ans = get_ans(arr, to_column);
    if (ans.size()) {
      break;
    }
  }
  
  if (ans.size() == 0) {
    cout << -1 << '\n';
    return 0;
  }

  cout << ans.size() << '\n';
  for (int i = 0; i < ans.size(); ++i) {
    cout << ans[i];
  }
}