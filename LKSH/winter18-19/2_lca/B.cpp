#include <bits/stdc++.h>

using namespace std;

const int l = 25;

vector<int> tin, tout;
int timer;

vector<vector<pair<int, int>>> g;

vector<vector<int>> dp;
vector<vector<int>> jump;
vector<int> edge_to;

int dfs(int v, int parent = 0) {
  tin[v] = ++timer;
  jump[v][0] = parent;
  dp[v][0] = edge_to[v];
  for (int i = 1; i <= l; ++i) {
    jump[v][i] = jump[jump[v][i - 1]][i - 1];
    dp[v][i] = dp[jump[v][i - 1]][i - 1];
  }

  for (int i = 0; i < g[v].size(); ++i) {
    int u = g[v][i].first;
    dfs(u, v);
  }

  tout[v] = ++timer;
  return 0;
}

bool predok(int v, int u) {
  return tin[v] <= tin[u] && tout[v] >= tout[u];
}

int lca(int v, int u) {
  if (predok(v, u)) {
    return v;
  }
  if (predok(u, v)) {
    return u;
  }

  for (int i = l; i >= 0; --i) {
    if (!predok(jump[v][i], u)) {
      v = jump[v][i];
    }
  }
  return jump[v][0];
}

int min_edge(int v, int u) {
  int init_v = v;
  int init_u = u;
  int minedge = 1e9;
  // int lca_vertex = lca(v, u);
  for (int i = l; i >= 0; --i) {
    if (!predok(jump[v][i], init_u)) {
      minedge = min(minedge, dp[v][i]);
      v = jump[v][i];
    }
  }
  minedge = min(minedge, dp[v][0]);
  for (int i = l; i >= 0; --i) {
    if (!predok(jump[u][i], init_v)) {
      minedge = min(minedge, dp[u][i]);
      u = jump[u][i];
    }
  }
  minedge = min(minedge, dp[u][0]);
  return minedge;
}

int main() {
  long long n;
  cin >> n;
  g.resize(n);
  tin.resize(n);
  tout.resize(n);
  jump.resize(n);
  edge_to.resize(n);
  dp.resize(n);
  for (int i = 0; i < n; ++i) {
    jump[i].resize(l + 1);
    dp[i].resize(l + 1);
  }

  for (int i = 0; i < n - 1; ++i) {
    int parent, cost;
    cin >> parent >> cost;
    parent--;
    g[parent].push_back({i + 1, cost});
    edge_to[i + 1] = cost;
  }

  dfs(0);

  int m;
  cin >> m;
  for (int i = 0; i < m; ++i) {
    int v, u;
    cin >> v >> u;
    v--;
    u--;
    cout << min_edge(v, u) << '\n';
  }

  return 0;
}