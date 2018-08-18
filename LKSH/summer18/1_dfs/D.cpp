#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

void dfs(std::vector<std::vector<int>>& arr, std::vector<char>& visited, std::vector<int>& tin,
         std::vector<int>& tout, int& t, std::vector<int>& up, std::vector<int>& ans, int v, int parent, bool root) {
  tin[v] = t++;
  visited[v] = 1;
  up[v] = tin[v];
  bool flag = false;
  int sons = 0;
  for (int i = 0; i < (int)arr[v].size(); ++i) {
    if (!visited[arr[v][i]]) {
      ++sons;
      dfs(arr, visited, tin, tout, t, up, ans, arr[v][i], v, false);
      up[v] = std::min(up[v], up[arr[v][i]]);
      if (up[arr[v][i]] >= tin[v] && (!root)) {
        flag = true;
      }
    } else if (arr[v][i] != parent) {
      up[v] = std::min(up[v], tin[arr[v][i]]);
    }
  }

  tout[v] = t++;

  if ((flag && !root) || (root && sons > 1)) {
    ans.push_back(v);
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> arr(n);
  for (int i = 0; i < m; ++i) {
    int from, to;
    std::cin >> from >> to;
    --from;
    --to;
    arr[from].push_back(to);
    arr[to].push_back(from);
  }

  std::vector<char> visited(n, 0);
  std::vector<int> ans(0);
  std::vector<int> tin(n, -1);
  std::vector<int> tout(n, -1);
  int t = 0;
  std::vector<int> up(n, 0);

  for (int i = 0; i < n; ++i) {
    if (!visited[i]) {
      dfs(arr, visited, tin, tout, t, up, ans, i, i, true);
    }
  }

  std::sort(ans.begin(), ans.end());
  std::cout << ans.size() << '\n';
  for (int i = 0; i < (int)ans.size(); ++i) {
    std::cout << ans[i] + 1 << ' ';
  }

  return 0;
}
