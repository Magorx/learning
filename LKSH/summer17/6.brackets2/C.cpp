#include <iostream>
#include <vector>
#include <string>

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
    --k;
    std::vector<Row<int32_t>> dinamic_array(2 * n + 1, Row<int32_t> (n, 0));
    dinamic_array[0][0] = 1;
    for (int32_t i = 1; i < n * 2 + 1; ++i) {
        for (int32_t j = 0; j < n + 1; ++j) {
            if (j == 0) {
                dinamic_array[i][j] = dinamic_array[i - 1][j + 1];
            } else {
                dinamic_array[i][j] = dinamic_array[i - 1][j - 1] + dinamic_array[i - 1][j + 1];
            }
        }
    }

    PrintMatrix(dinamic_array);
    std::cout << "=====" << dinamic_array.size() << '\n';

    std::string string = "(";
    int32_t balance = 1;
    std::cout << n << ' ' << k << '\n';
    for (int32_t i = 1; i < n * 2; ++i) {
        std::cout << i << ") " << string << ' ' << balance << ' ' << k << '\n';
        if (k < dinamic_array[i][balance + 1]) {
            string = string + '(';
            k -= dinamic_array[i][balance + 1];
            ++balance;
        } else {
            string = string + ')';
            k -= dinamic_array[i][balance + 1];
            --balance;
        }
    }

    std::cout << string << '\n';

    return 0;
}