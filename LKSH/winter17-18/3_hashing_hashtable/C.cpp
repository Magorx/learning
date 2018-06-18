#include <iostream>
#include <vector>
#include <string>

//const int K = 137;
const int M = 1000007;

long long f(int n) {
  if (n <= 2) {
    return 1;
  } else if (n % 2) {
    return (f(6 * n / 7) % M + f(2 * n / 3) % M) % M;
  } else {
    return (f(n - 1) % M + f(n - 3) % M) % M;
  }
}

class Hashtable {
public:
  std::vector<int> data;
  Hashtable() {
    data = std::vector<int>(M, -1);
    data[0] = 1;
    data[1] = 1;
    data[2] = 1;
  }
  int find(long long n) {
    n %= M;
    if (data[n] == -1) {
      if (n % 2) {
        data[n] = find(6 * n / 7) + find (2 * n / 3);
      } else {
        data[n] = find(n - 1) + find (n - 3);
      }
    }
    return data[n];
  }
};

int main() {
  freopen("eqsubstr.in", "r", stdin);
  freopen("eqsubstr.out", "w", stdout);
  long long n = 0;
  std::cin >> n;
  Hashtable table;
  std::cout << table.find(n);

  return 0;
}
