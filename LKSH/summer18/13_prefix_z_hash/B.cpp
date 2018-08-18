#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<int> prefix(string s) {
  vector<int> p(s.length(), 0);
  for (int i = 0; i < s.length() - 1; ++i) {
    int j = p[i];
    while (j > 0 && s[j] != s[i + 1]) {
      j = p[j - 1];
    }
    if (s[j] == s[i + 1]) {
      p[i + 1] = j + 1;
    } else {
      p[i + 1] = 0;
    }
  }

  return p;
}

int main() {
  string s;
  cin >> s;
  for (auto x : prefix(s)) {
    cout << x << ' ';
  }
  cout << '\n';
}