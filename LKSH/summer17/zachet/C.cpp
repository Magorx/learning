#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

const int32_t RIGHT = 1;
const int32_t LEFT = -1;
const double PI = 3.1415926535;
const double eps = 1e-3;

struct Vector {
    double x, y;

    double length() {
        return std::sqrt(this->x * this->x + this->y * this->y);
    }

    void rotate90(int32_t direction) {
        double new_x = 0, new_y = 0;
        new_x = -this->y * direction;
        new_y = this->x * direction;
        this->x = new_x;
        this->y = new_y;
    }

    Vector rotated90(int32_t direction) {
        Vector new_vector = *this;
        new_vector.rotate90(direction);
        return new_vector;
    }

    void set_length(double new_length) {
        double new_x = this->x * new_length / this->length(), new_y = this->y * new_length / this->length();
        this->x = new_x;
        this->y = new_y;
    }
};

struct Point : Vector{
    double x, y;
};

struct Line {
    Point point;
    Vector direction;
};

struct Circle {
    Point center;
    double radius;
};

// Input and Output
std::istream& operator>>(std::istream& input_stream, Vector& vector) {
    input_stream >> vector.x >> vector.y;
    return input_stream;
}

std::ostream& operator<<(std::ostream& output_stream, const Vector& vector) {
    output_stream << vector.x << ' ' << vector.y;
    return output_stream;
}

std::istream& operator>>(std::istream& input_stream, Point& point) {
    input_stream >> point.x >> point.y;
    return input_stream;
}

std::ostream& operator<<(std::ostream& output_stream, const Point& point) {
    output_stream << point.x << ' ' << point.y;
    return output_stream;
}
// ================

// Operators
Vector operator+(const Vector& first, const Vector& second) {
    return Vector{first.x + second.x, first.y + second.y};
}

Vector operator-(const Vector& first, const Vector& second) {
    return Vector{first.x - second.x, first.y - second.y};
}

Vector operator-(const Point& first, const Point& second) {
    return Vector{first.x - second.x, first.y - second.y};
}

Point operator+(const Point& point, const Vector& vector) {
    double  new_x = point.x + vector.x, new_y = point.y + vector.y;
    Point new_point;
    new_point.x = new_x;
    new_point.y = new_y;
    return new_point;
}

Vector operator*(const double coef, const Vector& vector) {
    return Vector{vector.x * coef, vector.y * coef};
}

Vector operator*(const Vector& vector, const double coef) {
    return Vector{vector.x * coef, vector.y * coef};
}

Vector operator/(const Vector& vector, const double coef) {
    return Vector{vector.x / coef, vector.y / coef};
}

bool operator<(Point& first,  Point& second) {
    if (first.x < second.x) {
        return false;
    } else if (first.x > second.x) {
        return true;
    } else {
        if (first.y < second.y) {
            return true;
        } else {
            return false;
        }
    }
}
// =========

// Dot and vector Product
double operator*(const Vector& first, const Vector& second) {
    return first.x * second.x + first.y * second.y;
}

double operator%(const Vector& first, const Vector& second) {
    return first.x * second.y - second.x * first.y;
}
// ======================

// Functions
double VectorVectorAngle(Vector first, Vector second) {
    return std::atan2(first % second, first * second) / PI * 180;
}

double PointPointDistance(Point first, Point second) {
    return (first - second).length();
}

double PointLineDistance(Point point, Line line) {
    return std::abs(((point - line.point) % line.direction) / line.direction.length());
}
// =========

int main() {
    Point a1, b1, c1, a2, b2, c2;
    std::cin >> a1 >> b1 >> c1 >> a2 >> b2 >> c2;

    Vector vec11 = a1 - b1, vec12 = a1 - c1, vec13 = c1 - b1;
    Vector vec21 = a2 - b2, vec22 = a2 - c2, vec23 = c2 - b2;

    std::vector<double> lens1 {vec11.length(), vec12.length(), vec13.length()};
    std::vector<double> lens2 {vec21.length(), vec22.length(), vec23.length()};

    std::sort(lens1.begin(), lens1.end());
    std::sort(lens2.begin(), lens2.end());

    std::vector<double> arr {lens1[0] / lens2[0], lens1[1] / lens2[1], lens1[2] / lens2[2]};

    double coef = std::abs(arr[0]);
    for (double c : arr) {
        //std::cout << c << '\n';
        if (std::abs(coef - std::abs(c)) > eps) {
            std::cout << "NO\n";
            return 0;
        }
    }
    std::cout << "YES\n";
    return 0;
}