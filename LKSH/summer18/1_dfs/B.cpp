#include <iostream>
#include <vector>

void dfs(std::vector<std::vector<int>>& arr, std::vector<char>& visited, std::vector<int>& tin, std::vector<int>& tout, int& t, int v) {
  tin[v] = t++;
  for (int i = 0; i < (int)arr[v].size(); ++i) {
    if (!visited[arr[v][i]]) {
      visited[arr[v][i]] = 1;
      dfs(arr, visited, tin, tout, t, arr[v][i]);
    }
  }
  tout[v] = t++;
}

int main() {
  int n = 0;
  int start = -1;
  std::cin >> n;
  std::vector<std::vector<int>> arr(n, std::vector<int>(0));
  for (int i = 0; i < n; ++i) {
    int parent = 0;
    std::cin >> parent;
    parent -= 1;
    if (parent < 0) {
      start = i;
      continue;
    }
    arr[parent].push_back(i);
  }

  std::vector<char> visited(n, 0);
  std::vector<int> tin(n, -1);
  std::vector<int> tout(n, -1);
  int t = 0;

  dfs(arr, visited, tin, tout, t, start);

  int m = 0;
  std::cin >> m;
  for (int i = 0; i < m; ++i) {
    int upper, lower;
    std::cin >> upper >> lower;
    --upper;
    --lower;
    //std::cout << tin[upper] << ' ' << tin[lower] << ' ' << tout[upper] << ' ' << tout[lower] << '\n';
    if (tin[upper] < tin[lower] && tout[upper] > tout[lower]) {
      std::cout << 1 << '\n';
    } else {
      std::cout << 0 << '\n';
    }
  }

  return 0;
}