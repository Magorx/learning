#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Edge {
long long from;
long long to;
long long w;
};

long long n, m, k;
vector<vector<int>> g;
vector<long long> parents;
pair<long long, long long> ans;
vector<vector<int>> lens;

vector<int> dsu;

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
  dsu[first] = second;
}

vector<char> visited;
void dfs(int v) {
  visited[v] = 1;
  for (int i = 0; i < (int)g[v].size(); ++i) {
    if (!visited[g[v][i]]) {
      dsu[g[v][i]] = v;
      dfs(g[v][i]);
    }
  }
}

int main() {
  cin >> n >> m >> k;

  g.resize(n);
  visited.resize(n, 0);
  dsu.resize(n, -1);
  for (long long i = 0; i < m; ++i) {
    long long from, to;
    cin >> from >> to;
    --from;
    --to;
    g[from].push_back(to);
    g[to].push_back(from);
  }

  for (int i = 0; i < n; ++i) {
    if (!visited[i]) {
      dsu[i] = i;
      dfs(i);
    }
  }
  for (int i = 0; i < (int)dsu.size(); ++i) {
    cout << dsu[i] << '\n';
  }
  for (int z = 0; z < k; ++z) {
    string s;
    int from, to;
    cin >> s >> from >> to;
    --from;
    --to;
    if (s == "ask") {
      if (get(from) == get(to)) {
        cout << "YES\n";
      } else {
        cout << "NO\n";
      }
    } else {
      if (dsu[from] == to) {
        dsu[from] = from;
      } else  if (dsu[to] == from) {
        dsu[to] = to;
      } 
    }
  }

  return 0;
}