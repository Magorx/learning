#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

template<typename T>
std::vector<T> ReadVector(size_t length) {
    std::vector<T> objects(length);
    for (size_t i = 0; i < length; ++i) {
        std::cin >> objects[i];
    }
    return objects;
}

double foo(double x, int32_t a, int32_t b, int32_t c, int32_t d) {
    return a * x * x * x + b * x * x + c * x + d;
}

double BinarySearch(int32_t a, int32_t b, int32_t c, int32_t d) {
    double left = 1e-7;
    double right = 1e7;
    for (int32_t i = 0; i < 50; ++i) {
        double middle = (left + right) / 2;
        if ((foo(middle, a, b, c, d) > 0) == (foo(left, a, b, c, d) > 0)) {
            left = middle;
        } else {
            right = middle;
        }
    }
    return left;
}

int main() {
    int32_t a, b, c, d;
    std::cin >> a >> b >> c >> d;
    std::cout << BinarySearch(a, b, c, d) << '\n';

    return 0;
}
