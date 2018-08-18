#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
const long long P = 273;
const long long mod = 1e9+9;
vector<long long> P_power(1e6+1, 1);

void precout_p_powers() {
  for (int i = 1; i < P_power.size(); ++i) {
    P_power[i] = (P_power[i - 1] * P) % mod;
  }
}

vector<long long> hashed(string s) {
  vector<long long> h(s.length(), s[0]);
  for (int i = 1; i < s.length(); ++i) {
    h[i] = (h[i - 1] * P % mod + s[i]) % mod;
  }
  return h;
}

long long segment_hash(const vector<long long>& h, int l, int r) {
  --l;
  if (l < 0) {
    return h[r];
  }
  // cout << (h[r] - (h[l] * P_power[r - l]) % mod + mod) % mod << '\n';
  return (h[r] - (h[l] * P_power[r - l]) % mod + mod) % mod;
}

int main() {
  precout_p_powers();
  string s;
  int m;
  cin >> s >> m;

  vector<long long> h = hashed(s);
  /* for (auto x : h) {
    cout << x << ' ';
  }
  cout << '\n'; */
  for (int i = 0; i < m; ++i) {
    int l1, r1, l2, r2;
    cin >> l1 >> r1 >> l2 >> r2;
    --l1;
    --r1;
    --l2;
    --r2;
    if (segment_hash(h, l1, r1) == segment_hash(h, l2, r2)) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
  }
  cout << '\n';
}