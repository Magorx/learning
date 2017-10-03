#include <iostream>
#include <vector>
#include <string>

const int32_t MODULE = 1e9 + 7;

template<typename T>
using Row = std::vector<T>;

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
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

int main() {
    int32_t n, k;
    std::cin >> n >> k;
    std::vector<Row<int32_t>> dinamic_array(2 * n + 1, Row<int32_t> (n, 0));
    dinamic_array[0][0] = 1;
    for (int32_t i = 1; i < n * 2 + 1; ++i) {
        for (int32_t j = 0; j < k + 1; ++j) {
            if (j == 0) {
                dinamic_array[i][j] = dinamic_array[i - 1][j + 1] % MODULE;
            } else {
                dinamic_array[i][j] = (dinamic_array[i - 1][j - 1] + dinamic_array[i - 1][j + 1])  % MODULE;
            }
        }
    }

    std::vector<Row<int32_t>> dinamic_array1(2 * n + 1, Row<int32_t> (n, 0));
    dinamic_array1[0][0] = 1;
    for (int32_t i = 1; i < n * 2 + 1; ++i) {
        for (int32_t j = 0; j < k; ++j) {
            if (j == 0) {
                dinamic_array1[i][j] = dinamic_array1[i - 1][j + 1] % MODULE;
            } else {
                dinamic_array1[i][j] = (dinamic_array1[i - 1][j - 1] + dinamic_array1[i - 1][j + 1]) % MODULE;
            }
        }
    }

    PrintMatrix(dinamic_array);
    std::cout << "====" << '\n';
    PrintMatrix(dinamic_array1);

    std::cout << ((dinamic_array[n * 2][0] - dinamic_array1[n * 2][0])  % MODULE + MODULE) % MODULE<< '\n';

    return 0;
}