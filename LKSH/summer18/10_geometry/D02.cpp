#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
const double eps = 1e-7;

struct Vector {
  double x;
  double y;
  int id;
  static int new_id;

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

bool is_dog_in_cat(vector<Vector>& cat, Vector dog) {
  double angle = 0;
  for (int i = 0; i < cat.size() - 1; ++i) {
    Vector v1 = dog - cat[i];
    Vector v2 = dog - cat[i + 1];
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

vector<Vector> convex_hull(vector<Vector>& cat) {
  sort(cat.begin(), cat.end());
  vector<Vector> hull;
  Vector begin = cat[0];
  hull.push_back(begin);
  hull.push_back(begin);
  for (int i = 0; i < cat.size(); ++i) {
    cat[i].x -= begin.x;
    cat[i].y -= begin.y;
  }
  sort(++cat.begin(), cat.end(), polar_angle_comparator);

  for (int i = 1; i < cat.size(); ++i) {
    Vector last_point = *(--hull.end());
    Vector last_last_point = *(----hull.end());
    Vector cur_point = cat[i];

    Vector last_v = last_point - last_last_point;
    Vector cur_v = cur_point - last_point;
    if (last_v % cur_v < 0) {
      hull.pop_back();
    }
    hull.push_back(cur_point);
  }

  return hull;
}

long double find_square(vector<Vector>& cat) {
  cat.push_back(cat[0]);
  Vector init_point(0, 0);
  long double square = 0;
  for (int i = 0; i < cat.size() - 1; ++i) {
    square += (cat[i] - init_point) % (cat[i + 1] - init_point) / 2;
  }

  cat.pop_back();
  return square;
}

long double find_perimetr(vector<Vector>& cat) {
  cat.push_back(cat[0]);
  Vector init_point(0, 0);
  long double perimetr = 0;
  for (int i = 0; i < cat.size() - 1; ++i) {
    perimetr += (cat[i] - cat[i + 1]).len();
  }

  cat.pop_back();
  return perimetr;
}

int Vector::new_id = 0;
long double P = 0;
long double S = 0;

int main() {
  cout.precision(20);
  int n;
  Vector dog;
  cin >> n;
  vector<Vector> cat(n);
  for (int i = 0; i < n; ++i) {
    cin >> cat[i];
    cat[i].id = i + 1;
  }

  auto hull = convex_hull(cat);
  cout << hull.size() - 1 << '\n';
  for (int i = 1; i < hull.size(); ++i) {
    cout << hull[i].id << ' ';
  }
  cout << '\n';

  cout << find_perimetr(hull) << '\n';
  cout << find_square(hull) << '\n';

  return 0;
}
