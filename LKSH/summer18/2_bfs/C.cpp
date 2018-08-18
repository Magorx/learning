#include <iostream>
#include <vector>
#include <deque>
#include <set>

using namespace std;
long long n, m;
vector<vector<pair<long long, long long>>> g;
vector<long long> parents;
pair<long long, long long> ans;
vector<int> len;

long long path_len(long long v, long long u) {
  if (v == u) {
    return 0;
  } else {
    return 1 + path_len(v, parents[u]);
  }
}


long long dist(long long s, long long t) {
  set<vector<long long>> q;
  vector<long long> d(n, -1);
  d[s] = 0;
  q.insert({d[s], 0, s});
  while (!q.empty()) {
    vector<long long> tmp = *q.begin();
    long long vertex = tmp[2];
    long long distance = tmp[0];
    q.erase(q.begin());
    for (long long i = 0; i < (long long)g[vertex].size(); ++i) {
      long long u = g[vertex][i].first;
      if (d[u] > distance + g[vertex][i].second || d[u] == -1) {
        parents[u] = vertex;
        len[u] = tmp[1] + 1;
        d[u] = distance + g[vertex][i].second;
        q.insert({d[u], tmp[1] + 1, u});
      } else if (d[u] == distance + g[vertex][i].second) {
        if (tmp[1] + 1 > len[u]) {
          parents[u] = vertex;
          len[u] = tmp[1] + 1;
          q.insert({d[u], tmp[1] + 1, u});
        }
      }
    }
  }

  return d[t];
}


int main() {
  cin >> n >> m;
  long long s, t;
  s = 0;
  t = n - 1;

  g.resize(n);
  len.resize(n, 0);
  parents.resize(n, -1);
  for (long long i = 0; i < m; ++i) {
    long long from, to, weight;
    cin >> from >> to >> weight;
    --from;
    --to;
    g[from].push_back({to, weight});
    g[to].push_back({from, weight});
  }

  int ret = dist(s, t);
  cout << ret << ' ' << path_len(s, t) << '\n'; 
  return 0;
}