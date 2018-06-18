#include <iostream>
#include <vector>

long long gcd(long long a, long long b, long long& x, long long& y) {
  if (a == 0) {
    x = 0;
    y = 1;
    return b;
  }
  long long xx;
  long long yy;
  long long ans = gcd(b % a, a, xx, yy);
  // std::cout << a << ' ' << b << '\n';
  x = yy - b / a * xx;
  y = xx;
  return ans;
}

int main() {
  long long a, b, c;
  std::cin >> a >> b >> c;
  long long x, y;
  long long g = gcd(a, b, x, y);
  if (c % g) {
    std::cout << "Impossible\n";
    return 0;
  }
  x = x * (c / g);
  y = y * (c / g);

  long long k = x * g / b;
  x -= k * b / g;
  y += k * a / g;
  // long long new_x = x;
  // long long new_y = y;


  // if (x > 0) {
  //   long long i = 0;
  //   for (i = 0; i < 1000000 && new_x >= 0; ++i) {
  //     new_x = x - b / g * i;
  //     new_y = y + a / g * i;
  //   }
  //   if (i) {
  //     x = new_x + b / g;
  //     y = new_y - a / g;
  //   }
  // } else if (x < 0) {
  //   long long i = 0;
  //   for (i = 0; i < 1000000 && new_x < 0; ++i) {
  //     new_x = x + b / g * i;
  //     new_y = y - a / g * i;
  //     // std::cout << i << ' ' << new_x << ' ' << new_y << ' ' << '\n';
  //   }
  //   x = new_x;
  //   y = new_y;
  // }

  if (x < 0) {
    x += b / g;
    y -= a / g;
  }

  std::cout << x << ' ' << y << '\n';
  return 0;
}