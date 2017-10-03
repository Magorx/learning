#include <iostream>
#include <vector>
#include <string>


template<typename T>
int32_t BinarySearch(std::vector<T> sorted_vector, T wanted_item) {
    int32_t left = -1;
    int32_t right = sorted_vector.size();
    while (left + 1 < right && sorted_vector[left] != wanted_item) {
        int32_t middle = (left + right) / 2;
        if (sorted_vector[middle] > wanted_item) {
            right = middle;
        } else {
            left = middle;
        }
    }
    if (sorted_vector[left] == wanted_item) {
        return left;
    } else {
        return -1;
    }
}

int main() {
    std::vector<std::string> sorted_vector {"hi", "by", "on", "hello"};
    std::string a = "by";
    std::cout << BinarySearch(sorted_vector, a) << '\n';
}
