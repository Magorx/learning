#include <iostream>
#include <vector>
#include <algorithm>

int dfs(std::vector<std::vector<int>>& arr, std::vector<char>& visited, int& edge, std::vector<int>& ans, int v) {
  visited[v] = 1;
  for (int i = 0; i < (int)arr[v].size(); ++i) {
    if (!visited[arr[v][i]]) {
      int ret = dfs(arr, visited, edge, ans, arr[v][i]);
      if (ret == 1) {
        if (v == edge) {
          return 2;
        } else {
          ans.push_back(v + 1);
          return 1;
        }
      }
      if (ret == 2) {
        return 2;
      }
    } else if (visited[arr[v][i]] == 1) {
      edge = arr[v][i];
      ans.push_back(arr[v][i] + 1);
      ans.push_back(v + 1);
      return 1;
    }
  }
  visited[v] = 2;
  return 0;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> arr(n, std::vector<int>(0));
  for (int i = 0; i < m; ++i) {
    int from, to;
    std::cin >> from >> to;
    --from;
    --to;
    if (std::count(arr[from].begin(), arr[from].end(), to) == 0) {
      arr[from].push_back(to);
    }
  }

  std::vector<char> visited(n, 0);
  int edge = -1;
  std::vector<int> ans(0);

  for (int i = 0; i < n; ++i) {
    if (!visited[i]) {
      if (dfs(arr, visited, edge, ans, i) != 0) {
        break;
      }
    }
  }

  if ((int)ans.size() == 0) {
    std::cout << "NO\n";
  } else {
    std::cout << "YES\n";
    std::reverse(ans.begin(), ans.end());
    for (int i = 0; i < (int)ans.size(); ++i) {
      std::cout << ans[i] << ' ';
    }
    std::cout << '\n';
  }

  return 0;
}
