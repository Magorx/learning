#include <iostream>
#include <vector>

template<typename T>
using Row = std::vector<T>;

struct Coords {
    int32_t x = -1;
    int32_t y = -1;
};

int main() {
    int32_t m, n;
    std::cin >> m >> n;
    if (m == n) {
        if (m == 1) {
            std::cout << 2 << '\n';
            return 0;
        } else {
            std::cout << 1 << '\n';
            return 0;
        }
    }
    m--, n--;
    Coords shift1 {1, 2};
    Coords next_shift1 {2, 3};
    int32_t x = 0, y = 0;
    while (x <= m + 10 && y <= n + 10) {
        if ((shift1.x == 1 && x == m && y == n) || (shift1.x == 2 && x + 1 == m && y + 1 == n)) {
            std::cout << 2 << '\n';
            return 0;
        } else {
            x += shift1.x;
            y += shift1.y;
            std::swap(shift1, next_shift1);
        }
    }
    shift1 = Coords {2, 1};
    next_shift1 = Coords {3, 2};
    x = 0, y = 0;
    while (x <= m + 10 && y <= n + 10) {
        if ((shift1.x == 2 && x == m && y == n) || (shift1.x == 3 && x + 1 == m && y + 1 == n)) {
            std::cout << 2 << '\n';
            return 0;
        } else {
            x += shift1.x;
            y += shift1.y;
            std::swap(shift1, next_shift1);
        }
    }

    std::cout << 1 << '\n';

    return 0;
}