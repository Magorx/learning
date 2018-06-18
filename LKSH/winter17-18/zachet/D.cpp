#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int ans_x, ans_y;

int mex(std::vector<int>& arr) {
  if (!arr.size()) {
    return 0;
  } else if (arr[0] < 0) {
    return 0;
  }
  if (arr.size() == 1) {
    if (arr[0] == 0) {
      return 1;
    } else {
      return 0;
    }
  }
  std::vector<char> was(arr.size() + 100, 0);
  for (int i = 0; i < arr.size(); ++i) {
    was[arr[i]] = 1;
  }
  for (int i = 0; i < was.size(); ++i) {
    if (!was[i]) {
      return i;
    }
  }
  return -1;
}

std::vector<std::vector<int>> dp(100, std::vector<int>(100, -1));

int grandy(int n, int m, bool lvl = true) {
  // std::cout << "call with " << n << ' ' << m << '\n';
  if (n <= 0 || m <= 0) {
    // std::cout << "return 0\n";
    return 0;
  }
  if (dp[n][m] != -1) {
    return dp[n][m];
  } else if (dp[m][n] != -1) {
    return dp[m][n];
  }
  std::vector<int> children_grandies;
  int cur_ans = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      children_grandies.push_back(grandy(i - 1, j - 1, 0) ^ grandy(i - 1, m - j, 0) ^ grandy(n - i, j - 1, 0) ^ grandy(n - i, m - j, 0));
      cur_ans = mex(children_grandies);
      if (lvl && cur_ans) {
        ans_x = i;
        ans_y = j;
        return 1;
      }
    }
  }
  
  // std::cout << "returning " << mex(children_grandies) << '\n';
  dp[n][m] = mex(children_grandies);
  return dp[n][m];
}

int main() {
  // freopen("paper2.in", "r", stdin);
  // freopen("paper2.out", "w", stdout);
  int n, m;
  std::cin >> m >> n;
  if (grandy(m, n)) {
    std::cout << "Win.\n" << ans_x << ' ' << ans_y << '\n';
  } else {
    std::cout << "Loss.";
  }
  // for (int i = 0; i < dp.size(); ++i) {
  //   pv(dp[i]);
  // }
  return 0;
}