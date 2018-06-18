#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int ans_x, ans_y;

template <typename T>
void pv(std::vector<T>& v) {
  for (int i = 0; i < v.size(); ++i) {
    std::cout << v[i] << std::endl;
  }
}

int mex(std::vector<int>& arr) {
  if (!arr.size()) {
    return 0;
  } else if (arr[0] < 0) {
    return 0;
  }
  // if (arr.size() == 1) {
  //   if (arr[0] == 0) {
  //     return 1;
  //   } else {
  //     return 0;
  //   }
  // }
  std::vector<int> was(arr.size() + 100, 0);
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

std::vector<std::vector<int>> dp(1000, std::vector<int>(1000, -1));

int grandy(int n, int m, bool lvl = true) {
  // std::cout << "call with " << n << ' ' << m << '\n';
  if (n <= 0 || m <= 0) {
    // std::cout << "return 0\n";
    return 0;
  }

  if (n > m) {
    std::swap(n, m);
  }

  if (dp[n][m] != -1) {
    return dp[n][m];
  }

  std::vector<int> children_grandies;
  int cur_ans = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      children_grandies.push_back(grandy(i - 1, j - 1, 0) ^ grandy(i - 1, m - j, 0) ^ grandy(n - i, j - 1, 0) ^ grandy(n - i, m - j, 0));
      cur_ans = mex(children_grandies);
      if (lvl & cur_ans) {
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
  int n, m;
  std::cin >> m >> n;
  if (grandy(m, n)) {
    std::cout << "Win.\n" << ans_x << ' ' << ans_y << '\n';
  } else {
    std::cout << "Loss.";
  }
  return 0;
}

  // if (false) {
  //   std::cout << "{";
  //   for (int i = 0; i < dp.size(); ++i) {
  //     std::cout << '{';
  //     for (int j = 0; j < dp[i].size(); ++j) {
  //       std::cout << dp[i][j] << ',';
  //     }
  //     std::cout << "},\n";
  //   }
  //   std::cout << '}' << '\n';
  // }

  // std::cout << "\n\n\n";

  // if (false) {
  //   std::cout << "{";
  //   for (int i = 0; i < anses.size(); ++i) {
  //     std::cout << '{';
  //     for (int j = 0; j < anses[i].size(); ++j) {
  //       std::cout << '{' << anses[i][j].first << ',' << anses[i][j].second << "},";
  //     }
  //     std::cout << "},\n";
  //   }
  //   std::cout << '}' << '\n';
  // }
