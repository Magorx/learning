#include <bits/stdc++.h>

using namespace std;

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

Vector operator*(const Vector& first, const int k) {
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