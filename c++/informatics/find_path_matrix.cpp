#include <iostream>
#include <cstdint>
#include <algorithm>
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
void PrintVector(std::vector<T> random_vector) {
    for (size_t i = 0; i < random_vector.size(); ++i) {
        std::cout << random_vector[i];
        if (i < random_vector.size() - 1) {
            std::cout << ' ';
        }
    }
}

template<typename T>
void PrintMatrix(std::vector<Row<T>> matrix) {
    for (size_t i = 0; i < matrix.size(); ++i) {
        PrintVector(matrix[i]);
        std::cout << '\n';
    }
}

std::vector<int32_t> CalculateParents(std::vector<Row<int32_t>> adjacency_matrix, size_t start_vertex_index) {
    const size_t vertex_count = adjacency_matrix.size();
    std::queue<size_t> to_visit;
    to_visit.push(start_vertex_index);
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

std::vector<int32_t> GetPath(std::vector<int32_t> parents, 
                             int32_t start_vertex_index, int32_t end_vertex_index) {
    std::vector<int32_t> path;
    for (int32_t i = end_vertex_index; i != -1; i = parents[i]) {
        path.push_back(i + 1);
        if (i == start_vertex_index) {
            break;
        }
    }
    std::reverse(path.begin(), path.end());
    return path;
}

int main() {
    size_t vertex_count = 0;
    std::cin >> vertex_count;
    std::vector<Row<int32_t>> adjacency_matrix = ReadMatrix<int32_t>(vertex_count, vertex_count);
    size_t start_vertex_index = 0;
    size_t end_vertex_index = 0;
    std::cin >> start_vertex_index;
    std::cin >> end_vertex_index;
    if (start_vertex_index == end_vertex_index) {
        std::cout << 0 << '\n';
        return 0;
    }

    start_vertex_index -= 1;
    end_vertex_index -= 1;
    std::vector<int32_t> path = GetPath(CalculateParents(adjacency_matrix, start_vertex_index), start_vertex_index, end_vertex_index);

    if (path.size() == 0) {
        std::cout << -1;
        return 0;
    }
    std::cout << path.size() - 1 << '\n';
    PrintVector(path);
    std::cout << '\n';


    return 0;
}