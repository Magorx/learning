#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
std::vector<T> ReadVector(size_t length) {
    std::vector<T> objects(length);
    for (size_t i = 0; i < length; ++i) {
        std::cin >> objects[i];
    }
    return objects;
}

template<typename T>
int32_t BinarySearch(std::vector<T> sorted_vector, T wanted_item) {
    int32_t left = -1;
    int32_t right = sorted_vector.size();
    while (left + 1 < right && sorted_vector[left] != wanted_item) {
        int32_t middle = (left + right) / 2;
        if (sorted_vector[middle] > wanted_item) {
            right = middle;
        } else {
            left = middle;
        }
    }
    if (sorted_vector[left] == wanted_item) {
        return left;
    } else {
        return -1;
    }
}

struct Question{
    int32_t left, right, x;
};

std::istream& operator>>(std::istream& input_stream, Question& question) {
    input_stream >> question.left >> question.right >> question.x;
    return input_stream;
}

struct Town{
    int32_t people, id;
};

int32_t MAXIMUM_TOWN_ID = 0;
std::istream& operator>>(std::istream& input_stream, Town& town) {
    ++MAXIMUM_TOWN_ID;
    town.id = MAXIMUM_TOWN_ID;
    input_stream >> town.people;
    return input_stream;
}

bool operator<(Town first, Town second) {
    if (first.people < second.people) {
        return true;
    } else if (first.people > second.people) {
        return false;
    } else {
        if (first.id < second.id) {
            return true;
        } else {
            return false;
        }
    }
}

std::ostream& operator<<(std::ostream& output_stream, Town town) {
    output_stream << '<' << "Town " << town.id << '|' << town.people << '>';
    return output_stream;
}

std::ostream& operator<<(std::ostream& output_stream, Question question) {
    output_stream << '<' << "Question " << question.left << '-' << question.right << '|' << question.x << '>';
    return output_stream;
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
    int32_t n = 0;
    std::cin >> n;
    std::vector<Town> towns = ReadVector<Town>(n);
    std::sort(towns.begin(), towns.end());
    int32_t question_count = 0;
    std::cin >> question_count;
    std::vector<Question> questions = ReadVector<Question>(question_count);

    // PrintVector(towns);
    // std::cout << '\n';
    // PrintVector(questions);
    // std::cout << '\n';

    for (int32_t i = 0; i < question_count; ++i) {
        Question question = questions[i];
        auto answer = std::lower_bound(towns.begin(), towns.end(), Town {question.x, question.left});
        // std::cout << *answer << ' ' << question;
        if (answer != towns.end()) {
            if (answer->id <= question.right && answer->id >= question.left && answer->people == question.x) {
                std::cout << 1;
            } else {
                std::cout << 0;
            }
        } else {
            std::cout << 0;
        }
        // std::cout << '\n';
    }
    std::cout << '\n';

    return 0;
}
