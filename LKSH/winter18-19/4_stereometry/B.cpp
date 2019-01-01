#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-7;

struct Vector {
  double x, y, z;

  Vector() {
    x = 0;
    y = 0;
    z = 0;
  }

  Vector(double x_, double y_, double z_) {
    x = x_;
    y = y_;
    z = z_;
  }

  double len() const {
    return sqrt(x * x + y * y + z * z);
  }

  void rotate(Vector axis, double angle) {
    double cs = cos(angle);
    double sn = sin(angle);
    double new_x = x * (cs + (1 - cs) * axis.x * axis.x + (1 - cs) * axis.x * axis.y - sn * axis.z + (1 - cs) * axis.x * axis.z + sn * axis.y);
    double new_y = y * ((1 - cs) * axis.y * axis.x + sn * axis.z + cs + 1 - cs * axis.y * axis.y + (1 - cs) * axis.y * axis.z - sn * axis.x);
    double new_z = z * ((1 - cs) * axis.z * axis.x - sn * axis.y + (1 - cs) * axis.z * axis.y + sn * axis.x + cs + (1 - cs) * axis.z * axis.z);
    x = new_x;
    y = new_y;
    z = new_z;
  }

  void normalize() {
    double l = len();
    x = x / l;
    y = y / l;
    z = z / l;
  }

  void set_len(double l) {
    normalize();
    x *= l;
    y *= l;
    z *= l;
  }
};

const Vector e1(1, 0, 0);
const Vector e2(0, 1, 0);
const Vector e3(0, 0, 1);

Vector operator+(const Vector& first, const Vector& second) {
  return Vector(first.x + second.x, first.y + second.y, first.z + second.z);
}

Vector operator-(const Vector& first, const Vector& second) {
  return Vector(first.x - second.x, first.y - second.y, first.z - second.z);
}

Vector operator*(const Vector& first, const double k) {
  return Vector(first.x * k, first.y * k, first.z * k);
}

double operator*(const Vector& first, const Vector& second) {
  return first.x * second.x + first.y * second.y + first.z * second.z;
}

Vector operator%(const Vector& first, const Vector& second) {
  return Vector(first.y * second.z -  first.z * second.y, first.z * second.x - first.x * second.z, first.x * second.y - first.y * second.x);
}

istream& operator>>(istream& input, Vector& first) {
  input >> first.x >> first.y >> first.z;
  return input;
}

ostream& operator<<(ostream& output, const Vector& first) {
  output << first.x << ' ' << first.y << ' ' << first.z;
  return output;
}

double angle(const Vector& first, const Vector& second) {
  return atan2((first % second).len(), first * second);
}

Vector any_orthogonal(const Vector& first) {
  if (first.len() == 0) {
    return Vector(0, 0, 0);
  }
  Vector res = first % e1;
  if (res.len()) {
    return res;
  }
  res = first % e2;
  if (res.len()) {
    return res;
  }
  res = first % e3;
  if (res.len()) {
    return res;
  }
  return Vector(0, 0, 0);
}

double volume(const Vector& first, const Vector& second, const Vector& third) {
  return (first % second) * third;
}

double point_line_dist(const Vector& point, const Vector& a, const Vector& b) {
  Vector first = point - a;
  Vector second = b - a;
  return (first % second).len() / second.len();
}

double point_seg_dist(const Vector& point, const Vector& a, const Vector& b) {
  Vector point_a_vec = point - a;
  Vector second = b - a;
  if (point_a_vec * second < 0) {
    return point_a_vec.len();
  }
  point_a_vec = point - b;
  second = a - b;
  if (point_a_vec * second < 0) {
    return point_a_vec.len();
  }

  return point_line_dist(point, a, b);
}

double point_plane_distance(Vector point, double a, double b, double c, double d) {
  return (a * point.x + b * point.y + c * point.z + d) / sqrt(a * a + b * b + c * c);
}

bool point_on_plane(Vector point, double a, double b, double c, double d) {
  return a * point.x + b * point.y + c * point.z + d == 0;
}

Vector orthogon_base(Vector point, double a, double b, double c, double d) {
  double h = point_plane_distance(point, a, b, c, d);
  Vector n(a, b, c);
  n.set_len(h);
  if (point_on_plane(point + n, a, b, c, d)) {
    return point + n;
  } else {
    return point + (n * (-1));
  }
}

vector<double> plane_by_points(const Vector& a, const Vector& b, const Vector& c) {
  Vector first = b - a;
  Vector second = c - a;
  Vector n = first % second;
  double A = n.x;
  double B = n.y;
  double C = n.z;
  double D = -1 * (A * a.x + B * a.y + C * a.z);
  return {A, B, C, D};
}

bool three_points_on_line(const Vector& a, const Vector& b, const Vector& c) {
  Vector first = b - a;
  Vector second = c - a;
  return (first % second).len() < eps;
}

int main() {
  Vector a, b, c;
  cin >> a >> b >> c;
  cout.precision(10);
  Vector middle = (a + b + c) * ((double)1 / (double)3);
  auto w = plane_by_points(a, b, c);
  Vector n(w[0], w[1], w[2]);
  n.set_len((a - b).len() * sqrt((double) 2 / (double) 3));
  cout << middle + n << '\n';
  
  return 0;
}