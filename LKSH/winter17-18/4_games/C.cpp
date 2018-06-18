#include <iostream>
#include <vector>
#include <string>

std::vector<std::vector<std::vector<int>>> dp (101, std::vector<std::vector<int>> (101, std::vector<int>(2, -1)));
std::vector<int> paper;

int cntdp(int l, int r, int player) {
  std::cout << "called with " << l << ' ' << r << ' ' << player << '\n';
  if (dp[l][r][player] != -1) {
    return dp[l][r][player];
  }
  if (l == r) {
    dp[l][r][player] = paper[l];
    dp[l][r][player ^ 1] = paper[l];
    return paper[l];
  }

  if (player == 1) {
    dp[l][r][player] = std::min(cntdp(l + 1, r, 0), cntdp(l, r - 1, 0));
  } else {
    dp[l][r][player] = std::max(cntdp(l + 1, r, 0), cntdp(l, r - 1, 0));
  }

  return dp[l][r][player];
  
}

int main() {
  int n = 0;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    int a = 0;
    std::cin >> a;
    paper.push_back(a);
  }

  std::cout << cntdp(0, paper.size() - 1, 0);

  return 0;
}