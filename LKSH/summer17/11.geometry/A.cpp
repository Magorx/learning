#include <iostream>
#include <vector>
#include <cmath>

const int32_t RIGHT = 1;
const int32_t LEFT = -1;
const double PI = 3.1415926535;

struct Coords {
    int32_t x, y;

    Coords(int32_t x, int32_t y) {
        this->x = x;
        this ->y = y;
    }

    Coords() {
        this->x = 0;
        this ->y = 0;
    }
};

Coords operator-(Coords first, Coords second) {
    return {first.x - second.x, first.y - second.y};
}

std::istream& operator>>(std::istream& input_stream, Coords& coords) {
    input_stream >> coords.x >> coords.y;
    return input_stream;
}

std::ostream& operator<<(std::ostream& output_stream, Coords coords) {
    output_stream << coords.x << ' ' << coords.y;
    return output_stream;
}

struct Vector {
    int32_t x, y;

    Vector(Coords begin, Coords end) {
        this->x = end.x - begin.x;
        this->y = end.y - begin.y;
    }

    Vector(Coords a) {
        this->x = a.x;
        this->y = a.y;
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

std::ostream& operator<<(std::ostream& output_stream, Vector vector) {
    output_stream << vector.x << ' ' << vector.y;
    return output_stream;
}

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
    return std::abs(first.x * second.x + first.y * second.y);
}

int32_t operator^(Vector first, Vector second) {
    return std::abs(first.x * second.y - first.y * second.x);
}

double AngleInRadins(Vector first, Vector second) {
    return std::atan2(first ^ second, first * second);
}

double AngleInDegrees(Vector first, Vector second) {
    return std::abs(std::atan2(first ^ second, first * second)) / PI * 180;
}

int main() {
    Coords first, second, third;
    std::cin >> first >> second >> third;

    Vector v1 = second - first;
    Vector v2 = third - first;
    double angle = std::abs(AngleInRadins(v1, v2));

    std::cout << std::fixed << angle << '\n';

    return 0;
}