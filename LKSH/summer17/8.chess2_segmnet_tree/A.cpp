#include <iostream>
#include <vector>
#include <string>

typedef unsigned long long int big_uint;

struct SegmentTree {
    std::vector<big_uint> data;
    big_uint data_size;

    SegmentTree(big_uint n) {
        this->data = std::vector<big_uint> (4 * n, 0);
        this->data_size = n * 4;
    }

    void set(big_uint vertex, big_uint left, big_uint right, big_uint index, big_uint value) {
        if (right - left <= 1) {
            this->data[vertex] = value;
            return;
        }
        big_uint middle = (left + right) / 2;
        if (index < middle) {
            this->set(2 * vertex, left, middle, index, value);
        } else {
            this->set(2 * vertex + 1, middle, right, index, value);
        }
        this->data[vertex]  = this->data[2 * vertex] + this->data[2 * vertex + 1];
    }

    void set(big_uint index, big_uint value) {
        this->set(1, 0, this->data_size / 4, index, value);
    }

    big_uint sum(big_uint vertex, big_uint left, big_uint right, big_uint q_left, big_uint q_right) {
        if (q_right <= left || q_left >= right) {
            return 0;
        } else if (q_left <= left && right <= q_right) {
            return this->data[vertex];
        } else {
            big_uint middle = (left + right) / 2;
            return this->sum(2 * vertex, left, middle, q_left, q_right) + this->sum(2 * vertex + 1, middle, right, q_left, q_right);
        }
    }

    big_uint sum(big_uint q_left, big_uint q_right) {
        return this->sum(1, 0, this->data_size / 4, q_left, q_right);
    }
};

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
    big_uint port_count = 0;
    big_uint question_count = 0;
    std::cin >> port_count >> question_count;
    SegmentTree tree = SegmentTree(port_count);

    for (big_uint i = 0; i < question_count; ++i) {
        std::string type;
        big_uint first, second;
        std::cin >> type >> first >> second;
        if (type == "A") {
            tree.set(first - 1, second);
        } else {
            std::cout << tree.sum(first - 1, second) << '\n';
        }
    }

    return 0;
}