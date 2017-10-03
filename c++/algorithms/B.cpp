#include <iostream>
#include <vector>
#include <algorithm>

using Row = std::pair<int32_t, int32_t>;

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

    size_t maximum_index_of_sent_guy = 0;
    for (sie_t i = 0; i < people_count; ++ i) {
        for (sie_t j = 0; j < people_count; ++ j) {
            if (j == maximum_index_of_sent_guy) {
                std::cout << costs[j].second;
            }
        }
    }

    return 0;
}