#include <iostream>
#include <vector>
#include <string>

const long long MM = (1ll << 32);
const long long M = 100007;

long long f(int n) {
  if (n <= 2) {
    return 1;
  } else if (n % 2) {
    return (f(6 * n / 7) % MM + f(2 * n / 3) % MM) % MM;
  } else {
    return (f(n - 1) % MM + f(n - 3) % MM) % MM;
  }
}

class Hashtable {
public:
  std::vector<std::vector<std::pair<long long, long long>>> data;
  Hashtable():  data(M, std::vector<std::pair<long long, long long>>(1, {-1, -1}))
  {
    data[0][0].second = 1;
    data[1][0].second = 1;
    data[2][0].second = 1;
    data[0][0].first = 0;
    data[1][0].first = 1;
    data[2][0].first = 2;
  }

  long long find(long long n) {
    long n_moduled = n % M;
    for (long long nn = 0; nn < data[n_moduled].size(); ++nn) {
      if (data[n_moduled][nn].first == n || data[n_moduled][nn].first == -1) {
        if (data[n_moduled][nn].second == -1 || data[n_moduled][nn].second == 0) {
          if (n % 2) {
            data[n_moduled][nn].second = (find(6 * n / 7) % MM + find(2 * n / 3) % MM) % MM;
          } else {
            data[n_moduled][nn].second = (find(n - 1) % MM + find(n - 3) % MM) % MM;
          }
          data[n_moduled][nn].first = n;
        }
        return data[n_moduled][nn].second;
      }
    }
    data[n_moduled].push_back(std::pair<long long, long long>(-1, -1));
    long long nn = data[n_moduled].size() - 1;
    if (data[n_moduled][nn].second == -1 || data[n_moduled][nn].second == 0) {
      if (n % 2) {
        data[n_moduled][nn].second = (find(6 * n / 7) % MM + find(2 * n / 3) % MM) % MM;
      } else {
        data[n_moduled][nn].second = (find(n - 1) % MM + find(n - 3) % MM) % MM;
      }
      data[n_moduled][nn].first = n;
    }

    return data[n_moduled][nn].second;
  }
};

int main() {
  freopen("function.in", "r", stdin);
  freopen("function.out", "w", stdout);
  long long n = 0;
  std::cin >> n;
  Hashtable table;
  std::cout << table.find(n) << '\n';
  // for (int i = 0; i < n; ++i) {
  //   std::cout << table.find(i) << '\n';
  //   if (f(i) != table.find(i)) {
  //     std::cout << "ggwp " << i << f(i) << " - " << table.find(i) << '\n';
  //   }
  // }

  return 0;
}