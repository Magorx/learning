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

std::vector<Row<int>> SHIFTS {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};

int dfs(size_t vertex_count, std::vector<Row<char>>& matrix, size_t cur_x, size_t cur_y, std::vector<Row<int>>& visited) {
  visited[cur_x][cur_y] = 1;
  int cnt = 1;
  for (auto x : SHIFTS) {
    size_t new_x = cur_x + x[0];
    size_t new_y = cur_y + x[1];
    if (matrix[new_x][new_y] == '.' && !visited[new_x][new_y]) {
      cnt += dfs(vertex_count, matrix, new_x, new_y, visited);
    }
  }

  return cnt;
}

int count_room_square(size_t vertex_count, std::vector<Row<char>>& matrix, size_t initial_x, size_t initial_y) {
  std::vector<Row<int>> visited(vertex_count, Row<int>(vertex_count, 0));
  visited[initial_x][initial_y] = 1;
  return dfs(vertex_count, matrix, initial_x, initial_y, visited);
}


int main() {
  size_t vertex_count = -1;
  size_t initial_x = -1;
  size_t initial_y = -1;
  std::cin >> vertex_count;
  std::vector<Row<char>> matrix = ReadMatrix<char>(vertex_count, vertex_count);
  std::cin >> initial_x >> initial_y;
  --initial_x;
  --initial_y;

  std::cout << count_room_square(vertex_count, matrix, initial_x, initial_y) << '\n';

  return 0;
}