#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

template<typename T>
using Row = std::vector<T>;

struct Coords {
  int32_t x = 0;
  int32_t y = 0;
  bool exists = true;
};

const std::vector<Coords> SHIFTS = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

template<typename T>
void PrintCollection(const T& collection, std::string separator=" ", std::string end="") {
  if (!(collection.end() - collection.begin()))
  return;

  for (auto i = collection.begin(); i != collection.end() - 1; ++i) {
  std::cout << *i << separator;
  }
  std::cout << (*(collection.end() - 1)) << end;
}

template<typename T>
void PrintMatrix(std::vector<Row<T>> matrix) {
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            std::cout << matrix[i][j];
        }
        std::cout << '\n';
    }
}

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
Coords FindInMatrix(const std::vector<Row<T>> matrix, const T& to_find) {
  for (size_t x = 0; x < matrix.size(); ++x) {
    for (size_t y = 0; y < matrix[x].size(); ++y) {
      if (matrix[x][y] == to_find) {
        return {static_cast<int32_t>(x), static_cast<int32_t>(y)};
      }
    }
  }

  return {-1, -1, false};
}

std::ostream& operator<<(std::ostream& output_stream, const Coords& coords) {
  output_stream << coords.x << ' ' << coords.y;
  return output_stream;
}

bool operator==(const Coords& first, const Coords& second) {
  return (first.x == second.x && first.y == second.y);
}

bool operator!=(const Coords& first, const Coords& second) {
  return (!(first == second));
}

bool RightCoord(int32_t coord, int32_t desk_size) {
  return (coord >= 0 && coord < desk_size);
}

bool RightCoords(Coords coords, int32_t desk_size) {
  return (RightCoord(coords.x, desk_size) && RightCoord(coords.y, desk_size));
}

std::vector<Row<Coords>> CalculateParents(const std::vector<Row<char>>& desk, Coords from_coords, Coords to_coords, 
                                          const std::vector<char>& wall_symbols) {
  const auto desk_row_count = desk.size();
  const auto desk_column_count = desk[0].size();
  std::queue<Coords> to_visit;
  to_visit.push(from_coords);
  std::vector<Row<char>> visited(desk_row_count, Row<char> (desk_column_count, 0));
  visited[from_coords.x][from_coords.y] = 1;
  for (size_t i = 0; i < desk_row_count; ++i) {
    for (size_t j = 0; j < desk_column_count; ++j) {
      if (std::find(wall_symbols.begin(), wall_symbols.end(), desk[i][j]) != wall_symbols.end()) {
        visited[i][j] = 1;
      }
    }
  }
  std::vector<Row<Coords>> parents(desk_row_count, Row<Coords>(desk_column_count, {-1, -1}));

  bool path_found = false;
  while (!to_visit.empty() && !path_found) {
    Coords cur_coords = to_visit.front();
    to_visit.pop();
    for (Coords shift : SHIFTS) {
      Coords new_coords {cur_coords.x + shift.x, cur_coords.y + shift.y};
      if (!RightCoord(new_coords.x, desk_row_count)
          || !RightCoord(new_coords.y, desk_column_count) 
          || visited[new_coords.x][new_coords.y]) {
        continue;
      }
      parents[new_coords.x][new_coords.y] = cur_coords;
      visited[new_coords.x][new_coords.y] = '.';
      if (new_coords == to_coords) {
        path_found = true;
      }
      to_visit.push(new_coords);
    }
  }
  return parents;
}

struct PathFound {
  bool exists = false;
  std::vector<Coords> path;
};

PathFound GetPath(const std::vector<Row<Coords>>& parents, Coords from_coords, Coords to_coords) {
  if (parents[to_coords.x][to_coords.y] == Coords {-1, -1}) {
    return {false, {}};
  }
  std::vector<Coords> way;
  for (Coords cur_coords = to_coords;
    parents[cur_coords.x][cur_coords.y] != Coords {-1, -1};
    cur_coords = parents[cur_coords.x][cur_coords.y]) {
    way.push_back(cur_coords);
  }
  way.push_back(from_coords);
  std::reverse(way.begin(), way.end());

  return {true, way};
}

PathFound CalculatePath(const std::vector<Row<char>>& desk, Coords from_coords, Coords to_coords, 
                                  const std::vector<char>& wall_symbols) {
  return GetPath(CalculateParents(desk, from_coords, to_coords, wall_symbols), from_coords, to_coords);
}

void SolveLabyrinth(const std::vector<Row<char>>& desk, Coords from_coords, Coords to_coords, 
                                      const std::vector<char>& wall_symbols, char marker) {
  auto path = CalculatePath(desk, from_coords, to_coords, wall_symbols);
  if (!path.exists) {
    std::cout << "N\n";
    return;
  }
  auto solved_desk = desk;
  for (int32_t i = 1; i < path.path.size(); ++i) {
    solved_desk[path.path[i].x][path.path[i].y] = marker;
  }
  std::cout << "Y\n";
  PrintMatrix(solved_desk);
}

int main() {
  int32_t desk_size = 0;
  std::cin >> desk_size;
  std::vector<Row<char>> desk = ReadMatrix<char>(desk_size, desk_size);
  Coords from_coords = FindInMatrix(desk, '@');
  Coords to_coords = FindInMatrix(desk, 'X');

  SolveLabyrinth(desk, from_coords, to_coords, {'0'}, '+');

  return 0;
}