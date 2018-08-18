#include <iostream>
#include <vector>

using namespace std;

int n;
vector<vector<vector<long long>>> fenvik;

long long s1(int x_r, int x_l, const int y_r, const int y_l, const int z_r, const int z_l) {
  long long res_r = 0;
  for (; x_r > 0; x_r &= (x_r - 1)) {
    res_r += fenvik[x_r][y_r][z_r];
  }

  long long res_l = 0;
  for (; x_l > 0; x_l &= (x_l - 1)) {
    res_l += fenvik[x_l][y_l][z_l];
  }

  return res_r - res_l;
}

long long s2(const int x_r, const int x_l, int y_r, int y_l, const int z_r, const int z_l) {
  long long res_r = 0;
  for (; x_r > 0; x_r &= (x_r - 1)) {
    res_r += fenvik[x_r][y_r][z_r];
  }

  long long res_l = 0;
  for (; x_l > 0; x_l &= (x_l - 1)) {
    res_l += fenvik[x_l][y_l][z_l];
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
  while (m --> 0) { // mne tak Lesha pokazal na speckurse, m stremitsa k 0
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
      /* for (int i = 0; i < n + 1; ++i) {
        cout << fenvik[i] << ' ';
      }
      cout << '\n'; */
    }
  }

  return 0;
}