#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int mex(std::vector<int>& arr) {
  std::vector<char> was(arr.size() + 2, 0);
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

int vexor(std::vector<int> arr) {
  int a = 0;
  for (int i = 0; i < arr.size(); ++i) {
    a ^= arr[i];
  }
  return a;
}

std::vector<std::vector<int>> dp(1000, std::vector<int>(1000, -1));

int grandy(int n, int m, int s) {
  // std::cout << "call with " << n << ' ' << m << '\n';
  if ((n <= 1 && m <= s) || (m <= 1 && n <= s)) {
    // std::cout << "return 0\n";
    return 0;
  }
  if (dp[n][m] != -1) {
    return dp[n][m];
  }
  std::vector<int> children_grandies;
  for (int i = 1; i <= n - 1; ++i) {
    children_grandies.push_back(grandy(n - i, m, s) ^ grandy(i, m, s));
  }
  for (int j = 1; j <= m - 1; ++j) {
    children_grandies.push_back(grandy(n, m - j, s) ^ grandy(n, j, s));
  }
  
  // std::cout << "returning " << mex(children_grandies) << '\n';
  dp[n][m] = mex(children_grandies);
  return dp[n][m];
}

int main() {
  freopen("choco.in", "r", stdin);
  freopen("choco.out", "w", stdout);
  long long n, m, s;
  std::cin >> n >> m >> s;

  if (grandy(n, m, s)) {
    std::cout << 1 << '\n';
  } else {
    std::cout << 2 << '\n';
  }

  return 0;
}