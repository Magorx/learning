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

int main() {
  long long q;
  cin >> q;
  for (int i = 0; i < q; ++i) {
    long long a, b, n, m;
    cin >> a >> b >> n >> m;
    long long r = module_opposite(n, m);
    long long s = module_opposite(m, n);
    long long x = b * n * r + a * m * s;
    long long k = x / (m * n);
    x -= k * m * n;
    cout << x << '\n';
  }  

  return 0;
}