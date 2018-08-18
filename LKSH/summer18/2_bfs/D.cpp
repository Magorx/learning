#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <algorithm>

using namespace std;


struct Edge {
long long from;
long long to;
long long w;
};


long long n, m;
vector<Edge> g;
vector<int> d;
vector<long long> parents;
pair<long long, long long> ans;
vector<int> len;


void ford_boyard() {
  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < (int)g.size(); ++i) {
      Edge e = g[i];
      if (d[e.from] + e.w < d[e.to]) {
        d[e.to] = d[e.from] + e.w;
        parents[e.to] = e.from;
      }
    }
  }
}

vector<char> visited;
int edge = -1;
bool super_flag = true;

vector<int> find_loop(int v) {
  if (visited[v]) {
    edge = v;
    return {};
  } else {
    visited[v] = 1;
    vector<int> ret(0);
    if (parents[v] != -1) {
      ret = find_loop(parents[v]);
      if (!super_flag) {
        return ret;
      }
    } else {
      super_flag = false;
      return {-1};
    }
    ret.push_back(v);
    if (v == edge) {
      super_flag = false;
    }
    return ret;
  }
}

int main() {
  cin >> n;

  len.resize(n, 0);
  d.resize(n, 0);
  visited.resize(n, 0);
  parents.resize(n, -1);
  for (long long i = 0; i < n; ++i) {
    for (long long j = 0; j < n; ++j) {
      int w;
      cin >> w;
      if (w == 100000) {
        continue;
      }
      g.push_back({i, j, w});
    }
  }

  ford_boyard();
  vector<int> loop;
  bool flag = false;
  for (int i = 0; i < n; ++i) {
    if (d[i] < 0) {
       loop = find_loop(i);
       if (count(loop.begin(), loop.end(), -1) > 0) {
         super_flag = true;
         edge = -1;
         visited.clear();
         visited.resize(n, 0);
         continue;
       } else {
         flag = true;
         break;
       }
    }
  }

  if (flag) {
    cout << "YES\n";
    cout << loop.size() << '\n';
    for (int i = 0; i < (int)loop.size(); ++i) {
      cout << loop[i] + 1 << ' ';
    }
    cout << '\n';
  } else {
    cout << "NO\n";
  }


  return 0;
}