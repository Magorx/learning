#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

vector<long long> dsu;
vector<long long> dsu_size;
long long max_n = 1e6;

long long get(long long v) {
  if (dsu[v] == v) {
    return v;
  } else {
    return dsu[v] = get(dsu[v]);
  }
}

void add(long long first, long long second) {
  first = get(first);
  second = get(second);
  if (dsu_size[first] > dsu_size[second]) {
    dsu[second] = first;
    dsu_size[first] += dsu_size[second];
  } else {
    dsu[first] = second;
    dsu_size[second] += dsu_size[first];
  }
}

int main() {
  long long n;
  cin >> n;
  dsu.resize(n * 4, -1);
  dsu_size.resize(n * 4, -1);
  for (long long i = 0; i < (long long)dsu.size(); ++i) {
    dsu[i] = i;
    dsu_size[i] = 1;
  }

  map<pair<long long, long long>, long long> z;
  long long max_id = 0;

  for (long long i = 0; i < n; ++i) {
    long long a, b, c, d;
    cin >> a >> b >> c >> d;
    auto first = z.find({a, b});
    auto second = z.find({c, d});
    if (first == z.end()) {
      z[{a, b}] = max_id;
      ++max_id;
    }
    if (second == z.end()) {
      z[{c, d}] = max_id;
      ++max_id;
    }

    if (get(z[{a, b}]) == get(z[{c, d}])) {
      cout << i + 1 << '\n';
      return 0;
    }
      add(z[{a, b}], z[{c, d}]);
  }
  cout << 0 << '\n';  

  return 0;
}