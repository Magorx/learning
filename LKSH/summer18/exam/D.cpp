#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<int> dsu;
vector<int> dsu_size;

int get(int v) {
  if (dsu[v] == v) {
    return v;
  } else {
    return dsu[v] = get(dsu[v]);
  }
}

void add(int first, int second) {
  first = get(first);
  second = get(second);
  if (dsu_size[first] > dsu_size[second]) {
    dsu[second] = first;
    dsu_size[first] += dsu_size[second];
  } else {
    dsu[first] = second;
    dsu_size[second] += dsu_size[first];
  }
}

vector<vector<int>> g;
vector<int> visited;
int n;

bool megaflag = false;

void dfs(int v, int bus) {
  visited[v] = 1;
  if (bus == 0) {
    add(v, n + 1);
  } else {
    add(v, n + 2);
  }
  for (int i = 0; i < g[v].size(); ++i) {
    int u = g[v][i];
    if (!visited[u]) {
      dfs(u, bus ^ 1);
    }
  }
}

int main() {
  int m;
  cin >> n >> m;
  g.resize(n + 1);
  visited.resize(n + 1, 0);
  dsu.resize(n + 3, -1);
  dsu_size.resize(n + 3, -1);
  for (int i = 0; i < (int)dsu.size(); ++i) {
    dsu[i] = i;
    dsu_size[i] = 1;
  }

  vector<pair<int, int>> block;

  for (int i = 0; i < m; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    if (c == 1) {
      add(b, a);
    } else {
      g[a].push_back(b);
      g[b].push_back(a);
      block.push_back({a, b});
    }
  }

  for (int i = 0; i < n; ++i) {
    if (!visited[i]) {
      dfs(i, 0);
    }
  }

  for (auto x : block) {
    if (get(x.first) == get(x.second)) {
      cout << -1 << '\n';
      return 0;
    }
  }

  int cnt = 0;
  int bus = get(1);
  vector<int> ans;
  for (int i = 1; i <= n; ++i) {
    if (get(i) == bus) {
      cnt++;
      ans.push_back(i);
    }
  }
  cout << cnt << '\n';
  for (auto x : ans) {
    cout << x << ' ';
  }
  cout << '\n';

  return 0;
}
