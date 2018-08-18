#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
const double eps = 1e-6;

const int PARALLEL = 0;
const int PERESECHEL = 1;
const int DISESECHEL = 2;

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
  return {first.x - second.x, first.y - second.y};
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

// VECTOR MANIPULATIONS

Vector operator*(double coef, Vector v) {
  return {coef * v.x, coef * v.y};
}

// CROSES

int line_line_cross(Vector first, Vector second) {
  if (first % second < eps) {
    return PARALLEL;
  } else {
    return PERESECHEL;
  }
}

Vector line_line_cross_point(Vector first, Vector second) {
  
}

int ray_line_cross(Vector ray_start_point, Vector ray, Vector line_point_one, Vector line_point_two) {
  if (ray % line == 0) {
    return PARALLEL;
  } else if ()
}

// DISTANCES

double point_point_distance(Vector first, Vector second) {
  return (second - first).len();
}

double point_line_distance(Vector point, Vector line) {
  return abs(((Vector(0, 0) - point) % (line - point))) / line.len();
}

double point_ray_distance(Vector point, Vector ray) {
  if (ray * point >= 0) {
    return point_line_distance(point, ray);
  } else {
    return min((point - ray).len(), point.len());
  }
}

double point_segment_distance(Vector point, Vector seg_one, Vector seg_two) {
  if ((seg_two - seg_one) * (point - seg_one) >= 0 && (seg_one - seg_two) * (point - seg_two) >= 0) {
    return point_line_distance(point, seg_one - seg_two);
  } else {
    return min(point_point_distance(seg_one, point), point_point_distance(seg_two, point));
  }
}



int main() {
  Vector a, b, c, d;
  cin >> a >> b >> c >> d;
  cout << c - b << '\n';
  cout << "point A line BC " << point_line_distance(a - b, c - b) << '\n';
  cout << "point A ray BC " << point_ray_distance(a - b, c - b) << '\n';
  cout << "point A seg BC" << point_segment_distance(a, b, c) << '\n';
}
