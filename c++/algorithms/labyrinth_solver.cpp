#include <iostream>
#include <cstdint>
#include <vector>
#include <queue>

const char CONNECTING_SYMBOL = '*';

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
void PrintMatrix(std::vector<Row<T>> matrix) {
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            std::cout << matrix[i][j];
        }
        std::cout << '\n';
    }
}

std::vector<int32_t> LineCoordToMatrix(int32_t line_coord, int32_t row_count) {
    return std::vector<int32_t> {line_coord % row_count, line_coord / row_count};
}

size_t MaxrixCoordToLine(size_t x, size_t y, size_t row_count) {
    return x + y * row_count;
}

std::vector<int32_t> bfs(std::vector<Row<int32_t>> adjacency_matrix, size_t start_vertex_index) {
    std::queue<size_t> to_visit;
    to_visit.push(start_vertex_index);
    const size_t vertex_count = adjacency_matrix.size();
    std::vector<bool> visited(vertex_count, false);
    visited[start_vertex_index] = true;
    std::vector<int32_t> parents(vertex_count, -1);
    while (!to_visit.empty()) {
        const size_t cur_vertex_index = to_visit.front();
        to_visit.pop();
        for (size_t i = 0; i < vertex_count; ++i) {
            if (adjacency_matrix[cur_vertex_index][i] && !visited[i]) {
                to_visit.push(i);
                parents[i] = int32_t(cur_vertex_index);
                visited[i] = true;
            }
        }
    }

    return parents;
}

char GetCharFromMatrix(std::vector<Row<char>> char_matrix, size_t x, size_t y) {
    if (x >= 0 && y >= 0 && x < char_matrix.size() && y < char_matrix[0].size()) {
        return char_matrix[x][y];
    } else {
        return 0;
    }
}

std::vector<Row<int32_t>> CharMatrixToAdjacency(std::vector<Row<char>> char_matrix) {
    const size_t row_count = char_matrix.size();
    const size_t column_count = char_matrix[0].size();
    const size_t vertex_count = column_count * row_count;
    const std::vector<Row<int32_t>> coord_shifts {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    std::vector<Row<int32_t>> adjacency_matrix(vertex_count, Row<int32_t>(vertex_count, 0));
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
                    adjacency_matrix[MaxrixCoordToLine(x, y, row_count)]
                                    [MaxrixCoordToLine(new_x, new_y, row_count)] = 1;
                }
            }
        }
    }

    return adjacency_matrix;
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

std::vector<Row<char>> SolveLabyrinth(std::vector<Row<char>> labyrinth, size_t x_from, size_t y_from, 
                                       size_t x_to, size_t y_to) {
    std::vector<Row<int32_t>> adjacency_matrix = CharMatrixToAdjacency(labyrinth);
    const size_t line_coord_from = MaxrixCoordToLine(x_from, y_from, labyrinth.size());
    const size_t line_coord_to = MaxrixCoordToLine(x_to, y_to, labyrinth.size());
    std::vector<int32_t> parents = bfs(adjacency_matrix, line_coord_from);
    std::vector<Row<int32_t>> way {{int32_t(x_to), int32_t(y_to)}};
    for (int32_t i = line_coord_to; parents[i] != -1; i = parents[i]) {
        way.push_back(LineCoordToMatrix(parents[i], labyrinth.size()));
    }
    for (std::vector<int32_t> coords: way) {
        int32_t x = coords[0];
        int32_t y = coords[1];
        labyrinth[x][y] = 'X';
    }
    return labyrinth;
}


int main() {
    size_t row_count = 0;
    size_t column_count = 0;
    std::cin >> row_count >> column_count;
    const std::vector<Row<char>> adjacency_matrix = ReadMatrix<char>(row_count, column_count);
    size_t x_from = 0;
    size_t y_from = 0;
    size_t x_to = 0;
    size_t y_to = 0;
    std::cin >> x_from >> y_from >> x_to >> y_to;
    std::cout << '\n';
    PrintMatrix(SolveLabyrinth(adjacency_matrix, x_from, y_from, x_to, y_to));

    return 0;
}