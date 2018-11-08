#include <bits/stdc++.h>

using namespace std;

vector<char> visited;
vector<vector<int>> g;
vector<vector<int>> ans;

void dfs(int v) {
  ans[ans.size() - 1].push_back(v);
  visited[v] = 1;
  for (int u : g[v]) {
    if (!visited[u]) {
      dfs(u);
    }
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  g.resize(n);
  visited.resize(n, 0);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    --a;
    --b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  for (int i = 0; i < n; ++i) {
    if (!visited[i]) {
      ans.push_back({});
      dfs(i);
    }
  }

  cout << ans.size() << '\n';
  for (auto vec : ans) {
    cout << vec.size() << '\n';
    for (auto x : vec) {
      cout << x + 1 << ' ';
    }
    cout << '\n';
  }

  return 0;
}