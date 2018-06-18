#include <iostream>
#include <vector>

template<typename T>
using Row = std::vector<T>;

template<typename T>
std::vector<T> ReadVector(size_t length) {
    std::vector<T> objects(length);
    for (size_t i = 0; i < length; ++i) {
        std::cin >> objects[i];
    }
    return objects;
}

template<typename T>
std::vector<Row<T>> ReadMatrix(size_t row_count, size_t column_count) {
    std::vector<Row<T>> matrix;
    matrix.reserve(row_count);
    for (size_t i = 0; i < row_count; ++i) {
        matrix.push_back(ReadVector<T>(column_count));
    }
    return matrix;
}

int dfs(size_t vertex_count, std::vector<Row<int>>& matrix, size_t cur_vertex, std::vector<int>& visited) {
  visited[cur_vertex] = 1;
  size_t cnt = 1;
  for (size_t i = 0; i < vertex_count; ++i) {
    if (matrix[cur_vertex][i] && !visited[i]) {
      cnt += dfs(vertex_count, matrix, i, visited);
    }
  }
  return cnt;
}

int count_vertex_in_one_component(size_t vertex_count, std::vector<Row<int>>& matrix, size_t initial_vertex) {
  std::vector<int> visited(vertex_count, 0);
  visited[initial_vertex] = 1;
  return dfs(vertex_count, matrix, initial_vertex, visited);
}


int main() {
  size_t vertex_count = -1;
  size_t initial_vertex = -1;
  std::cin >> vertex_count >> initial_vertex;
  --initial_vertex;
  std::vector<Row<int>> matrix = ReadMatrix<int>(vertex_count, vertex_count);

  std::cout << count_vertex_in_one_component(vertex_count, matrix, initial_vertex) << '\n';

  return 0;
}