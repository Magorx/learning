#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

int32_t ShiftIntRight(int32_t n) {
    return n % 10 * 1000 + (n % 100 - n % 10) / 10 + (n % 1000 - n % 100) / 10 + n / 1000 * 100;
}

int32_t ShiftIntLeft(int32_t n) {
    return n / 1000 + (n % 10) * 10 + (n % 100 - n % 10) * 10 + (n % 1000 - n % 100) * 10;
}

int main() {
    int n1 = 0, n2 = 0;
    std::cin >> n1 >> n2;

    std::queue<int32_t> to_visit;
    std::vector<std::pair<int32_t, int32_t>> parents (10000, std::make_pair(-1, -1));
    std::vector<char> visited (0, 0);
    to_visit.push(n1);
    visited[n1] = 1;
    std::cout << n1;

    while (!to_visit.empty()) {
        int32_t n = to_visit.front();
        std::cout << '>' << n << '\n';
        to_visit.pop();

        if (n == n2) {
            break;
        }

        std::vector<int32_t> new_ints {ShiftIntLeft(n), ShiftIntRight(n), n + 1000, n - 1};

        for (int32_t new_n : new_ints) {
            if (n / 1000 < 10 && n % 10 > 0 && !visited[n]) {
                to_visit.push(new_n);
                visited[new_n] = true;
                if (parents[new_n].first < 0 || (parents[new_n].first > parents[n].first + 1)){
                    parents[new_n] = std::make_pair(parents[n].first + 1, n);
                }
            }
        }

        visited[n] = 1;
    }

    std::vector<int32_t> way;
    for (int32_t i = n2; parents[i].second != -1; i = parents[i].second) {
        //std::cout << i << '\n';
        way.push_back(parents[i].second);
    }
    std::reverse(way.begin(), way.end());

    for (int32_t i = 0; i < static_cast<int32_t>(way.size()); ++i) {
        std::cout << way[i] << '\n';
    }
    std::cout << n2 << '\n';

    return 0;
}