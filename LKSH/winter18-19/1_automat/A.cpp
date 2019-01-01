#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> arr(8, vector<int>(256, -1));

int get_state(int cur_state, char c) {
  if (arr[cur_state][c] == -1) {
    return cur_state;
  } else {
    return arr[cur_state][c];
  }
}

int main() {
  int c;
  cin >> c;
  cout << c;
  // freopen("comments.in", "r", stdin);
  string s;
  string text;
  string output;

  arr[0]['/'] = 1;
  for (size_t i = 0; i < arr[0].size(); ++i) {
    arr[1][i] = 0;
  }
  arr[1]['{'] = 5;
  arr[1]['/'] = 2;
  arr[2]['\n'] = 0;
  arr[1]['*'] = 7;
  for (size_t i = 0; i < arr[0].size(); ++i) {
    arr[7][i] = 3;
  }
  arr[7]['*'] = 4;
  arr[3]['*'] = 4;
  for (size_t i = 0; i < arr[0].size(); ++i) {
    arr[4][i] = 3;
  }
  arr[4]['/'] = 6;
  arr[4]['*'] = 4;
  arr[0]['{'] = 5;
  arr[5]['}'] = 6;
  for (size_t i = 0; i < arr[0].size(); ++i) {
    arr[6][i] = 0;
  }
  arr[6]['/'] = 1;
  arr[6]['{'] = 5;
  vector<char> to_write {1, 1, 0, 0, 0, 0, 0, 0};
  vector<char> to_delete {0, 0, 1, 0, 0, 0, 0, 1};

  int cur_state = 0;
  int deleted = 0;
  while (getline(cin, s)) {
    s += '\n';
    for (char c : s) {
      cur_state = get_state(cur_state, c);
      if (to_write[cur_state]) {
        output += c;
      }
      if (to_delete[cur_state] > deleted) {
        output.pop_back();
        deleted += 1;
      } else if (!to_delete[cur_state] && deleted) {
        deleted = 0;
      }
    }
  }

  // freopen("comments.out", "w", stdout);
  cout << output;
  return 0;
}