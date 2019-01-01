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

long long module_oppsite(long long n, long long m) {
  auto ret = gcd_extended(n, m);
  if (ret[0] != 1) {
    return -1;
  } else {
    return ((ret[1] % m) + m) % m;
  }
}

int main() {
  freopen("inv.in", "r", stdin);
  freopen("inv.out", "w", stdout);
  long long n, m;
  cin >> n >> m;
  long long ret = module_oppsite(n, m);
  if (ret == -1) {
    cout << -1 << '\n';
  } else {
    cout << ret << '\n';
  }

  return 0;
}