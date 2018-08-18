#include <iostream>
#include <vector>
#include <set>

using namespace std;
vector<vector<pair<int, int>>> g;
int n, m;
int inf = 1e9;

int daikstra(int s, int t) {
  set<pair<int, int>> q;
  vector<int> d(n, -inf);
  d[s] = 0;
  q.insert({s, d[s]});
  while (!q.empty()) {
    pair<int, int> tmp = *q.begin();
    int vertex = tmp.first;
    int distance = tmp.second;
    q.erase(q.begin());
    for (int i = 0; i < (int)g[vertex].size(); ++i) {
      int u = g[vertex][i].first;
      if (d[u] > distance + g[vertex][i].second || d[u] == -inf) {
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
  }

  int ret = daikstra(s, t);
  if (ret == -inf) {
    cout << "Unreachable" << '\n';
  } else {
    cout << ret << '\n';
  }
  

  return 0;
}