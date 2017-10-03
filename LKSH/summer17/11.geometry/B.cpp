#include <iostream>
#include <vector>
#include <cmath>

const int32_t RIGHT = 1;
const int32_t LEFT = -1;

struct Coords {
    int32_t x, y;

    Coords(int32_t x, int32_t y) {
        this->x = x;
        this ->y = y;
    }
};

std::istream& operator<<(std::istream& input_stream, Coords coords) {
    input_stream >> coords.x >> coords.y;
    return input_stream;
}

struct Vector {
    int32_t x1, x2, y1, y2;
    int32_t x, y;

    void Vector(Coords begin, Coords end) {
        this->x = begin.x - end.x;
        this->y = begin.y - end.y;
    }

    void Rotate90(int32_t direction) {
        int32_t new_x = 0, new_y = 0;
        new_x = -this->y * direction;
        new_y = this->x * direction;
        this->x = new_x;
        this->y = new_y;
    }

    void Rotate180(int32_t direction) {
        for (int32_t i = 0; i < 2; ++i)
            this->Rotate90(direction);
    }
};

Vector operator+(Vector first, Vector second) {
    return Vector {first.x + second.x, first.y + second.y};
}

Vector operator-(Vector first, Vector second) {
    return Vector {first.x - second.x, first.y - second.y};
}

Vector operator*(Vector vector, int32_t integer) {
    return Vector {vector.x * integer, vector.y * integer};
}

Vector operator*(int32_t integer, Vector vector) {
    return Vector {vector.x * integer, vector.y * integer};
}

int32_t operator*(Vector first, Vector second) {
    return first.x * second.x + first.y * second.y;
}

int main() {
    Coords first, second, third;
    std::cin >> first >> second >> third;

    return 0;
}