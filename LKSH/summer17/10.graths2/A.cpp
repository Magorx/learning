#include <iostream>
#include <vector>
#include <queue>

template<typename T>
using Row = std::vector<T>

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

int main() {
    int32_t n = 0;
    std::cin >> n;
    std::vector<Row<int32_t>> board = ReadMatrix<int32_t>(n, n);
    std::queue<int32_t> to_visit;
    std::vector<char> visited (n, 0);

    to_visit.push(1)

}