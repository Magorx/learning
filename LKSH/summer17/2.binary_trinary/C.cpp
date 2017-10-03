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

double time(double x, double a, double v1, double v2) {
    return std::sqrt((1 - a) * (1 - a) + x * x) / v1 + std::sqrt(a * a + (1 - x) * (1 - x)) / v2;
}

double TrinarySearch(double a, double v1, double v2) {
    double left = 0;
    double right = 1;
    for (int32_t i = 0; i < 400; ++i) {
        //std::cout << left << ' ' << right << '\n';
        double m1 = left + (right - left) / 3;
        double m2 = left + 2 * (right - left) / 3;
        if (time(m1, a, v1, v2) < time(m2, a, v1, v2)) {
            right = m2;
        } else {
            left = m1;
        }
    }
    return left;
}

int main() {
    double a, v1, v2;
    std::cin >> v1 >> v2 >> a;

    std::cout.precision(7);
    std::cout << TrinarySearch(a, v1, v2) << '\n';

    return 0;
}