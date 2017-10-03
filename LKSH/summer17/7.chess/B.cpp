#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

template<typename T>
using Row = std::vector<T>;

struct Coords {
    int32_t x = -1;
    int32_t y = -1;
};

struct Figure {
    int32_t x,  y;
    std::vector<Coords> shifts;
    int32_t id;
};

std::vector<Coords> KNIGHT_SHIFTS = {{-1, -2}, {1, -2}, {2, -1}, {2, 1}, {1, 2}, {-1, 2}, {-2, -1}, {-2, 1}};


bool operator==(const Coords& first, const Coords& second) {
    return (first.x == second.x && first.y == second.y);
}

bool operator!=(const Coords& first, const Coords& second) {
    return (!(first.x == second.x && first.y == second.y));
}

std::ostream& operator<<(std::ostream& output_stream, const Coords& coords) {
    output_stream << coords.x << ' ' << coords.y;
    return output_stream;
}

std::string itos(int32_t num) {
    std::string result;
    while (num > 9) {
        result += char(num % 10 + '0');
        num /= 10;
    }
    result += char(num % 10 + '0');
    std::reverse(result.begin(), result.end());
    return result;
}

Coords DeskCoordsToCoords(const std::string& coord) {
    return {coord[0] - 'a', static_cast<int32_t>(coord[1] - '1')};
}

std::string CoordsToDeskCoords(Coords coords) {
    return char(coords.x + 'a') + itos(coords.y + 1);
}

bool RightCoords(int32_t coord, int32_t desk_size) {
    return (coord >= 0 && coord < desk_size);
}

bool RightCoords(Coords coords, int32_t desk_size) {
    return (RightCoords(coords.x, desk_size) && RightCoords(coords.y, desk_size));
}

int main() {
    int32_t desk_row_count = 8;
    int32_t desk_column_count = 8;
    std::vector<Row<int32_t>> desk(desk_row_count, Row<int32_t> (desk_column_count, 0));

    int32_t figure_count = 2;
    std::vector<Figure> figures;
    std::vector<Coords> goals;

    for (int32_t i = 0; i < figure_count; ++figure_count) {
        std::string raw_coords;
        std::cin >> raw_coords;
        Coords coords = DeskCoordsToCoords(raw_coords);
        Figure figure {coords.x, coords.y, KNIGHT_SHIFTS, i};
        figures.push_back(figure);
    }
    for (int32_t i = 0; i < figure_count; ++figure_count) {
        std::string raw_coords;
        std::cin >> raw_coords;
        Coords coords = DeskCoordsToCoords(raw_coords);
        goals.push_back(coords);
    }    

    std::queue<Figure> to_visit;
    to_visit.push(figures[0]);
    to_visit.push(figures[1]);
    std::vector<Row<char>> visited(desk_row_count, Row<char> (desk_column_count, 0));
    visited[knight_one.x][knight_one.y] = 1;
    visited[knight_two.x][knight_two.y] = 1;
    std::vector<Row<Coords>> parents(desk_row_count, Row<Coords> (desk_column_count, {-1, -1}));

    bool done = false;
    while (!to_visit.empty() && !done) {
        Figure cur_figure = to_visit.front();
        to_visit.pop();
        for (Coords shift : cur_figure.shifts) {
            Coords new_coords {cur_figure.x + shift.x, cur_figure.y + shift.y};
            if (!RightCoords(new_coords, desk_row_count) || visited[new_coords.x][new_coords.y]) {
                continue;
            }
            parents[new_coords.x][new_coords.y] = Coords {cur_figure.x, cur_figure.y};
            visited[new_coords.x][new_coords.y] = 1;
            if (new_coords == goal_coords) {
                done = true;
            }
            to_visit.push(Figure {new_coords, cur_figure.shifts});
        }
    }

    std::vector<Coords> way;
    for (Coords cur_coords = goal_coords;
         parents[cur_coords.x][cur_coords.y] != Coords {-1, -1};
         cur_coords = parents[cur_coords.x][cur_coords.y]) {
        way.push_back(cur_coords);
    }
    way.push_back(knight_coords);
    std::reverse(way.begin(), way.end());

    for (Coords cur_coords : way) {
        std::cout << char(cur_coords.x + 'a') << cur_coords.y + 1 << '\n';
    }

    return 0;
}