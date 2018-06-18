#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int mex(std::vector<int>& arr) {
  std::vector<char> was(arr.size() + 2, 0);
  for (int i = 0; i < arr.size(); ++i) {
    was[arr[i]] = 1;
  }
  for (int i = 0; i < was.size(); ++i) {
    if (!was[i]) {
      return i;
    }
  }
  return -1;
}

int main() {
  // freopen("demiurgs.in", "r", stdin);
  // freopen("demiurgs.out", "w", stdout);
  long long n = 0;
  std::cin >> n;
  long long a = 0;
  for (long long i = n; i < n + 1000000; ++i) {
    a = a ^ i;
    if (a == 0) {
      std::cout << i << '\n';
      return 0;
    }
  }
  a = 0;
  for (long long i = n; i > std::max(n - 1000000, 0ll); --i) {
    a = a ^ i;
    if (a == 0) {
      std::cout << i << '\n';
      return 0;
    }
  }
  std::cout << 0 << '\n';

  return 0;
}