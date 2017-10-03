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

template<typename T>
void PrintVector(const std::vector<T>& vector) {
   for (size_t i = 0; i + 1 < vector.size(); ++i) {
    std::cout << vector[i] << '\n';
  }
  if (!vector.empty()) {
    std::cout << vector.back();
  }
}

struct SourcesAndSinks {
  std::vector<int32_t> sources;
  std::vector<int32_t> sinks;
};

SourcesAndSinks FindSourcesSinks(const std::vector<Row<int32_t>>& adjacency_matrix) {
  const auto vertex_count = adjacency_matrix.size();
  std::vector<char> sources_flags(vertex_count, 1);
  std::vector<char> sinks_flags(vertex_count, 1);
  for (size_t i = 0; i < vertex_count; ++i) {
    for (size_t j = 0; j < vertex_count; ++j) {
      if (adjacency_matrix[i][j]) {
        sinks_flags[i] = 0;
        sources_flags[j] = 0;
      }
    }
  }
  
  SourcesAndSinks result;
  for (size_t i = 0; i < vertex_count; ++i) {
    if (sources_flags[i]) {
      result.sources.push_back(i + 1);
    }
    if (sinks_flags[i]) {
      result.sinks.push_back(i + 1);
    }
  }

  return result;
}

void PrintResult(const SourcesAndSinks& result) {
  const auto& sources = result.sources;
  const auto& sinks = result.sinks;
  std::cout << sources.size() << '\n';
  if (!sources.empty()) {
    PrintVector(sources);
    std::cout << '\n';
  }
  std::cout << sinks.size() << '\n';
  if (!sinks.empty()) {
    PrintVector(sinks);
    std::cout << '\n';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int32_t vertex_count = 0;
  std::cin >> vertex_count;
  const auto& adjacency_matrix = ReadMatrix<int32_t>(vertex_count, vertex_count);

  PrintResult(FindSourcesSinks(adjacency_matrix));

  return 0;
}