#include <iostream>
#include <vector>
#include <string>

template<typename T>
using Row = std::vector<T>;

template<typename T>
using Matrix = std::vector<Row<T>>;

struct Coords {
    int32_t x, y;
};

struct Text {
    Coords coords;
    std::string text;
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

class Canvas {
    int32_t column_count, row_count;
    Matrix<char> up_left_corner;
    Matrix<char> up_right_corner;
    Matrix<char> down_left_corner;
    Matrix<char> down_right_corner;
    Matrix<char> up;
    Matrix<char> down;
    Matrix<char> left;
    Matrix<char> right;
    std::vector<Canvas> canvases;
    std::vector<Text> texts;

    // void draw() {
    //     for (int32_t i = 0; i < column_count; ++i) {
    //         for (int32_t j = 0; j < row_count; ++j) {
    //             if (i < this->up_left_corner.size())
    //         }
    //     }
    // }
};

int main() {
    std::goto(1, 1);

    return 0;
}
