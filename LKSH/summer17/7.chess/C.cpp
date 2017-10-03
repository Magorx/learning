#include <iostream>
#include <algorithm>

int main() {
    unsigned long long int w, h, x, y;
    std::cin >> w >> h >> x >> y;
    unsigned long long int horizontal_count = w - 1;
    unsigned long long int vertical_count = h - 1;
    unsigned long long int additional = std::min(x - 1, y - 1) + std::min(w - x, h - y) + std::min(w - x, y - 1) + std::min(x - 1, h - y);
    std::cout << horizontal_count + vertical_count + additional << '\n';
}