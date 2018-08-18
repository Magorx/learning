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
  cin >> s;
  int n = s.length();
  reverse(s.begin(), s.end());
  vector<int> z = z_func(s);
  for (int i = 1; i < z.size(); ++i) {
    if (z[i] + i == n) {
      cout << i << '\n';
      return 0;
    }
  }
  cout << n << '\n';

  return 0;
}