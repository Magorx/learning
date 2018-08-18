#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
const long long P = 1e6+3;
const long long mod = 1e9+9;
vector<long long> P_power(1e6+1, 1);

void precout_p_powers() {
  for (int i = 1; i < P_power.size(); ++i) {
    P_power[i] = (P_power[i - 1] * P) % mod;
  }
}

vector<long long> hashed(vector<int> s) {
  vector<long long> h(s.size(), s[0]);
  for (int i = 1; i < s.size(); ++i) {
    h[i] = (h[i - 1] * P % mod + s[i]) % mod;
  }
  return h;
}

long long segment_hash(const vector<long long>& h, int l, int r) {
  --l;
  if (l < 0) {
    return h[r];
  }
  return (h[r] - (h[l] * P_power[r - l]) % mod + mod) % mod;
}

int main() {
  precout_p_powers();
  int n;
  int m;
  cin >> n >> m;
  vector<int> arr(n, 0);
  for (int i = 0; i < n; ++i) {
    cin >> arr[i];
  }

  vector<long long> h = hashed(arr);
  reverse(arr.begin(), arr.end());
  vector<long long> h_reversed = hashed(arr);

  for (int i = 0; i < n; ++i) {

  }

  cout << '\n';
}