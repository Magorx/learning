#include <iostream>
#include <vector>
#include <cmath>

const int32_t RIGHT = -1;
const int32_t LEFT = 1;
const double PI = 3.1415926535;

struct Coords {
    double x, y;

    Coords(double x, double y) {
        this->x = x;
        this->y = y;
    }

    Coords() {
        this->x = 0;
        this->y = 0;
    }
};

struct Vector {
    double x, y;

    Vector(Coords begin, Coords end) {
        this->x = end.x - begin.x;
        this->y = end.y - begin.y;
    }

    Vector(Coords a) {
        this->x = a.x;
        this->y = a.y;
    }

    Vector(double x, double y) {
        this->x = x;
        this->y = y;
    }

    void rotate90(int32_t direction) {
        double new_x = 0, new_y = 0;
        new_x = -this->y * direction;
        new_y = this->x * direction;
        this->x = new_x;
        this->y = new_y;
    }

    Vector rotated90(int32_t direction) {
        Vector result = *this;
        result.rotate90(LEFT);
        return result;
    }

    void rotate180() {
        for (int32_t i = 0; i < 2; ++i)
            this->rotate90(LEFT);
    }

    double len() {
        return std::sqrt(x * x + y * y);
    }

    void set_len(double len) {
        double new_x = this->x * len / this->len(), new_y = this->y * len / this->len();
        this->x = new_x;
        this->y = new_y;
    }
};

Vector operator-(Coords first, Coords second) {
    return {first.x - second.x, first.y - second.y};
}

Coords operator+(Coords point, Vector vector) {
    return Coords {point.x + vector.x, point.y + vector.y};
}

std::istream& operator>>(std::istream& input_stream, Coords& coords) {
    input_stream >> coords.x >> coords.y;
    return input_stream;
}

std::ostream& operator<<(std::ostream& output_stream, Coords coords) {
    output_stream << coords.x << ' ' << coords.y;
    return output_stream;
}

std::ostream& operator<<(std::ostream& output_stream, Vector vector) {
    output_stream << vector.x << ' ' << vector.y;
    return output_stream;
}

Vector operator*(double number, Vector vector) {
    return {vector.x * number, vector.y * number};
}

struct Line {
    Coords point;
    Vector direction;
};

double operator*(Vector first, Vector second) {
    return first.x * second.x + first.y * second.y;
}

double operator%(Vector first, Vector second) {
    return first.x * second.y - first.y * second.x;
}

double AngleInRadins(Vector first, Vector second) {
    return std::atan2(first % second, first * second);
}

double AngleInDegrees(Vector first, Vector second) {
    return std::atan2(first % second, first * second) / PI * 180;
}

bool OnOneSide(Coords first, Coords second, Line line) {
    return (((first - line.point) % line.direction > 0) == 
            ((second - line.point) % line.direction > 0));
}

Line KBToLine(double k, double b) {
    Coords point{0.0, b};
    Vector direction{1.0, k + b};
    return Line{point, direction};
}

double PointLineDistance(Coords point, Line line) {
    return std::abs(((point - line.point) % line.direction) / line.direction.len());
}

int main() {
    Coords from, to;
    double k, b;
    std::cin >> from >> to >> k >> b;

    Line river = KBToLine(k, b);
    
    if (!OnOneSide(from, to, river)) {
        std::cout << "No solution.\n";
        return 0;
    }

    double distance = PointLineDistance(to, river);
    river.direction.set_len(distance);
    Coords new_to;
    if ((to - river.point) % river.direction < 0) {
        new_to =  to + 2 * river.direction.rotated90(LEFT);
    } else {
        new_to =  to + (-2 * river.direction.rotated90(LEFT));
    }
    std::cout.precision(10);
    std::cout << std::fixed << (from - new_to).len() << '\n';

    return 0;
}

// 0 150
// 0 -150
// 2 500
// 521.536