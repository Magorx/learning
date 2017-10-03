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
    Coords shift {1, 2};
    Coords next_shift {2, 3};
    int32_t x = 0, y = 0;
    int32_t x2 = 1, y2 = 1;
    while (x <= m + 1 && y <= n + 11) {
        // std::cout << x << ' ' << y << '\n';
        if (shift.x == 1) {
            if (x == m && y == n) {
                std::cout << 2 << '\n';
                return 0;
            }
        } else if (x2 == m && y2 == n) {
            std::cout << 2 << '\n';
            return 0;
        }
        x += shift.x;
        y += shift.y;
        x2 += shift.x;
        y2 += shift.y;
        std::swap(shift, next_shift);
    }
    shift = Coords {2, 1};
    next_shift = Coords {3, 2};
    x = 0, y = 0;
    x2 = 1, y2 = 1;
    while (x <= m + 1 && y <= n + 11) {
        // std::cout << x << ' ' << y << '\n';
        if (shift.x == 2) {
            if (x == m && y == n) {
                std::cout << 2 << '\n';
                return 0;
            }
        } else if (x2 == m && y2 == n) {
            std::cout << 2 << '\n';
            return 0;
        }
        x += shift.x;
        y += shift.y;
        x2 += shift.x;
        y2 += shift.y;
        std::swap(shift, next_shift);
    }

    std::cout << 1 << '\n';

    return 0;
}