#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<int> z_func(string s) {
  vector<int> z(s.length(), 0);
  int l = 0;
  int r = 0;
  for (int i = 1; i < s.length(); ++i) {
    if (i <= r) {
      z[i] = min(z[i - l], r - i + 1);
    }
    while (z[i] + i < s.length() && s[z[i]] == s[z[i] + i]) {
      ++z[i];
    }
    if (i + z[i] - 1 > r) {
      l = i;
      r = i + z[i] - 1;
    }
  }
  z[0] = s.length();

  return z;
}

int main() {
  string s;
  int n;
  cin >> n;
  cin >> s;
  auto ret = z_func(s);
  reverse(ret.begin(), ret.end());
  for (auto x : ret) {
    cout << x << ' ';
  }
  cout << '\n';
}