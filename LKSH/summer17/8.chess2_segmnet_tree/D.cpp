#include <iostream>

int main() {
    int32_t n, m;
    std::cin >> m >> n;
    if (n % 2 && m % 2) {
        std::cout << 2 << '\n';
    } else {
        std::cout << 1 << '\n';
    }

    return 0;
}