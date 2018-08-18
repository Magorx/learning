#include <iostream>
#include <vector>

struct Vector {
  double x;
  double y;

  Vector() {
    x = 0;
    y = 0;
  }

  Vector(double x_, double y_) {
    x = x_;
    y = y_;
  }
};

Vector operator-(Vector first, Vector second) {
  return {second.x - first.x, second.y - first.y};
}

Vector operator+(Vector first, Vector second) {
  return {first.x + second.x, first.y + second.y};
}

double operator*(Vector first, Vector second) {
  return first.x * second.x + first.y * second.y;
}

double operator%(Vector first, Vector second) {
  first.x * second.y - first.y * second.x;
}

std::istream& operator>>(std::istream& input_stream, Vector& vector) {
  input_stream >> vector.x >> vector.y;
  return input_stream;
}

std::ostream& operator<<(std::ostream& output, Vector& vector) {
  output << vector.x << vector.y;
  return output;
}
