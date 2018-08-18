#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>

using namespace std;

struct Point {
  int x;
  int y;
  Point(int _x, int _y){
    x = _x;
    y = _y;
  }
};

vector<vector<int>> SHIFTS {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};


string find_path(vector<vector<Point>>& parents, Point goal) {
  char c;
  Point prev = parents[goal.x][goal.y];
  if (prev.x == -1) {
    return "";
  }
  if (prev.x < goal.x) {
    c = 'S';
  } else if (prev.x > goal.x) {
    c = 'N';
  } else if (prev.y < goal.y) {
    c = 'E';
  } else {
    c = 'W';
  }
  return c + find_path(parents, prev);
}


int main() {
  int n, m, x1, y1, x2, y2;
  cin >> n >> m >> x1 >> y1 >> x2 >> y2;
  --x1;
  --x2;
  --y1;
  --y2;
  vector<vector<char>> world(n, vector<char>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> world[i][j];
    }
  }
  vector<vector<Point>> parents(n, vector<Point>(m, {-1, -1}));
  vector<vector<char>> visited(n, vector<char>(m, 0));
  vector<vector<int>> times(n, vector<int>(m, 10000000));
  vector<vector<int>> d(n, vector<int>(m, -1));

  times[x1][y1] = 0;

  deque<Point> q;
  q.push_back({x1, y1});
  while (!q.empty()) {
    Point cur_point = q.front();
    // cout << "cur " << cur_point.x << ' ' << cur_point.y << '\n';
    visited[cur_point.x][cur_point.y] = 1;
    q.pop_front();
    if (cur_point.x == x2 && cur_point.y == y2) {
      continue;
    }
    for (int i = 0; i < (int)SHIFTS.size(); ++i) {
      vector<int> shift = SHIFTS[i];
      int new_x = cur_point.x + shift[0];
      int new_y = cur_point.y + shift[1];
      // cout << new_x << ' ' << new_y << endl;
      if (new_x < 0 || new_x >= n || new_y < 0 || new_y >= m) {
        continue;
      }
      if (world[new_x][new_y] == '.') {
        if (times[cur_point.x][cur_point.y] + 1 < times[new_x][new_y]) {
          parents[new_x][new_y] = {cur_point.x, cur_point.y};
          times[new_x][new_y] = times[cur_point.x][cur_point.y] + 1;
          q.push_front({new_x, new_y});
        }
      }
      if (world[new_x][new_y] == 'W') {
        if (times[cur_point.x][cur_point.y] + 2 < times[new_x][new_y]) {
          parents[new_x][new_y] = {cur_point.x, cur_point.y};
          times[new_x][new_y] = times[cur_point.x][cur_point.y] + 2;
          q.push_back({new_x, new_y});
        }
      }
    }
  }
  string path = find_path(parents, {x2, y2});
  if (path.length() == 0) {
    cout << -1 << '\n';
  } else {
    reverse(path.begin(), path.end());
    cout << times[x2][y2] << '\n' << path << '\n';
  }

  return 0;
}