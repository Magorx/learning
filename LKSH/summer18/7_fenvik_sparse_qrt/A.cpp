#include <iostream>
#include <vector>

using namespace std;

int n;
vector<long long> fenvik;
vector<long long> arr;

long long sum(int l, int r) {
  long long res_r = 0;
  for (; r > 0; r &= (r - 1)) {
    res_r += fenvik[r];
  }

  long long res_l = 0;
  for (; l > 0; l &= (l - 1)) {
    res_l += fenvik[l];
  }

  return res_r - res_l;
}

void add(int i, long long delta) {
  for (; i <= n; i = (i | (i - 1)) + 1) {
    fenvik[i] += delta;
  }
}

int main() {
  cin >> n;
  fenvik.resize(n + 1, 0);
  arr.resize(n + 1, 0);
  int m;
  cin >> m;
  while (m-- > 0) {
    long long l, r; 
    char type;
    cin >> type >> l >> r;
    if (type == 'Q') {
      --l;
      cout << sum(l, r) << '\n';
    } else {
      long long delta = r - arr[l];
      arr[l] = r;
      add(l, delta);
    }
  }

  return 0;
}