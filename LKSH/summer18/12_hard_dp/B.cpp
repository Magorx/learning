#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> parents;
vector<long long> dp;

template <typename T>
bool relax(T& first, const T& second) {
  if (first < second) {
    first = second;
    return true;
  } else {
    return false;
  }
}

struct Meeting {
  int min_happiness;
  int max_happiness;
  int delta_happiness;

  Meeting(int a, int b, int c) {
    min_happiness = a;
    max_happiness = b;
    delta_happiness = c;
  }
};

long long max_meetings(int n, vector<Meeting>& meetings, int init_happiness) {
  int cur_happiness = init_happiness;
  dp.resize((1 << n), 0);
  for (int mask = 0; mask < (1 << n); ++mask) {
    cur_happiness = init_happiness;
    for (int i = 0; i < n; ++i) {
      if (mask & (1 << i)) {
        cur_happiness += meetings[i].delta_happiness;
      }
    }
    for (int i = 0; i < n; ++i) {
      if ((mask & (1 << i)) == 0) {
        if (cur_happiness >= meetings[i].min_happiness && cur_happiness <= meetings[i].max_happiness) {
          if (relax(dp[mask | (1 << i)], dp[mask] + 1)) {
            parents[mask | (1 << i)] = i;
          }
        }
      }
    }
  }

  int mask = 0;
  int max_v = 0;
  for (int i = 0; i < (1 << n); ++i) {
    if (dp[i] >= max_v) {
      mask = i;
      max_v = dp[i];
    }
  }

  return dp[mask];
}

vector<int> get_order(int n) {
  int mask = 0;
  int max_v = 0;
  for (int i = 0; i < (1 << n); ++i) {
    if (dp[i] >= max_v) {
      mask = i;
      max_v = dp[i];
    }
  }
  vector<int> ret;
  while (mask > 0) {
    ret.push_back(parents[mask] + 1);
    mask ^= (1 << parents[mask]);
  }

  if (ret[ret.size() - 1] == 0) {
    ret.pop_back();
  }
  reverse(ret.begin(), ret.end());

  return ret;
}

int main() {
  int n, init_happiness;
  cin >> n >> init_happiness;
  parents.resize((1 << n), -1);
  vector<Meeting> meetings; 
  for (int i = 0; i < n; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    meetings.push_back({a, b, c});
  }

  cout << max_meetings(n, meetings, init_happiness) << '\n';
  for (auto x : get_order(n)) {
    cout << x << ' ';
  }
  cout << '\n';

  return 0;
}