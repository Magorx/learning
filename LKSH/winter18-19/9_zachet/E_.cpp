#include <bits/stdc++.h>

using namespace std;

vector<long long> gcd_extended(long long a, long long b) {
  if (b == 0) {
    return {a, 1, 0};
  } else {
    auto ret = gcd_extended(b, a % b);
    long long d = ret[0];
    long long x = ret[1];
    long long y = ret[2];
    return {d, y, x - (a / b) * y};
  }
}

long long module_opposite(long long n, long long m) {
  auto ret = gcd_extended(n, m);
  if (ret[0] != 1) {
    return -1;
  } else {
    return ((ret[1] % m) + m) % m;
  }
}

template <typename T>
T gcd(T a, T b) {
  if (b == 0) {
    return a;
  } else {
    return gcd(b, a % b);
  }
}

long long lcm(long long a, long long b) {
  return a * b / gcd(a, b);
}

pair<bool, pair<long long, long long>> solve_diophant(long long a, long long b, long long c) {
  auto ret = gcd_extended(a, b);
  long long d = ret[0];
  long long x = ret[1];
  long long y = ret[2];
  long long k = a / b;

  if (c % d) {
    return {false, {0, 0}};
  } else {
    a = a / d;
    b = b / d;
    c = c / d;
    x = x * c + k * b;
    y = y * c - k * a;
    long long coef = -1 * x / b;
    x = x + coef * b;
    y = y - coef * a;
    if (x < 0) {
      x += b;
      y -= a;
    }
    return {true, {x, y}};
  }
}

long long suplex(long long a, long long b, long long n, long long m) {
  auto ret = solve_diophant(m, n, a - b);
  if (!ret.first) {
    return -1;
  } else {
    return ret.second.first * m + b;
  }
}

long long top_solve(long long a, long long b, long long n, long long m) {
  for (int i = 0; i < m * n; ++i) {
    if (i % n == a && i % m == b) {
      return i;
    }
  }
  return -1;
}

int main() {
  // long long q;
  // cin >> q;
  for (int a = 1; a < 40; ++a) {
    for (int b = 1; b < 40; ++b) {
      for (int n = a + 1; n < 40; ++n) {
        for (int m = b + 1; m < 40; ++m) {
          if (suplex(a, b, n, m) != top_solve(a, b, n, m))
            cout << "a = " << a << " b = " << b << " n = " << n << " m = " << m << " my_ans = " << suplex(a, b, n, m) << " true_ans = " << top_solve(a, b, n, m) << '\n';
        }
      }
    }
  }

  return 0;
}
