#include <bits/stdc++.h>

using namespace std;

const int NONE = 1;

struct Point {
    int x;
    int type;
    int id;

    Point() {
      x = -1;
      type = -1;
      id = -1;
    }

    Point(int a, int b, int c) {
        x = a;
        type = b;
        id = c;
    }
};

bool operator<(const Point& first, const Point& second) {
    if (first.x < second.x) {
        return true;
    } else if (second.x < first.x) {
        return false;
    } else {
        if (first.type < second.type) {
            return true;
        } else {
            return false;
        }
    }
}

int main() {
  int n, w, l, r;
  cin >> n >> w >> l >> r;
  if (r - l < w) {
    cout << -1 << '\n';
    return 0;
  }

  vector<Point> arr(n);
  for (int i = 0; i < n; ++i) {
    cin >> arr[i].x;
    arr[i].type = NONE;
    arr[i].id = i;
  }
  arr.push_back({l, NONE - 1, -1});
  arr.push_back({r, NONE + 1, -1});
  sort(arr.begin(), arr.end());

  int min_to_remove = 1e9;
  int l_index = 0;
  int ans_l = 1;
  int ans_r = n;
  for (int i = 0; i < n + 2; ++i) {
    Point cur = arr[i];
    if (l_index == i) {
      continue;
    } else {
      if (cur.x - arr[l_index].x < w) {
        continue;
      } else {
        while (cur.x - arr[l_index].x >= w) {
          ++l_index;
        }
        if (l_index == i) {
          cout << 0 << '\n';
          return 0;
        }

        if (i - l_index < min_to_remove) {
          min_to_remove = i - l_index;
          ans_l = l_index;
          ans_r = i - 1;
        }
      }
    }
  }
  cout << "PE PLZ";

  if (min_to_remove == 1e9) {
    cout << n << '\n';
    for (int i = 0; i < n; ++i) {
      cout << i + 1 << '\n';
    }
  } else {
    cout << min_to_remove << '\n';
    for (int i = ans_l; i <= ans_r; ++i) {
      cout << arr[i].id + 1 << '\n';
    }
  }

  return 0;
}