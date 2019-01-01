#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;
vector<int> used;
vector<int> absolute_used;
vector<vector<int>> getable;
set<pair<int, int>> ans;
int t = 1;

vector<int> dfs(int v, int depth = 0) {
  if (absolute_used[v]) {
    return getable[v];
  }
  used[v] = t;

  vector<vector<int>> arr;
  vector<int> can_get;

  for (int u : g[v]) {
    if (used[u] != t) {
      vector<int> ret = dfs(u, depth + 1);
      arr.push_back(ret);
      for (int x : ret) {
        can_get.push_back(x);
        ans.insert({v, x});
        ans.insert({x, v});
      }
    }
  }

  for (int i = 0; i < arr.size(); ++i) {
    for (int j = 0; j < arr.size(); ++j) {
      for (int z : arr[i]) {
        for (int y : arr[j]) {
          ans.insert({z, y});
          ans.insert({y, z});
        }
      }
    }
  }

  can_get.push_back(v);
  if (depth == 0) {
    getable[v] = can_get;
    absolute_used[v] = 1;
  }
  return can_get;
}

int main() {
  int n, m;
  cin >> n >> m;

  g.resize(n);
  used.resize(n);
  absolute_used.resize(n);
  getable.resize(n);

  for (int i = 0; i < m; ++i) {
    int from, to;
    cin >> from >> to;
    from--;
    to--;
    g[from].push_back(to);
  }

  for (int i = 0; i < n; ++i) {
    t += 1;
    dfs(i);
    ans.insert({i, i});
  }

  cout << ans.size() << '\n';
  return 0;
}