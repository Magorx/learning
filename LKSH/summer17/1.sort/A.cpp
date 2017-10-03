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
    int32_t people_count = 0;
    size_t bus_count = 0;
    std::cin >> people_count >> bus_count;
    std::vector<Row> busses = ReadVectorOfPairs<Row>(bus_count);

    int32_t summary_people_taken = 0;
    bool all_taken = false;
    std::vector<int32_t> buses_chosen;
    std::sort(busses.begin(), busses.end());
    for (int32_t i = bus_count - 1; i >= 0; --i) {
        summary_people_taken += busses[i].first;
        buses_chosen.push_back(busses[i].second);
        if (summary_people_taken >= people_count) {
            all_taken = true;
            break;
        }
    }

    if (all_taken) {
        std::cout << buses_chosen.size() << '\n';;
        PrintVector(buses_chosen);
        std::cout << '\n';
    } else {
        std::cout << -1 << '\n';
    }

    return 0;
}