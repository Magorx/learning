#include <bits/stdc++.h>
using namespace std;

vector<int> used;
vector<vector<int>> g;
vector<int> match;
int t = 0;
int n, m;

bool dfs(int v) {
  if (used[v] == t) {
    return false;
  }
  used[v] = t;
  for (int u : g[v]) {
    if (match[u] == -1 || dfs(match[u])) {
      match[u] = v;
      match[v] = u;
      return true;
    }
  }
  return false;
}
bool dfs2(int v);

bool dfs3(int v) {
  if (used[v] == t) {
    return false;
  }
  used[v] = t;
  // cout << v << "!\n";
  if (match[v] != -1) {
    dfs2(match[v]);
  }
  return false;
}

bool dfs2(int v) {
  if (used[v] == t) {
    return false;
  }
  used[v] = t;
  // cout << v << "!\n";
  for (int u : g[v]) {
    dfs3(u);
  }
  return false;
}

int main() {
  cin >> n >> m;
  g.resize(n + m + 1);
  used.resize(n + m + 1);
  match.resize(n + m + 1, -1);
  int v, u;
  while(cin >> v >> u) {
    v--;
    u--;
    g[v].push_back(n + u);
    g[n + u].push_back(v);
  }

  for (int i = 0; i < n; ++i) {
    t += 1;
    dfs(i);
  }
  /*for (auto x : match) {
    cout << x << ' ';
  }
  cout << '\n';*/

  t += 5;
  for (int i = 0; i < n; ++i) {
    if (match[i] == -1) {
      // cout << i << "!\n";
      dfs2(i);
    }
  }

  /*for (auto z : used) {
    cout << z << ' ';
  }
  cout << '\n';*/

  vector<int> ans1;
  vector<int> ans2;

  for (int i = 0; i < n + m; ++i) {
    if (i < n && used[i] != t) {
      ans1.push_back(i + 1);
    } else if (i >= n && used[i] == t) {
      ans2.push_back(i + 1);
    }
  }

  cout << ans1.size() + ans2.size() << '\n' << ans1.size() << ' ' << ans2.size() << '\n';
  for (auto x : ans1) {
    cout << x << ' ';
  }
  cout << '\n';

  for (auto x : ans2) {
    cout << x - n << ' ';
  }
  cout << '\n';

  return 0;  
}