#include <iostream>
#include <vector>
#include <string>

const long long MM = (1ll << 32) - 1;

long long f(int n) {
  if (n <= 2) {
    return 1;
  } else if (n % 2) {
    return (f(6 * n / 7) % MM + f(2 * n / 3) % MM) % MM;
  } else {
    return (f(n - 1) % MM + f(n - 3) % MM) % MM;
  }
}

int main() {
  //freopen("in.in", "r", stdin);
  long long n = 0;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::cout << f(i) << '\n';
  }

  return 0;
}