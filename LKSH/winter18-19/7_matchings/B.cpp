#include <bits/stdc++.h>
using namespace std;

const char WALL = '.';

vector<vector<int>> used;
vector<vector<char>> arr;
vector<vector<pair<int, int>>> match; // black
const vector<vector<int>> SHIFTS = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
const pair<int, int> NONE = {-1, -1};
int t = 1;

int n, m, a, b;

bool dfs(int x, int y) {
  if (used[x][y] == t) {
    return false;
  }
  used[x][y] = t;
  for (auto shift : SHIFTS) {
    int nx = x + shift[0];
    int ny = y + shift[1];
    if (nx < 0 || ny < 0 || ny >= m || nx >= n || arr[nx][ny] == WALL) {
      continue;
    }
    if (match[nx][ny] == NONE || dfs(match[nx][ny].first, match[nx][ny].second)) {
      match[nx][ny] = {x, y};
      match[x][y] = {nx, ny};
      return true;
    }
  } 
  return false;
}

int main() {
  cin >> n >> m >> b >> a; // a = 1*1, b = 1*2
  arr.resize(n);
  used.resize(n);
  match.resize(n);
  int free = 0;
  for (int i = 0; i < n; ++i) {
    arr[i].resize(m);
    used[i].resize(m);
    match[i].resize(m, NONE);
    for (int j = 0; j < m; ++j) {
      cin >> arr[i][j];
      if (arr[i][j] != WALL) {
        ++free;
      }
    }
  }

  if (2 * a <= b) {
    cout << free * a << '\n';
    return 0;
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (((i + j) % 2) == 0) {
        t += 1;
        if (arr[i][j] != WALL) {
          dfs(i, j);
        }
      }
    }
  }

  int cost_b = 0;
  int cost_a = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (arr[i][j] != WALL) {
        if (match[i][j] != NONE) {
          cost_b += b;
        } else {
          cost_a += a;
        }
      }
    }
  }
  cost_b /= 2;
  
  int cost = cost_b + cost_a;
  cout << cost << '\n';

  return 0;
}