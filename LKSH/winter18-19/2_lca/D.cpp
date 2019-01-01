#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;
vector<int> used;
int t = 0;
set<pair<int, int>> ans;

vector<int> dfs(int v) {
  used[v] = t;
  vector<int> arr;
  ans.insert({v, v});
  for (int i = 0; i < g[v].size(); ++i) {
    int u = g[v][i];
    if (used[u] != t) {
      auto ret = dfs(u);
      for (auto x : ret) {
        arr.push_back(x);
      }
    }
  }
  for (int x : arr) {
    ans.insert({v, x});
    ans.insert({x, v});
  }
  arr.push_back(v);
  return arr;
}

int main() {
  long long n, m;
  cin >> n >> m;
  g.resize(n);
  used.resize(n);
  for (int i = 0; i < m; ++i) {
    int from, to;
    cin >> from >> to;
    from--;
    to--;
    g[from].push_back(to);
  }

  // long long cnt = 0;
  for (int i = 0; i < n; ++i) {
    t += 1;
    auto ret = dfs(i);
    for (int x : ret) {
      ans.insert({i, x});
      ans.insert({x, i});
    }
  }
  cout << ans.size() << '\n';

  return 0;
}