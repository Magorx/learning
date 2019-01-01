#include <bits/stdc++.h>

using namespace std;
vector<vector<vector<int>>> g;

int main() {
  string s;
  cin >> s;
  int n, m, k;
  cin >> n >> m >> k;
  vector<int> terminal(k);
  for (int i = 0; i < k; ++i) {
    cin >> terminal[i];
    terminal[i] -= 1;
  }

  g.resize(n);
  for (int i = 0; i < n; ++i) {
    g[i].resize(256, vector<int>());
  }
  for (int i = 0; i < m; ++i) {
    int a, b;
    char c;
    cin >> a >> b >> c;
    a -= 1;
    b -= 1;
    g[a][c].push_back(b);
  }
  
  set<int> cur_states;
  set<int> new_states;
  cur_states.insert(0);
  for (int i = 0; i < s.length(); ++i) {
    // cout << i << ' ' << s[i] << '\n';
    char c = s[i];
    new_states.clear();
    for (int state : cur_states) {
      // cout << state << " " << c << '\n';
      for (int z = 0; z < g[state][c].size(); ++z) {
        new_states.insert(g[state][c][z]);  
      }
    }
    cur_states = new_states;
  }
  for (int i : cur_states) {
    for (int j : terminal) {
      if (i == j) {
        cout << "Accepts\n";
        return 0;
      }
    }
  }
  cout << "Rejects\n";

  return 0;
}