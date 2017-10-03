#include <iostream>
#include <cstdint>
#include <vector>
#include <queue>

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

std::vector<int32_t> BreathFirstSearch(std::vector<Row<int32_t>> adjacency_matrix, size_t start_vertex_index) {
    std::queue<size_t> to_visit;
    to_visit.push(start_vertex_index);
    const size_t vertex_count = adjacency_matrix.size();
    std::vector<bool> visited(vertex_count, false);
    visited[start_vertex_index] = true;
    std::vector<int32_t> parents(vertex_count, -1);
    while (!to_visit.empty()) {
        x, y = q.pop()
        for (shift in shifts) :
            tmp_x = x + shift[0]
            tmp_y = y + shift[1]

    }

    return parents;
}


int main() {

    return 0;
}