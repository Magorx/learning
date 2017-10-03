#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

template<typename T>
using Row = std::vector<T>;

template<typename T>
void PrintCollection(const T& collection, std::string separator=" ", std::string end="") {
  if (!(collection.end() - collection.begin()))
    return;

  for (auto i = collection.begin(); i != collection.end() - 1; ++i) {
    std::cout << *i << separator;
  }
  std::cout << *(collection.end() - 1) << end;
}

struct Coords {
    int32_t x = -1;
    int32_t y = -1;
};

std::vector<Coords> KNIGHT_SHIFTS = {{-1, -2}, {1, -2}, {2, -1}, {2, 1}, {1, 2}, {-1, 2}, {-2, -1}, {-2, 1}};


bool operator==(const Coords& first, const Coords& second) {
    return (first.x == second.x && first.y == second.y);
}

bool operator!=(const Coords& first, const Coords& second) {
    return (!(first == second));
}

std::ostream& operator<<(std::ostream& output_stream, const Coords& coords) {
    output_stream << coords.x + 1 << ' ' << coords.y + 1;
    return output_stream;
}

std::istream& operator>>(std::istream& input_stream, Coords& coords) {
  input_stream >> coords.x >> coords.y;
  --coords.x;
  --coords.y;
  return input_stream;
}

bool RightCoord(int32_t coord, int32_t desk_size) {
    return (coord >= 0 && coord < desk_size);
}

bool RightCoords(Coords coords, int32_t desk_size) {
    return (RightCoord(coords.x, desk_size) && RightCoord(coords.y, desk_size));
}

std::vector<Row<Coords>> CalculateParents(int32_t desk_size, Coords knight_coords, Coords goal_coords) {
  std::queue<Coords> to_visit;
  to_visit.push(knight_coords);
  std::vector<Row<char>> visited(desk_size, Row<char> (desk_size, 0));
  visited[knight_coords.x][knight_coords.y] = 1;
  std::vector<Row<Coords>> parents(desk_size, Row<Coords> (desk_size, {-1, -1}));

  bool path_found = false;
  while (!to_visit.empty() && !path_found) {
      Coords cur_coords = to_visit.front();
      to_visit.pop();
      for (Coords shift : KNIGHT_SHIFTS) {
          Coords new_coords {cur_coords.x + shift.x, cur_coords.y + shift.y};
          if (!RightCoords(new_coords, desk_size) || visited[new_coords.x][new_coords.y]) {
              continue;
          }
          parents[new_coords.x][new_coords.y] = cur_coords;
          visited[new_coords.x][new_coords.y] = 1;
          if (new_coords == goal_coords) {
              path_found = true;
          }
          to_visit.push(new_coords);
      }
  }
  return parents;
}

std::vector<Coords> GetPath(const std::vector<Row<Coords>>& parents, Coords knight_coords, Coords goal_coords) {
  std::vector<Coords> way;
  for (Coords cur_coords = goal_coords;
       parents[cur_coords.x][cur_coords.y] != Coords {-1, -1};
       cur_coords = parents[cur_coords.x][cur_coords.y]) {
      way.push_back(cur_coords);
  }
  way.push_back(knight_coords);
  std::reverse(way.begin(), way.end());

  return way;
}

std::vector<Coords> CalculatePath(int32_t desk_size, Coords knight_coords, Coords goal_coords) {
  return GetPath(CalculateParents(desk_size, knight_coords, goal_coords), knight_coords, goal_coords);
}

void PrintResult(std::vector<Coords> way) {
  std::cout << way.size() - 1 << '\n';
  PrintCollection(way, "\n", "\n");
}

int main() {
    int32_t desk_size = 0;
    std::cin >> desk_size;
    Coords knight_coords;
    Coords goal_coords;
    std::cin >> knight_coords >> goal_coords;

    PrintResult(CalculatePath(desk_size, knight_coords, goal_coords));

    return 0;
}