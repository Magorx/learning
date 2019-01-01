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

template <typename T>
T gcd(T a, T b) {
  if (b == 0) {
    return a;
  } else {
    return gcd(b, a % b);
  }
}

long long module_oppsite(long long n, long long m) {
  auto ret = gcd_extended(n, m);
  if (ret[0] != 1) {
    return -1;
  } else {
    return ((ret[1] % m) + m) % m;
  }
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

int main() {
  long long a, b, c;
  cin >> a >> b >> c;
  auto ans = solve_diophant(a, b, c);
  if (!ans.first) {
    cout << "Impossible\n";
  } else {
    long long x = ans.second.first;
    long long y = ans.second.second;
    cout << x << ' ' << y << '\n';
  }

  return 0;
}