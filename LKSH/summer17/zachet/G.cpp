#include <iostream>
#include <cstdint>
#include <vector>
#include <queue>

const char CONNECTING_SYMBOL = '*';

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

template<typename T>
void PrintMatrix(std::vector<Row<T>> matrix) {
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            std::cout << matrix[i][j];
        }
        std::cout << '\n';
    }
}

std::vector<int32_t> LineCoordToMatrix(int32_t line_coord, int32_t row_count) {
    return std::vector<int32_t> {line_coord % row_count, line_coord / row_count};
}

size_t MaxrixCoordToLine(size_t x, size_t y, size_t row_count) {
    return x + y * row_count;
}

std::vector<int32_t> bfs(std::vector<Row<int32_t>> adjacency_matrix, size_t start_vertex_index) {
    std::queue<size_t> to_visit;
    std::vector<int32_t> distances(adjacency_matrix.size(), 1e9 + 2);
    distances[start_vertex_index] = 0;
    to_visit.push(start_vertex_index);
    const size_t vertex_count = adjacency_matrix.size();
    std::vector<bool> visited(vertex_count, false);
    visited[start_vertex_index] = true;
    std::vector<int32_t> parents(vertex_count, -1);
    while (!to_visit.empty()) {
        const size_t cur_vertex_index = to_visit.front();
        to_visit.pop();
        for (size_t i = 0; i < vertex_count; ++i) {
            if (adjacency_matrix[cur_vertex_index][i] && !visited[i]) {
                to_visit.push(i);
                parents[i] = int32_t(cur_vertex_index);
                visited[i] = true;
                distances[i] = distances[cur_vertex_index] + 1;
            }
        }
    }

    return distances;
}

char GetCharFromMatrix(std::vector<Row<char>> char_matrix, size_t x, size_t y) {
    if (x >= 0 && y >= 0 && x < char_matrix.size() && y < char_matrix[0].size()) {
        return char_matrix[x][y];
    } else {
        return 0;
    }
}

int main() {
    int32_t n = 0, m = 0, k = 0;
    std::cin >> n >> m >> k;
    std::vector<Row<int>> matrix(n, Row<int>(n, 0));
    std::vector<int32_t> friends(k);
    for (int32_t i = 0; i < k; ++i) {
        std::cin >> friends[i];
        --friends[i];
    }

    for (int32_t i = 0; i < m; ++i) {
        int32_t a, b;
        std::cin >> a >> b;
        --a, --b;
        matrix[a][b] = 1;
        matrix[b][a] = 1;
    }

    int32_t min_dist = 1e9;
    int32_t from = -1, to = -1;
    if (from == 0 || to == 0) {
        return 0;
    }
    for (int32_t i = 0; i < k; ++i) {
        int32_t friend_index = friends[i];
        std::vector<int32_t> distances = bfs(matrix, friend_index);
        for (int32_t j = 0; j < k; ++j) {
            if (i == j) {
                continue;
            }
            int32_t new_friend_index = friends[j];
            if (distances[new_friend_index] < min_dist) {
                min_dist = distances[new_friend_index];
                from = friend_index + 1;
                to = new_friend_index + 1;
            }
        }
    }
    if (min_dist != 1e9) {
        std::cout << from << ' ' << to << ' ' << min_dist << '\n';
    } else {
        std::cout << -1 << '\n';
    }

    return 0;
}