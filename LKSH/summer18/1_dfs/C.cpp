#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

void dfs(std::vector<std::vector<std::pair<int, int>>>& arr, std::vector<char>& visited, std::vector<int>& tin,
         std::vector<int>& tout, int& t, std::vector<int>& up, std::vector<int>& ans, int v, int parent) {
  tin[v] = t++;
  visited[v] = 1;
  up[v] = tin[v];
  for (int i = 0; i < (int)arr[v].size(); ++i) {
    if (!visited[arr[v][i].first]) {
      dfs(arr, visited, tin, tout, t, up, ans, arr[v][i].first, v);
      up[v] = std::min(up[v], up[arr[v][i].first]);
    } else if (arr[v][i].first != parent) {
      up[v] = std::min(up[v], tin[arr[v][i].first]);
    }
    if (up[arr[v][i].first] > tin[v]) {
      ans.push_back(arr[v][i].second);
    }
  }

  tout[v] = t++;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<std::pair<int, int>>> arr(n, std::vector<std::pair<int, int>>(0));
  for (int i = 0; i < m; ++i) {
    int from, to;
    std::cin >> from >> to;
    --from;
    --to;
    arr[from].push_back(std::pair<int, int>(to, i));
    arr[to].push_back(std::pair<int, int>(from, i));
  }

  std::vector<char> visited(n, 0);
  std::vector<int> ans(0);
  std::vector<int> tin(n, -1);
  std::vector<int> tout(n, -1);
  int t = 0;
  std::vector<int> up(n, 0);

  for (int i = 0; i < n; ++i) {
    if (!visited[i]) {
      dfs(arr, visited, tin, tout, t, up, ans, i, i);
    }
  }

  std::sort(ans.begin(), ans.end());
  std::cout << ans.size() << '\n';
  for (int i = 0; i < (int)ans.size(); ++i) {
    std::cout << ans[i] + 1 << ' ';
  }

  return 0;
}
