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
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

void DeathFirstSearch(std::vector<Row<size_t>>& adjacency_list, size_t cur_vertex_index, 
         std::vector<char>* visited=nullptr, std::vector<int32_t>* parents=nullptr) {
    const bool allocated_memory = false;
    if (visited == nullptr || parents == nullptr) {
        visited = new std::vector<char> (adjacency_list.size(), 0);
        parents = new std::vector<int32_t> (adjacency_list.size(), -1);
        allocated_memory = true;
    }
    visited->at(cur_vertex_index) = 1;
    std::cout << "> " << cur_vertex_index << '\n';
    for (size_t connected_vertex_index: adjacency_list[cur_vertex_index]) {
        if (visited->at(connected_vertex_index) == 0) {
            visited->at(connected_vertex_index) = 1;
            parents->at(connected_vertex_index) = cur_vertex_index;
            std::cout << cur_vertex_index << " -> " << connected_vertex_index << '\n';
            DeathFirstSearch(adjacency_list, connected_vertex_index, visited, parents);
        }
    }
    if (allocated_memory) {
        delete visited;
        delete parents;
    }
}

int main() {
    std::vector<Row<size_t>> adjacency_list {{2, 1}, {2, 3, 0}, {3, 4, 0, 1}, {2, 4}, {2, 3}};
    DeathFirstSearch(adjacency_list, 0);

    return 0;
}