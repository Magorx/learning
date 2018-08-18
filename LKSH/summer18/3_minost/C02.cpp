#include <iostream>
#include <vector>
#include <deque>
#include <set>

using namespace std;
int n, m;
vector<vector<pair<int, int>>> g;
int ans;

int dist() {
  ans = 0;
  set<pair<int, int>> q;
  vector<char> used(n, 0);
  vector<int> d(n, -1);
  d[0] = 0;
  q.insert({0, d[0]});
  while (!q.empty()) {
    pair<int, int> tmp = *q.begin();
    int vertex = tmp.first;
    used[vertex] = 1;
    // cout << vertex << endl;
    // int distance = tmp.second;
    ans += tmp.second;
    q.erase(q.begin());
    for (int i = 0; i < (int)g[vertex].size(); ++i) {
      int u = g[vertex][i].first;
      if (used[u]) {
        continue;
      }
      if (d[u] > g[vertex][i].second || d[u] == -1) {
        d[u] = g[vertex][i].second;
        q.insert({u, d[u]});
      }
    }
  }

  return ans;
}


int main() {
  cin >> n >> m;

  g.resize(n);
  for (int i = 0; i < m; ++i) {
    int from, to, weight;
    cin >> from >> to >> weight;
    --from;
    --to;
    g[from].push_back({to, weight});
    g[to].push_back({from, weight});
  }
  cout << dist() << '\n';

  return 0;
}