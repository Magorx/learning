#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;
vector<int> used;
long long ANS = 0;
vector<int> absolute_used;
vector<int> cnts;
vector<vector<int>> getable;
int t = 1;
set<pair<int, int>> ans;

vector<int> dfs(int v, int depth = 0) {
  used[v] = t;
  if (absolute_used[v]) {
    return getable[v];
  }
  vector<int> arr;
  for (int i = 0; i < g[v].size(); ++i) {
    int u = g[v][i];
    if (used[u] != t) {
      auto ret = dfs(u);
      for (auto x : ret) {
        arr.push_back(x);
      }
    }
  }
  
  for (int i = 0; i < arr.size(); ++i) {
    for (int j = i + 1; j < arr.size(); ++j) {
      ans.insert({arr[i], arr[j]});
      ans.insert({arr[j], arr[i]});
    }
  }
  for (int x : arr) {
    ans.insert({v, x});
    ans.insert({x, v}); 
  }

  absolute_used[v] = 1;
  getable[v] = arr;
  arr.push_back(v);
  return arr;
}

int main() {
  long long n, m;
  cin >> n >> m;

  g.resize(n);
  getable.resize(n);
  used.resize(n);
  absolute_used.resize(n, 0);
  cnts.resize(n);
  for (int i = 0; i < m; ++i) {
    int from, to;
    cin >> from >> to;
    from--;
    to--;
    g[from].push_back(to);
  }

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