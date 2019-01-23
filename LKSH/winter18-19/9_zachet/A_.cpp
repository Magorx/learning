#include <bits/stdc++.h>

using namespace std;

void qq() {
  cout << "UQUQUQUQUQUQ" << endl;
}

vector<int> terminals;
vector<set<int>> g;
vector<map<int, int>> gr;
vector<set<pair<int, int>>> super_visited; // vertex and char
vector<int> used;
vector<int> s_reach;
int t = 1;
bool INF = false;
long long M = 1e9+7;

vector<long long> dp;

bool ignored(int v) {
  if (s_reach[v] != 1) {
    return true;
  } else {
    return false;
  }
}

int dfs(int v, int p, int c) {
  // cout << v << ' ' << p << ' ' << (char)c << '\n';
  /*if (ignored(v)) {
    return 0;
  } else */
  if (dp[v] != -1) {
    return dp[v];
  }
  long long ans = 0;
  super_visited[v].insert({p, c});
  used[v] = t;
  for (auto q : gr[v]) {
    int u = q.second;
    int ch = q.first;
    if (super_visited[u].find({v, ch}) != super_visited[u].end()) {
      continue;
    }
    ans += dfs(u, v, ch);
    ans %= M;
  }
  if (v == 0) {
    dp[v] = 1;
    return 1;
  }
  dp[v] = ans;
  return ans;
}

void cnt_starts(int v) {
  s_reach[v] = 1;
  used[v] = t;
  for (auto u : g[v]) {
    if (used[u] != t)
      cnt_starts(u);
  }
}

void cnt_terms(int v) {
  used[v] = t;
  for (auto u : gr[v]) {
    if (used[u.second] != t)
      cnt_terms(u.second);
  }
  used[v] = t + 1;
}

void check_cyc(int v) {
  used[v] = t;
  if (ignored(v)) {
    return;
  }
  for (auto u : g[v]) {
    if (used[u] == t) {
      INF = true;
      return;
    }
    check_cyc(u);
    if (INF) {
      return;
    }
  }
  used[v] = t + 1;
}

int main() {
  int n, m, k;
  cin >> n >> m >> k;
  g.resize(n);
  gr.resize(n);
  used.resize(n);
  s_reach.resize(n);
  terminals.resize(k);
  super_visited.resize(n);
  dp.resize(n, -1);
  for (int i = 0; i < k; ++i) {
    cin >> terminals[i];
    terminals[i] -= 1;
  }

  for (int i = 0; i < m; ++i) {
    int a, b;
    char c;
    cin >> a >> b >> c;
    a--;
    b--;
    g[a].insert(b);
    gr[b][c] = a;
  }

  t += 10;
  cnt_starts(0);

  t += 10;
  for (int i = 0; i < k; ++i) {
    cnt_terms(terminals[i]);
  }
  for (int i = 0; i < n; ++i) {
    if (used[i] != t + 1) {
      s_reach[i] = 0;
    }
  }

  /*if (ignored(0)) {
    cout << 0 << '\n';
  }*/

  t += 10;
  check_cyc(0);
  if (INF) {
    cout << "-1\n";
    return 0;
  }

  long long ans = 0;
  for (int i = 0; i < k; ++i) {
    t += 10;
    ans += dfs(terminals[i], 0, 0);
    ans %= M;
  }

  cout << ans << '\n';
  return 0;
}