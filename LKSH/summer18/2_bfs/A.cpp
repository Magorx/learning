#include <iostream>
#include <vector>
#include <deque>
#include <set>

using namespace std;
int n, m;
vector<vector<pair<int, int>>> g;

int dist(int s, int t) {
  set<pair<int, int>> q;
  vector<int> d(n, -1);
  d[s] = 0;
  q.insert({s, d[s]});
  while (!q.empty()) {
    pair<int, int> tmp = *q.begin();
    int vertex = tmp.first;
    int distance = tmp.second;
    q.erase(q.begin());
    for (int i = 0; i < (int)g[vertex].size(); ++i) {
      int u = g[vertex][i].first;
      if (d[u] > distance + g[vertex][i].second || d[u] == -1) {
        d[u] = distance + g[vertex][i].second;
        q.insert({u, d[u]});
      }
    }
  }

  return d[t];
}


int main() {
  cin >> n >> m;
  int s, t;
  cin >> s >> t;
  --s;
  --t;

  g.resize(n);
  for (int i = 0; i < m; ++i) {
    int from, to, weight;
    cin >> from >> to >> weight;
    --from;
    --to;
    g[from].push_back({to, weight});
    g[to].push_back({from, weight});
  }

  int ret = dist(s, t);
  if (ret < 0) {
    cout << -1 << '\n';
  } else {
    cout << ret << '\n';
  }

  return 0;
}