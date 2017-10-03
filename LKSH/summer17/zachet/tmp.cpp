#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

template<typename T>
using Row = std::vector<T>;

struct Edge {
    int32_t from, to;
};



int main() {
    int32_t n = 0, m = 0, k = 0;
    std::cin >> n >> m >> k;
    std::vector<int32_t> friends_indexs(n);
    std::vector<Row<int32_t>> arr(m);
    std::vector<char> visited(m, 0);
    std::queue<int32_t> to_visit;

    for (int32_t i = 0; i < m; ++i) {
        int32_t a, b;
        std::cin >> a >> b;
        arr[a].push_back(b);
        arr[b].push_back(a);
    }

    for (int32_t i = 0; i < k; ++i) {
        int32_t cur_friend = friends_indexs[i];

    }

    return 0;
}