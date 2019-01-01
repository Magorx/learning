#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 1e6;
const int K_MAX = 25;

vector<vector<int>> g;
vector<pair<int, int>> l;
vector<int> I;
int dfs(int v, int depth = 0) {
  I[v] = l.size();
  l.push_back({depth, v});
  for (int i = 0; i < g[v].size(); ++i) {
    int u = g[v][i];
    dfs(u, depth + 1);
    l.push_back({depth, v});
  }
  return 0;
}

pair<int, int> get_min(vector<vector<pair<int, int>>> &st, vector<int> &logs, int u, int v) {
  int iu = I[u];
  int iv = I[v];
  if (iu > iv) {
    swap(iu, iv);
  }

  int k = logs[iv - iu];
  return min(st[k][iu], st[k][iv - (1 << k) + 1]);
}

int main() {
  long long n, m;
  cin >> n >> m;
  g.resize(n);
  for (int i = 0; i < n - 1; ++i) {
    int parent;
    cin >> parent;
    g[parent].push_back(i + 1);
  }
  long long a1, a2;
  cin >> a1 >> a2;
  long long x, y, z;
  cin >> x >> y >> z;

  I.resize(n, -1);
  dfs(0);

  vector<int> logs(N_MAX);
  logs[1] = 0;
  for (int i = 2; i < N_MAX; i++) {
    logs[i] = logs[i / 2] + 1;
  }

  vector<vector<pair<int, int>>> st(K_MAX, vector<pair<int, int>>(N_MAX, {0, 0}));

  for (int i = 0; i < l.size(); i++)
    st[0][i] = l[i];
  
  for (int k = 1; k < K_MAX; k++) {
    for (int i = 0; i < l.size(); i++) {
      //cout << k << ' ' << i << '\n';
      st[k][i] = min(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
    }
  }

  long long ans = 0;
  long long prev_ans = 0;
  for (int i = 1; i <= m; ++i) {
    pair<int, int> ret = get_min(st, logs, (a1 + prev_ans) % n, a2);
    // cout << ret.second << '\n';
    ans += ret.second;
    prev_ans = ret.second;
    // cout << i << ") " << a1 << ' ' << a2 << ' ' << prev_ans << '\n';

    long long new_a1 = (x * a1 + y * a2 + z) % n;
    long long new_a2 = (x * a2 + y * new_a1 + z) % n;
    a1 = new_a1;
    a2 = new_a2;
  }
  cout << ans << "\n";

  return 0;
}