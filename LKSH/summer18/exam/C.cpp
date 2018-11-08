#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <algorithm>

using namespace std;
long long n, m;
vector<vector<pair<long long, long long>>> g;
long long max_w;
vector<long long> parents;

long long dist(long long s, long long t) {
  set<pair<pair<long long, long long>, long long>> q;
  vector<long long> max_pay(n, 0);
  vector<long long> d(n, -1);
  d[s] = 0;
  q.insert({{0, d[s]}, s});
  while (!q.empty()) {
    pair<pair<long long, long long>, long long> tmp = *q.begin();
    long long vertex = tmp.second;
    long long distance = tmp.first.second;
    q.erase(q.begin());
    for (long long i = 0; i < (long long)g[vertex].size(); ++i) {
      long long m_w = tmp.first.first;
      long long u = g[vertex][i].first;
      // cout << vertex << ' ' << u << ' ' << m_w << ' ' << g[vertex][i].second << ' ' << distance << ' ' << d[u] << '\n';
      if (d[u] == -1 || d[u] - max_pay[u] > distance + g[vertex][i].second - max(m_w, g[vertex][i].second)) {
        // cout << "OK\n";
        parents[u] = vertex;
        m_w = max(m_w, g[vertex][i].second);
        d[u] = distance + g[vertex][i].second;
        max_pay[u] = m_w;
        q.insert({{m_w, d[u]}, u});
      }
    }
  }
  return d[t];
}

vector<long long> get_path(long long s, long long t) {
  vector<long long> ans;
  long long cur_v = t;
  while (cur_v != -1) {
    ans.push_back(cur_v);
    cur_v = parents[cur_v];
  }

  return ans;
}


int main() {
  max_w = 0;
  cin >> n >> m;
  parents.resize(n, -1);
  long long s, t;

  g.resize(n);
  for (long long i = 0; i < m; ++i) {
    long long from, to, weight;
    cin >> from >> to >> weight;
    --from;
    --to;
    g[from].push_back({to, weight});
    g[to].push_back({from, weight});
  }

  cin >> s >> t;
  --s;
  --t;

  long long ret = dist(s, t);
  if (ret == -1) {
    cout << ret << '\n';
    return 0;
  }

  auto path = get_path(s, t);
  max_w = 0;
  long long a, b;
  for (long long i = 0; i < path.size() - 1; ++i) {
    long long v = path[i];
    long long u = path[i + 1];
    for (long long j = 0; j < g[v].size(); ++j) {
      if (g[v][j].first == u) {
        if (max_w < g[v][j].second) {
          max_w = g[v][j].second;
          a = v + 1;
          b = u + 1;
        }
      }
    }
  }
  cout << ret - max_w << ' ' << path.size() - 1 << '\n';

  reverse(path.begin(), path.end());
  for (auto x : path) {
    cout << x + 1 << ' ';
  }
  cout << '\n';

  cout << a << ' ' << b << '\n';

  return 0;
}