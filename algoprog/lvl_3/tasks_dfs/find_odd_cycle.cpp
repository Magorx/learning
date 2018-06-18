#include <iostream>
#include <vector>
#include <algorithm>


template<typename T>
using Row = std::vector<T>;

int dfs(std::vector<Row<int>>& matrix, int cur_vertex, std::vector<int>& visited, int path_length) {
  visited[cur_vertex] = path_length;
  for (auto x : matrix[cur_vertex]) {
    if (visited[x] == 0) {
      if (dfs(matrix, x, visited, path_length + 1)) {
        return true;
      }
    } else {
      int delta = std::abs(path_length - visited[x]);
      if (delta > 1 && delta % 2 == 0) {
        return true;
      }
    }
  }

  return false;
}

int main() {
  int vertex_count = -1;
  int edge_count = -1;
  std::cin >> vertex_count >> edge_count;
  std::vector<Row<int>> matrix(vertex_count, Row<int>());
  for (int i = 0; i < edge_count; ++i) {
    int from = 0;
    int to = 0;
    std::cin >> from >> to;
    --from;
    --to;
    matrix[from].push_back(to);
    matrix[to].push_back(from);
  }

  std::vector<int> visited(vertex_count, 0);

  for (int j = 0; j < vertex_count; ++j) {
    if (!visited[j]) {
      if (dfs(matrix, j, visited, 1)) {
        std::cout << "NO\n";
        return 0;
      }
    }
  }

  std::cout << "YES\n";
    for (int i = 0; i < vertex_count; ++i) {
      if (visited[i] % 2) {
        std::cout << i + 1 << ' ';
      }
    }
    std::cout << '\n';

  return 0;
}