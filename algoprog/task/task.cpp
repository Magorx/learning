#include <bits/stdc++.h>

using namespace std;

const long long OPEN = 1;
const long long CLOSE = 3;
const long long POINT = 2;

struct Point {
  long long time;
  long long stat;
  long long train;

  Point(long long a, long long b, long long c) {
    time = a;
    stat = b;
    train = c;
  }
};

set<long long> trains;
set<long long> stats;

bool OK(Point cur) {
  return trains.find(cur.train) != trains.end() || stats.find(cur.stat) != stats.end();
}

bool operator<(const Point& first, const Point& second) {
  if (first.time < second.time) {
    return true;
  } else if (second.time < first.time) {
    return false;
  } else {
    if (OK(first) > OK(second)) {
      return true;
    } else if (OK(first) < OK(second)) {
      return false;
    } else {
      if (first.stat < second.stat) {
        return true;
      } else {
        return false;
      }
    }
  }
}

int main() {
  long long n, e, m;
  cin >> n >> e >> m;
  e--;
  long long points_cnt = 0;

  vector<Point> arr;
  for (long long i = 0; i < m; ++i) {
    long long k;
    cin >> k;
    points_cnt += k;
    for (long long j = 0; j < k; ++j) {
      long long station, time;
      cin >> station >> time;
      station--;
      arr.push_back({time, station, i});
    }
  }
  sort(arr.begin(), arr.end());

  stats.insert(0);
  long long last_time = -1;
  for (long long i = 0; i < points_cnt; ++i) {
    Point cur = arr[i];
    if (OK(cur)) {
      trains.insert(cur.train);
      stats.insert(cur.stat);
      if (cur.stat == e) {
        cout << cur.time << '\n';
        return 0;
      }
      if (last_time != cur.time) {
        sort(arr.begin(), arr.end());
        last_time = cur.time;
      }
    }
  }
  cout << -1 << '\n';

  return 0;
}