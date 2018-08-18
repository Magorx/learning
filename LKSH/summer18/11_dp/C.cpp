#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<long long> arr;

vector<long long> find_nvp(vector<long long> arr) {
  vector<long long> ans;
  for (int i = 0; i < arr.size(); ++i) {
    long long value = arr[i];
    auto index = lower_bound(ans.begin(), ans.end(), value);
    if (index == ans.end()) {
      ans.push_back(value);
    } else {
      *index = value;
    }
  }
  return ans;
}

int main() {
  long long n, m, k, b, a1;
  cin >> n >> a1 >> k >> b >> m;
  arr.resize(n);
  arr[0] = a1;
  for (int i = 1; i < n; ++i) {
    arr[i] = (arr[i - 1] * k + b) % m;
  }

  cout << find_nvp(arr).size() << '\n';

  return 0;
}