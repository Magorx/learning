#include <iostream>
#include <vector>

template<typename T>
using Row = std::vector<T>;

template<typename T>
std::vector<T> ReadVector(int length) {
    std::vector<T> objects(length);
    for (int i = 0; i < length; ++i) {
        std::cin >> objects[i];
    }
    return objects;
}

template<typename T>
std::vector<Row<T>> ReadMatrix(int row_count, int column_count) {
    std::vector<Row<T>> matrix;
    matrix.reserve(row_count);
    for (int i = 0; i < row_count; ++i) {
        matrix.push_back(ReadVector<T>(column_count));
    }
    return matrix;
}

bool dfs(int vertex_count, std::vector<Row<int>>& matrix, int cur_vertex, std::vector<int>& visited, int last_vertex) {
  visited[cur_vertex] = 1;
  for (int i = 0; i < vertex_count; ++i) {
    if (matrix[cur_vertex][i]) {
      if (visited[i] && i != last_vertex) {
        return false;
      } else if (!visited[i]) {
        if (!dfs(vertex_count, matrix, i, visited, cur_vertex)) {
          return false;
        }
      }
    }
  }
  return true;
}

int main() {
  int vertex_count = -1;
  std::cin >> vertex_count;
  std::vector<Row<int>> matrix = ReadMatrix<int>(vertex_count, vertex_count);

  std::vector<int> visited(vertex_count, 0);
  visited[0] = 1;
  if (!dfs(vertex_count, matrix, 0, visited, 0)) {
    std::cout << "NO\n";
    return 0;
  } else {
    for (auto x : visited) {
      if (x == 0) {
        std::cout << "NO\n";
        return 0;
      }
    }
  }

  std::cout << "YES\n";

  return 0;
}