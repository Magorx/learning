#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
const double eps = 1e-7;

const int PARALLEL = 0;
const int PERESECHEL = 1;

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

  void set_len(double d) {
    normalize();
    x = x * d;
    y = y * d;
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

  void rotate(double cos_a, double sin_a) {
    double new_x = x * cos_a - y * sin_a;
    double new_y = x * sin_a + y * cos_a;
    x = new_x;
    y = new_y;
  }
};

bool operator<(Vector first, Vector second) {
  if (first.x - second.x < eps) {
    return true;
  } else if (first.x - second.x > eps) {
    return false;
  } else {
    if (first.y - second.y < eps) {
      return true;
    } else {
      return false;
    }
  }
}

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

vector<Vector> circle_circle_cross(Vector o1, double r1, Vector o2, double r2) {
  Vector v = o2 - o1;
  double d = v.len();
  if (d < eps) {
    cout << "PE PLZ\n";
  }
  double cos_a = (r1 * r1 + d * d - r2 * r2) / (2 * r1 * d);
  double sin_a = sqrt(1 - cos_a * cos_a);
  
  v.set_len(r1);
  v.rotate(cos_a, sin_a);
  Vector first_point = o1 + v;

  v.rotate(cos_a, -sin_a);
  v.rotate(cos_a, -sin_a);
  Vector second_point = o1 + v;
  if (d - r1 - r2 < eps) {
    return {first_point, second_point};
  }

  return {};
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

bool is_point_in_polygon(vector<Vector>& polygon, Vector point) {
  double angle = 0;
  for (int i = 0; i < polygon.size() - 1; ++i) {
    Vector v1 = point - polygon[i];
    Vector v2 = point - polygon[i + 1];
    if (abs(v1 % v2) < eps && v1 * v2 <= eps) {
      return true;
    }
    angle += atan2(v1 % v2, v1 * v2);
    // cout << angle << ' ' << atan2(v1 % v2, v1 * v2) << '\n';
  }
  if (abs(angle) - 2 * M_PI < eps && abs(angle) > eps) {
    return true;
  } else {
    return false;
  }
}

int main() {
  int n;
  Vector point;
  cin >> n >> point;
  vector<Vector> polygon(n);
  for (int i = 0; i < n; ++i) {
    cin >> polygon[i];
  }
  polygon.push_back(polygon[0]);
  if (is_point_in_polygon(polygon, point)) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
  }
}
