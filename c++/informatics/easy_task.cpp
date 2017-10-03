#include <iostream>
#include <vector>

template<typename T>
using Row = std::vector<T>;

template<typename T>
std::vector<T> ReadVector(int32_t length) {
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

int main() {
    size_t hill_count = 0;
    std::cin >> hill_count;
    const std::vector<Row<int32_t>> adjacency_matrix = ReadMatrix(hill_count, hill_count);
    const std::vector<int32_t> colors = ReadRow(hill_count);

    int32_t bad_bridge_count = 0;
    for (size_t i = 0; i < hill_count; ++i) {
        for (size_t j = i + 1; j < hill_count; ++j) {
            if (adjacency_matrix[i][j] && colors[i] != colors[j]) {
                ++bad_bridge_count;
            }
        }
    }
 
    std::cout << bad_bridge_count << '\n';
 
    return 0;
}
