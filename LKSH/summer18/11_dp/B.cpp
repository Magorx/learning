#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string get_ans(const vector<vector<int>>& dp, const string& s1, const string& s2, int i, int j, int l) {
  string ret = "";
  while (ret.length() < l) {
    if (s1[i - 1] == s2[j - 1]) {
      ret += s2[j - 1];
      --i;
      --j;
    } else {
      if (dp[i - 1][j] >= dp[i][j - 1]) {
        --i;
      } else {
        --j;
      }
    }
  }
  reverse(ret.begin(), ret.end());
  return ret;
}

string max_shared_part(string first, string second) {
  int l1 = first.length();
  int l2 = second.length();
  vector<vector<int>> dp(l1 + 1, vector<int>(l2 + 1, 0));
  for (int i = 1; i <= l1; ++i) {
    for (int j = 1; j <= l2; ++j) {
      if (first[i - 1] == second[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      }
      dp[i][j] = max(dp[i][j], dp[i][j - 1]);
      dp[i][j] = max(dp[i][j], dp[i - 1][j]);
    }
  }

  /* for (int i = 0; i < dp.size(); ++i) {
    for (int j = 0; j < dp[1].size(); ++j) {
      cout << dp[i][j] << ' ';
    }
    cout << '\n';
  } */

  string ans = get_ans(dp, first, second, l1, l2, dp[dp.size() - 1][dp[0].size() - 1]);
  return ans;
}

int main() {
  string first, second;
  cin >> first >> second;
  string ret = max_shared_part(first, second);
  cout << ret << "\n";

  return 0;
}