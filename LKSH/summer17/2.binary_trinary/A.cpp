#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
std::vector<T> ReadVector(size_t length) {
    std::vector<T> objects(length);
    for (size_t i = 0; i < length; ++i) {
        std::cin >> objects[i];
    }
    return objects;
}

bool good_answer(std::vector<int32_t> ropes, int32_t answer, int32_t k) {
    for (size_t i = 0; i < ropes.size(); ++i) {
        k -= ropes[i] / answer;
    }
    return k <= 0;
}

template<typename T>
int32_t BinarySearch(std::vector<T> sorted_vector, int32_t k) {
    int32_t left = 0;
    int32_t right = 100000000;
    while (left + 1 < right) {
        int32_t middle = (left + right) / 2;
        if (good_answer(sorted_vector, middle, k)) {
            left = middle;
        } else {
            right = middle;
        }
    }   
    return left;
}

int main() {
    int32_t n = 0;
    int32_t k = 0;
    std::cin >> n >> k;
    std::vector<int32_t> ropes = ReadVector<int32_t>(n);

    std::cout << BinarySearch(ropes, k) << '\n';

    return 0;
}