#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <tuple>

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
void PrintCollection(const T& collection, std::string separator=" ", std::string end="") {
  if (!(collection.end() - collection.begin()))
    return;

  for (auto i = collection.begin(); i != collection.end() - 1; ++i) {
    std::cout << *i << separator;
  }
  std::cout << *(collection.end() - 1) << end;
}

std::vector<Row<int32_t>> ReadAdjacencyListFromAdjacencyMaxtrix(int32_t vertex_count) {
  std::vector<Row<int32_t>> adjacency_list(vertex_count);
  for (int32_t i = 0; i < vertex_count; ++i) {
    for (int32_t j = 0; j < vertex_count; ++j) {
      int32_t vertecies_connected;
      std::cin >> vertecies_connected;
      if (vertecies_connected) {
        adjacency_list[i].push_back(j);
      }
    }
  }
  return adjacency_list;
}

std::vector<int32_t> CalculateParents(const std::vector<Row<int32_t>>& adjacency_list, int32_t start_vertex) {
  const auto vertex_count = adjacency_list.size();
  std::queue<int32_t> to_visit;
  to_visit.push(start_vertex);
  std::vector<char> visited(vertex_count, 0);
  visited[start_vertex] = 1;
  std::vector<int32_t> parents(vertex_count, -1);

  while (!to_visit.empty()) {
    const auto cur_vertex = to_visit.front();
    to_visit.pop();
    for (const auto new_vertex : adjacency_list[cur_vertex]) {
      if (visited[new_vertex]) {
        continue;
      }
      visited[new_vertex] = 1;
      parents[new_vertex] = cur_vertex;
      to_visit.push(new_vertex);
    }
  }

  return parents;
}

struct PathFound {
  bool path_exists = false;
  std::vector<int32_t> path;
};

PathFound GetPath(const std::vector<int32_t>& parents, int32_t vertex_from, int32_t vertex_to) {
  std::vector<int32_t> way;
  if (vertex_from == vertex_to) {
    return {true, way};
  }
  for (int32_t i = vertex_to; parents[i] != -1; i = parents[i]) {
    way.push_back(i);
  }

  if (!way.empty()) {
    way.push_back(vertex_from);
  } else {
    return {false, way};
  }
  return {true, way};
}

PathFound CalculatePath(const std::vector<Row<int32_t>>& adjacency_list, int32_t vertex_from, int32_t vertex_to) {
  return GetPath(CalculateParents(adjacency_list, vertex_to), vertex_to, vertex_from);
}

void PrintResult(PathFound way) {
  if (!way.path_exists) {
    std::cout << -1 << '\n';
    return;
  }
  std::cout << way.path.size() - 1 << '\n';
  for (size_t i = 0; i < way.path.size(); ++i) {
    ++way.path[i];
  }
  PrintCollection(way.path, " ", "\n");
}

using VerticesPair = std::pair<int32_t, int32_t>;

VerticesPair ReadVerticesPair() {
  int32_t first = 0;
  int32_t second = 0;
  std::cin >> first >> second;
  return {first - 1, second - 1};
}

int main() {
  int32_t vertex_count = 0;
  std::cin >> vertex_count;
  const std::vector<Row<int32_t>> adjacency_list = ReadAdjacencyListFromAdjacencyMaxtrix(vertex_count);
  int32_t vertex_from = 0;
  int32_t vertex_to = 0;
  std::tie(vertex_from, vertex_to) = ReadVerticesPair();
  if (vertex_to == vertex_from) {
    std::cout << 0 << '\n';
    return 0;
  }

  PrintResult(CalculatePath(adjacency_list, vertex_from, vertex_to));

  return 0;
}
