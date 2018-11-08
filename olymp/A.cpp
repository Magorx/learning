#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
  int n = 0;
  cin >> n;
  string s;
  vector<int> arr;
  cin >> s;
  for (int i = 0; i < n; ++i) {
    arr.push_back(s[i] - '0');
  }

  int pref_sum = 0;

  for (int i = 0; i < n; ++i) {
    pref_sum += arr[i];
    bool flag = true;
    int last_index = i + 1;
    int s = 0;
    //cout << pref_sum << '\n';
    while (flag && last_index < arr.size()) {
      s = 0;
      if (pref_sum == -1) {
        cout << last_index << '\n';
      }
      for (int j = last_index; j < n; ++j) {
        last_index = j + 1;
        if (pref_sum == -1) {
          cout << "j) " << j << ' ' << s << '\n';
        }
        s += arr[j];
        if (s > pref_sum) {
          flag = false;
          break;
        } else if (s == pref_sum) {
          break;
        }
      }
    }
    if (s < pref_sum || s > pref_sum) {
        continue;
      } else {
        cout << "YES\n";
        return 0;
      }
  }

  cout << "NO\n";

  return 0;
}