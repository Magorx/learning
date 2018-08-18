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

int main() {
  Vector first, second;
  Vector a, b;
  cin >> a >> b;
  first = a - b;
  cin >> a >> b;
  second = a - b;

  cout.precision(10);
  cout << first.len() << ' ' << second.len() << '\n';
  cout << first + second << '\n';
  cout << first * second << ' ' << first % second << '\n';
  cout << abs(first % second / 2) << '\n';
}
