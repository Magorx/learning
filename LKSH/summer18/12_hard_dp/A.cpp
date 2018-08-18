#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

template <typename T>
bool relax(T& first, T second) {
  if (first < second) {
    first = second;
    return true;
  } else {
    return false;
  }
}

long long max_pair_sochetanie(int n, vector<vector<char>>& graph) {
  vector<long long> dp(pow(2, n), 0);
  for (int mask = 0; mask < pow(2, n); ++mask) {
    for (int j = 0; j < n; ++j) {
      if ((mask & (1 << j)) == 0) {
        relax(dp[mask | (1 << j)], dp[mask]);
        for (int k = 0; k < n; ++k) {
          if (((mask & (1 << k)) == 0) && (graph[j][k] == 'Y')) {
            relax(dp[mask | (1 << j) | (1 << k)], dp[mask] + 1);
          }
        }
        break;
      }
    }
  }
  return dp[pow(2, n) - 1];
}

int main() {
  int n;
  cin >> n;
  vector<vector<char>> graph(n, vector<char>(n, 0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> graph[i][j];
    }
  }

  cout << max_pair_sochetanie(n, graph) * 2 << '\n';

  return 0;
}