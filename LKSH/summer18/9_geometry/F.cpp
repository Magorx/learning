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
  Vector monastery, temple;
  cin >> monastery >> temple;
  double k, b;
  cin >> k >> b;
  monastery.y -= b;
  temple.y -= b;
  

  Vector direction(1, k);
  double line_a = k;
  double line_b = -1;
  double line_c = 0;
  cout.precision(20);
  if ((direction % monastery) * (direction % temple) < 0) {
    cout << "No solution.\n";
    return 0;
  } else {
    double tmp_len = Vector(line_a, line_b).len();
    double d = (line_a * temple.x + line_b * temple.y + line_c) / tmp_len;
    Vector mirrored(temple.x - 2 * d * line_a / tmp_len, temple.y - 2 * d * line_b / tmp_len);
    cout << (mirrored - monastery).len() << '\n';
  }
}
