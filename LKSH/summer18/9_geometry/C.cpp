#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

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

  double angle() {
    return atan2(y, x);
  }

  double len() {
    return hypot(x, y);
  }

  void normalize() {
    double d = len();
    x = x / d;
    y = y / d;
  }

  Vector normalized() {
    double d = len();
    double new_x = x / d;
    double new_y = y / d;
    return {new_x, new_y};
  }

  void rotate_clockwise() {
    double new_x = y;
    double new_y = -x;
    x = new_x;
    y = new_y;
  }

  void rotate_conterclockwise() {
    double new_x = -y;
    double new_y = x;
    x = new_x;
    y = new_y;
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
  return first.x * second.y - first.y * second.x;
}

std::istream& operator>>(std::istream& input_stream, Vector& vector) {
  input_stream >> vector.x >> vector.y;
  return input_stream;
}

std::ostream& operator<<(std::ostream& output, const Vector& vector) {
  output << vector.x << ' ' << vector.y;
  return output;
}

Vector operator*(double coef, Vector v) {
  return {coef * v.x, coef * v.y};
}

int main() {
  Vector first, second;
  Vector a, b;
  cin >> a >> b;
  first = a - b;
  double d;
  cin >> d;

  cout.precision(10);
  cout << first << '\n';
  second = first.normalized();
  cout << second << '\n';
  cout << d * second << '\n';
  first.rotate_clockwise();
  cout << first << '\n';
  first.rotate_conterclockwise();
  first.rotate_conterclockwise();
  cout << first << '\n';
}
