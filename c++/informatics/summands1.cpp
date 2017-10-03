#include <iostream>
#include <vector>

template<typename T>
void PrintVector(const std::vector<T>& random_vector) {
    for (size_t i = 0; i < random_vector.size(); ++i) {
        std::cout << random_vector[i];
        if (i < random_vector.size() - 1) {
            std::cout << ' ';
        }
    }
}

void MakeSummands(int32_t number, int32_t min_used_summand, int32_t sum, std::vector<int32_t>* summands) {
    if (sum > number) {
        return;
    }
    if (sum == number) {
        PrintVector(*summands);
        std::cout << '\n';
    } else {
        for (int32_t i = min_used_summand; i >= 1; --i) {
            summands->push_back(i);
            MakeSummands(number, i, sum + i, summands);
            summands->pop_back();
        }
    }
}

void MakeSummands(int32_t number) {
    std::vector<int32_t> summands;
    MakeSummands(number, number + 1, 0, &summands);
}

int main() {
    int32_t number = 0;
    std::cin >> number;
    MakeSummands(number);
}
