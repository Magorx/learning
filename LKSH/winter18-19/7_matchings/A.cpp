#include <bits/stdc++.h>
using namespace std;

vector<int> used;
vector<vector<int>> g;
vector<int> match;
int t = 0;

bool dfs(int v) {
  if (used[v] == t) {
    return false;
  }
  used[v] = t;
  for (int u : g[v]) {
    if (match[u] == -1 || dfs(match[u])) {
      match[u] = v;
      return true;
    }
  }
  return false;
}

int main() {
  int n, m;
  cin >> n >> m;
  g.resize(n);
  used.resize(n);
  match.resize(m, -1);
  for (int i = 0; i < n; ++i) {
    int u = 0;
    while (true) {
      cin >> u;
      if (!u) {
        break;
      }
      u--;
      g[i].push_back(u);
    }
  }

  for (int i = 0; i < n; ++i) {
    t += 1;
    dfs(i);
  }
  
  int ans = 0;
  for (int i = 0; i < m; ++i) {
    if (match[i] != -1) {
      ans += 1;
    }
  }
  cout << ans << '\n';
  for (int i = 0; i < m; ++i) {
    if (match[i] != -1) {
      cout << match[i] + 1 << ' ' << i + 1 << '\n';
    }
  }
}