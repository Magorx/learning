#include <bits/stdc++.h>

using namespace std;

template <typename T>
T binpow(const T& obj, long long pow, const T& module) {
  if (pow == 0) {
    return (T)1;
  } else if (pow == 1) {
    return obj % module;
  } else {
    if (pow % 2) {
      return (binpow(obj, pow - 1, module) * obj) % module;
    } else {
      T ret = binpow(obj, pow / 2, module);
      return (ret * ret) % module;
    }
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
  n = n % m;
  if (gcd(n, m) != 1) {
    return -1;
  } else {
    return binpow(n, m - 2, m);
  }
}

int main() {
  // freopen("inv.in", "r", stdin);
  // freopen("inv.out", "w", stdout);
  long long n, m;
  cin >> n >> m;
  long long ret = module_oppsite(n, m);
  cout << ret << '\n';

  return 0;
}