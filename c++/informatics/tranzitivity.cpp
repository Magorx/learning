#include <iostream>
#include <vector>

template<typename T>
using Row = std::vector<T>;

bool IsGraphTransitive(const std::vector<Row<char>>& adjacency_matrix) {
  const auto column_count = adjacency_matrix.size();
  const auto row_count = adjacency_matrix[0].size();
  for (size_t i = 0; i < column_count; ++i) {
    std::vector<int32_t> connected_vertices;
    for (size_t j = 0; j < row_count; ++j) {
      if (adjacency_matrix[i][j]) {
        for (size_t k = 0; k < connected_vertices.size(); ++k) {
          if (!adjacency_matrix[connected_vertices[k]][j]) {
            return false;
          }
        }
        connected_vertices.push_back(j);
      }
    }
  }

  return true;
}

std::vector<Row<char>> ReadAdjacencyMatrix(const int32_t vertex_count, const int32_t edges_count) {
  std::vector<Row<char>> adjacency_matrix(vertex_count, Row<char>(vertex_count, 0));
  for (int32_t i = 0; i < edges_count; ++i) {
    int32_t first_vertex = 0, second_vertex = 0;
    std::cin >> first_vertex >> second_vertex;
    --first_vertex;
    --second_vertex;
    adjacency_matrix[first_vertex][second_vertex] = 1;
    adjacency_matrix[second_vertex][first_vertex] = 1;
  }
  return adjacency_matrix;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int32_t vertex_count = 0, edges_count = 0;
  std::cin >> vertex_count >> edges_count;

  const std::vector<Row<char>> adjacency_matrix = ReadAdjacencyMatrix(vertex_count, edges_count);
  
  std::cout << (IsGraphTransitive(adjacency_matrix) ? "YES" : "NO") << '\n';

  return 0;
}