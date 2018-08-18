#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
const double eps = 1e-11;

struct Vector {
  double x;
  double y;
  int id;

  Vector() {
    x = 0;
    y = 0;
  }

  Vector(double x_, double y_) {
    x = x_;
    y = y_;
  }

  Vector(double x_, double y_, int id_) {
    x = x_;
    y = y_;
    
    id = id_;
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
  if (first.y < second.y) {
    return true;
  } else if (first.y > second.y) {
    return false;
  } else {
    if (first.x < second.x) {
      return true;
    } else {
      return false;
    }
  }
}

bool polar_angle_comparator(Vector& first, Vector& second) {
  double angle_1 = atan2(first.y, first.x);
  double angle_2 = atan2(second.y, second.x);
  double len_1 = first.len();
  double len_2 = second.len();
  if (angle_2 - angle_1 > eps) {
    return true;
  } else if (angle_1 - angle_2 > eps) {
    return false;
  } else {
    if (len_2 - len_1 > eps) {
      return true;
    } else 
    return false;
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

vector<Vector> convex_hull(vector<Vector> polygon) {
  sort(polygon.begin(), polygon.end());
  vector<Vector> hull;
  Vector begin = polygon[0];
  hull.push_back(begin);
  hull.push_back(begin);
  for (int i = 0; i < polygon.size(); ++i) {
    polygon[i].x -= begin.x;
    polygon[i].y -= begin.y;
  }
  sort(++polygon.begin(), polygon.end(), polar_angle_comparator);

  for (int i = 1; i < polygon.size(); ++i) {
    while (true) {
      Vector last_point = *(--hull.end());
      Vector last_last_point = *(----hull.end());
      Vector cur_point = polygon[i];

      Vector last_v = last_point - last_last_point;
      Vector cur_v = cur_point - last_point;
      if (last_v % cur_v < 0) {
        hull.pop_back();
      } else if (abs(last_v % cur_v) < eps && hull.size() != 2) {
        hull.pop_back();
        hull.push_back(cur_point);
        break;
      } else {
        hull.push_back(cur_point);
        break;
      }
    }
  }

  hull.erase(hull.begin());
  for (int i = 1; i < hull.size(); ++i) {
    hull[i].x += begin.x;
    hull[i].y += begin.y;
  }

  return hull;
}

long double find_square(vector<Vector> polygon) {
  polygon.push_back(polygon[0]);
  Vector init_point(0, 0);
  long double square = 0;
  for (int i = 0; i < polygon.size() - 1; ++i) {
    square += (polygon[i] - init_point) % (polygon[i + 1] - init_point) / 2;
  }

  polygon.pop_back();
  return square;
}

long double find_perimetr(vector<Vector> polygon) {
  polygon.push_back(polygon[0]);
  long double perimetr = 0;
  for (int i = 0; i < polygon.size() - 1; ++i) {
    perimetr += (polygon[i] - polygon[i + 1]).len();
  }

  polygon.pop_back();
  return perimetr;
}

int main() {
  cout.precision(20);
  int n;
  Vector dog;
  cin >> n;
  vector<Vector> polygon(n);
  for (int i = 0; i < n; ++i) {
    cin >> polygon[i];
    polygon[i].id = i + 1;
  }

  auto hull = convex_hull(polygon);
  cout << hull.size() << '\n';
  for (int i = 0; i < hull.size(); ++i) {
    cout << hull[i].id << ' ';
  }
  cout << '\n';

  cout << find_perimetr(hull) << '\n';
  cout << find_square(hull) << '\n';

  return 0;
}
