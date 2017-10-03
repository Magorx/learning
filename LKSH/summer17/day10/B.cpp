#include <iostream>
#include <vector>
#include <queue>

template<typename T>
using Row = std::vector<T>;

template<typename T>
std::vector<T> ReadVector(size_t length) {
    std::vector<T> objects(length);
    for (size_t i = 0; i < length; ++i) {
        std::cin >> objects[i];
    }
    return objects;
}

template<typename T>
std::vector<Row<T>> ReadMatrix(size_t row_count, size_t column_count) {
    std::vector<Row<T>> matrix;
    matrix.reserve(row_count);
    for (size_t i = 0; i < row_count; ++i) {
        matrix.push_back(ReadVector<T>(column_count));
    }
    return matrix;
}

int main() {
    int32_t n = 0, m = 0;
    std::cin >> n >> m;
    int32_t start = 0, end = 0;
    std::cin >> start >> end;
    std::vector<Row<std::pair<int32_t, int32_t>>> adjecency_list (n, Row<std::pair<int32_t, int32_t>>());
    for (int32_t i = 0; i < m; ++i) {
        int32_t from, to;
        double cost;
        std::cin >> from >> to >> cost;
        adjecency_list[from].push_back(std::make_pair(to, cost / 100));
    }
    std::queue<int32_t> to_visit;
    std::vector<char> visited (n, 0);
    std::vector<double> costs (n, 0);
    to_visit.push(start);

    while (!to_visit.empty()) {
        int32_t cur_vertex = to_visit.front();
        to_visit.pop();
        std::cout << cur_vertex << '\n';
        for (auto new_vertex : adjecency_list[cur_vertex]) {
            double new_cost = (1.0 - (1.0 - costs[cur_vertex]) * (1.0 - new_vertex.second));
            if (!visited[new_vertex.first]) {
                to_visit.push(new_vertex.first);
                costs[new_vertex.first] = new_cost;
            } else if (new_cost < costs[new_vertex.first]) {
                costs[new_vertex.first] = new_cost;
                to_visit.push(new_vertex.first);
                visited[new_vertex.first] = 1;
            }
        }
    }

    std::cout << costs[end];

    return 0;
}