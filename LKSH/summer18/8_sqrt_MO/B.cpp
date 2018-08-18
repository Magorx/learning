#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>

using namespace std;

struct Query {
  char type;
  int v;
  int u;
};

int n, m;
int k;
vector<int> used;
vector<int> used_compressed;
vector<vector<char>> deleted;
int t = 1;
vector<vector<int>> g;
vector<vector<int>> g_compressed;
vector<vector<char>> component_edges;
vector<int> colors;
set<pair<int, int>> baned_from_use;
vector<Query> queries;

void compress(int v, int color) {
  used[v] = t;
  colors[v] = color;
  for (int i = 0; i < (int)g[v].size(); ++i) {
    cout << deleted[v][g[v][i]] << "!!\n";
    if (used[g[v][i]] != t && baned_from_use.find({v, g[v][i]}) != baned_from_use.end() && !deleted[v][g[v][i]]) {
      cout << "dfs " << v << " -> " << g[v][i] << '\n';
      g_compressed[v].push_back(g[v][i]);
      compress(g[v][i], color);
    }
  }
}

void dfs_compressed(int v) {
  // cout << "dfs_comp " << v << '\n';
  used_compressed[v] = t;
  for (int i = 0; i < (int)g_compressed[v].size(); ++i) {
    if (used_compressed[g_compressed[v][i]] != t && component_edges[v][g[v][i]]) {
      cout << "dfs " << v << " -> " << g_compressed[v][i] << '\n';
      dfs_compressed(g_compressed[v][i]);
    }
  }
}

int main() {
  cin >> n >> m;
  k = sqrt(n + m);
  g.resize(n, vector<int>(0));
  deleted.resize(n, vector<char>(n, 0));
  component_edges.resize(n, vector<char>(n, 0));
  used.resize(n, 0);
  used_compressed.resize(n, 0);
  colors.resize(n);
  queries.resize(m);
  for (int i = 0; i < m; ++i) {
    char type;
    int v = -1;
    int u = -1;
    cin >> type;
    if (type != '?') {
      cin >> v >> u;
      --v;
      --u;
    }
    queries[i].type = type;
    queries[i].v = v;
    queries[i].u = u;
  }

  for (int i = 0; i < (m + k - 1) / k; ++i) {
    ++t;
    baned_from_use.clear();
    g_compressed.clear();
    g_compressed.resize(n);
    colors.clear();
    colors.resize(n, -1);
    for (int j = 0; j < k && i * k + j < m; ++j) {
      int v = queries[i * k + j].v;
      int u = queries[i * k + j].u;
      baned_from_use.insert({v, u});
      baned_from_use.insert({u, v});
    }
    for (int s = 0; s < n; ++s) {
      if (used[s] != t) {
        compress(s, i);
      }
    } 
    for (int j = 0; j < k && i * k + j < m; ++j) {
      ++t;
      char type = queries[i * k + j].type;
      if (type == '+') {
        int v = queries[i * k + j].v;
        int u = queries[i * k + j].u;
        deleted[v][u] = 0;
        deleted[v][u] = 0;
        ++component_edges[v][u];
        ++component_edges[v][u];
        g[v].push_back(u);
        g[u].push_back(v);
        g_compressed[colors[v]].push_back(colors[u]);
        g_compressed[colors[u]].push_back(colors[v]);
      } else if (type == '-') {
        int v = queries[i * k + j].v;
        int u = queries[i * k + j].u;
        deleted[v][u] = 1;
        deleted[u][v] = 1;
        --component_edges[v][u];
        --component_edges[u][v];
      } else if (type == '?') {
        for (int a = 0; a < n; ++a) {
          for (int aa = 0; aa < g_compressed[a].size(); ++aa) {
            cout << g_compressed[a][aa] << ' ';
          }
          cout << '\n';
        }
        cout << "\n";
        int cnt = 0;
        for (int s = 0; s < n; ++s) {
          // cout << "s = " << s << '\n';
          if (used_compressed[s] != t) {
            ++cnt;
            dfs_compressed(s);
          }
        }
        cout << cnt << '\n';
      }
    }
  }

  return 0;
}