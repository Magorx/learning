#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Edge {
long long from;
long long to;
long long w;
};

bool operator<(Edge first, Edge second) {
  if (first.w < second.w) {
    return true;
  } else {
    return false;
  }
}

long long n, m, k;
vector<Edge> g;

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

int ans;
int minost() {
  ans = 0;
  sort(g.begin(), g.end());
  for (int i = 0; i < (int)g.size(); ++i) {
    Edge e = g[i];
    if (get(e.from) != get(e.to)) {
      add(e.from, e.to);
      ans += e.w;
    }
  }
  return ans;
}

int main() {
  cin >> n >> m;

  g.resize(n);
  dsu.resize(n, -1);
  dsu_size.resize(n, -1);
  for (long long i = 0; i < m; ++i) {
    long long from, to, weight;
    cin >> from >> to >> weight;
    --from;
    --to;
    g.push_back({from, to, weight});
    g.push_back({to, from, weight});
  }

  for (int i = 0; i < (int)dsu.size(); ++i) {
    dsu[i] = i;
    dsu_size[i] = 1;
  }

  minost();
  cout << ans << '\n';

  return 0;
}