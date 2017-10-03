#include <iostream>
#include <vector>
#include <queue>
#include <map>

const char CONNECTING_SYMBOL = '~';

template<typename T>
using Row = std::vector<T>;

struct Coords {
    int32_t x, y;
};

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

bool RightCoords(int32_t coord, int32_t desk_size) {
    return (coord >= 0 && coord < desk_size);
}

bool RightCoords(Coords coords, int32_t desk_size) {
    return (RightCoords(coords.x, desk_size) && RightCoords(coords.y, desk_size));
}

int32_t CountPointsInComponent(std::vector<Row<char>>& board, std::vector<Row<char>>& visited, Coords coords) {
    if (visited[coords.x][coords.y]) {
        return 0;
    }
    std::vector<Coords> shifts = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
    std::queue<Coords> to_visit;
    to_visit.push(coords);
    char last_symb = board[coords.x][coords.y];
    int32_t cnt = 0;
    while (!to_visit.empty()) {
        Coords cur_coords = to_visit.front();
        to_visit.pop();
        for (Coords shift : shifts) {
            Coords new_coords {cur_coords.x + shift.x, cur_coords.y + shift.y};
            if (!RightCoords(new_coords, board.size()) || visited[new_coords.x][new_coords.y]) {
                continue;
            }
            char cur_symb = board[new_coords.x][new_coords.y];
            if (cur_symb != last_symb) {
                continue;
            }
            ++cnt;
            visited[new_coords.x][new_coords.y] = 1;
            to_visit.push(new_coords);
        }
    }
    return cnt * (cnt - 1);
}

int main() {
    int32_t a = 11;
    std::vector<Row<char>> board = ReadMatrix<char>(a, a);
    std::vector<Row<char>> visited(a, Row<char> (a));
    std::map<char, int> result {{'R', 0}, {'G', 0}, {'B', 0}, {'V', 0}, {'Y', 0}};
    for (int32_t i = 0; i < a; ++i) {
        for (int32_t j = 0; j < a; ++j) {
            result[board[i][j]] = std::max(CountPointsInComponent(board, visited, Coords {i, j}), result[board[i][j]]);
        }
    }

    std::cout << "R: " << result['R'] << '\n';
    std::cout << "G: " << result['G'] << '\n';
    std::cout << "B: " << result['B'] << '\n';
    std::cout << "Y: " << result['Y'] << '\n';
    std::cout << "V: " << result['V'] << '\n';

    return 0;
}
