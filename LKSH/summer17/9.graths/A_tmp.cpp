#include <iostream>
#include <vector>
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

char GetCharFromMatrix(std::vector<Row<char>> char_matrix, size_t x, size_t y) {
    if (x >= 0 && y >= 0 && x < char_matrix.size() && y < char_matrix[0].size()) {
        return char_matrix[x][y];
    } else {
        return 0;
    }
}

size_t MaxrixCoordToLine(size_t x, size_t y, size_t row_count) {
    return x + y * row_count;
}

std::vector<int32_t> LineCoordToMatrix(int32_t line_coord, int32_t row_count) {
    return std::vector<int32_t> {line_coord % row_count, line_coord / row_count};
}

std::vector<Row<int32_t>> CharMatrixToAdjacencyList(std::vector<Row<char>> char_matrix) {
    const size_t row_count = char_matrix.size();
    const size_t column_count = char_matrix[0].size();
    const size_t vertex_count = column_count * row_count;
    const std::vector<Row<int32_t>> coord_shifts {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    std::vector<Row<int32_t>> adjacency_list(vertex_count, Row<int32_t>(0));
    for (size_t x = 0; x < row_count; ++x) {
        for (size_t y = 0; y < column_count; ++y) {
            char cur_vertex_symb = char_matrix[x][y];
            for (size_t shift_index = 0; shift_index < coord_shifts.size(); ++shift_index) {
                const std::vector<int32_t> shift = coord_shifts[shift_index]; 
                const int32_t new_x = x + shift[0];
                const int32_t new_y = y + shift[1];

                char adjacency_symb = GetCharFromMatrix(char_matrix, new_x, new_y);
                if (!adjacency_symb) {
                    continue;
                }
                if (adjacency_symb == cur_vertex_symb || cur_vertex_symb == CONNECTING_SYMBOL || adjacency_symb == CONNECTING_SYMBOL) {
                    adjacency_list[MaxrixCoordToLine(x, y, row_count)].push_back(MaxrixCoordToLine(new_x, new_y, row_count));
                }
            }
        }
    }

    return adjacency_list;
}

std::map<char, int32_t>* DeathFirstSearch(std::vector<Row<int32_t>>& board, int32_t cur_vertex_index, 
                      std::vector<char>* visited=nullptr, std::map<char, int32_t>* result=nullptr,
                      char last_symbol=' ') {
    bool allocated_memory = false;
    if (visited == nullptr || result == nullptr) {
        visited = new std::vector<char> (board.size(), 0);
        result = new std::map<char, int32_t> {{'R', 0}, {'G', 0}, {'B', 0}, {'V', 0}, {'Y', 0}};
        allocated_memory = true;
    }
    visited->at(cur_vertex_index) = 1;
    std::vector<int32_t> cur_coords = LineCoordToMatrix(cur_vertex_index, board.size());
    char cur_symbol = board[cur_coords[0]][cur_coords[1]];
    if (cur_symbol == last_symbol) {
        (*result)[cur_symbol] = (*result)[cur_symbol] + 1;
    }
    //std::cout << "> " << cur_vertex_index << '\n';
    for (size_t connected_vertex_index: board[cur_vertex_index]) {
        if (visited->at(connected_vertex_index) == 0) {
            visited->at(connected_vertex_index) = 1;
            //std::cout << cur_vertex_index << " -> " << connected_vertex_index << '\n';
            DeathFirstSearch(board, connected_vertex_index, visited, result, cur_symbol);
        }
    }
    if (allocated_memory) {
        delete visited;
    }
    return result;
}

std::vector<Row<char>> board;

int main() {
    int32_t board_size =  11;
    board = ReadMatrix<char>(board_size, board_size);
    std::vector<Row<int32_t>> a = CharMatrixToAdjacencyList(board);
    int32_t b = 0;
    auto result = DeathFirstSearch(a, b);
    std::cout << (*result)['R'];

    return 0;
}
