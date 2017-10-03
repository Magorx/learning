#include <iostream>
#include <vector>
#include <algorithm>

using Row = std::pair<size_t, size_t>;

template<typename T>
std::vector<T> ReadVectorOfPairs(size_t length) {
    std::vector<T> objects(length);
    for (size_t i = 0; i < length; ++i) {
        std::cin >> objects[i].first;
        objects[i].second = i + 1;
    }
    return objects;
}

template<typename T>
void PrintVector(std::vector<T> random_vector) {
    for (size_t i = 0; i < random_vector.size(); ++i) {
        std::cout << random_vector[i];
        if (i < random_vector.size() - 1) {
            std::cout << ' ';
        }
    }
}

int main() {
    size_t people_count = 0;
    std::cin >> people_count;
    std::vector<Row> distances = ReadVectorOfPairs<Row>(people_count);
    std::vector<Row> costs = ReadVectorOfPairs<Row>(people_count);

    std::sort(distances.begin(), distances.end());
    std::sort(costs.begin(), costs.end());
    std::reverse(costs.begin(), costs.end());

    size_t maximum_index_of_sent_guy = 1;
    for (size_t i = 0; i < people_count; ++i) {
        bool to_continue = false;
        for (size_t j = 0; j < people_count; ++j) {
            if (maximum_index_of_sent_guy == distances[j].second) {
                std::cout << costs[j].second << ' ';
                ++maximum_index_of_sent_guy;
                to_continue = true;
            }
            if (to_continue) {
                to_continue = false;
                continue;
            }
        }
    }
    std::cout << '\n';

    return 0;
}