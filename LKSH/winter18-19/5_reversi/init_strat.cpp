#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> SHIFTS = {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}};
const int FREE = -1;
const int WHITE = 0;
const int BLACK = 1;

vector<vector<int>> coolness_map = 
{
  {+9, -3, 4, 4, 4, 4, -3, +9},
  {-3, -3, 1, 1, 1, 1, -3, +9},
  {4, 1, 1, 1, 1, 1, 1, 4}, 
  {4, 1, 1, 1, 1, 1, 1, 4}, 
  {4, 1, 1, 1, 1, 1, 1, 4}, 
  {4, 1, 1, 1, 1, 1, 1, 4}, 
  {-3, -3, 1, 1, 1, 1, -3, -3},
  {+9, -3, 4, 4, 4, 4, -3, 9}, 
};

struct Strat {
  int estimate(vector<vector<int>> &field) {
    int w = 0;
    int b = 0;
    for (int i = 0; i < field.size(); ++i) {
      for (int j = 0; j < field[0].size(); ++j) {
        if (field[i][j] == 'w') {
          w += coolness_map[i][j];
        } else if (field[i][j] == 'b') {
          b += coolness_map[i][j];
        }
      }
    }
    return w - b;
  }

  bool turn_is_possible(vector<vector<int>> &field, int color, int x, int y) {
    if (field[x][y] != FREE) {
      return false;
    }

    for (auto shift : SHIFTS) {
      int dx = 0;
      int dy = 0;
      bool was_enemy = false;
      while (true) {
        dx += shift[0];
        dy += shift[1];
        int cur_x = x + dx;
        int cur_y = y + dy;
        if (cur_x >= 8 || cur_y >= 8 || cur_x < 0 || cur_y < 0) {
          break;
        }
        if (field[cur_x][cur_y] == FREE) {
          break;
        }
        if (field[cur_x][cur_y] == color) {
          while (dx || dy) {
            dx -= shift[0];
            dy -= shift[1];
            cur_x = x + dx;
            cur_y = y + dy;
            // cout << field[cur_x][cur_y] << ' ' << color << ' ' << (color ^ 1) << '\n';
            if (field[cur_x][cur_y] == (color ^ 1)) {
              was_enemy = true;
            }
          }
          if (was_enemy) {
            return true;
          }
          break;
        }
      }
    }
    return false;
  }

  vector<pair<int, int>> get_possible_moves(vector<vector<int>> &field, int color) {
    vector<pair<int, int>> ans;
    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 8; ++j) {
        if (turn_is_possible(field, color, i, j)) {
          ans.push_back({i, j});
        }
      }
    }
    return ans;
  }

  pair<int, int> make_turn(vector<vector<int>> &field, int color, int depth=-1) {
    auto turns = get_possible_moves(field, color);
    int res = 0;
    if (depth == -1) {
      /*for (auto x : turns) {
        cout << x.first << '-' << x.second << '\n';
      }*/
      int move_x = -1;
      int move_y = -1;
      if (color == WHITE) {
        res = -1000;
        int move_x = -1;
        int move_y = -1;
        for (auto turn : turns) {
          int x = turn.first;
          int y = turn.second;
          field[x][y] = color;
          auto ret = make_turn(field, color ^ 1, 4);
          if (ret.first > res) {
            res = ret.first;
            move_x = x;
            move_y = y;
          }
        }
      } else {
        res = 1000;
        for (auto turn : turns) {
          int x = turn.first;
          int y = turn.second;
          field[x][y] = color;
          auto ret = make_turn(field, color ^ 1, 4);
          if (ret.first < res) {
            res = ret.first;
            move_x = x;
            move_y = y;
          }
        }
      }
      return {move_x, move_y};
    } else if (depth > 0) {
      if (color == WHITE) {
        
        for (auto turn : turns) {
          int x = turn.first;
          int y = turn.second;
          field[x][y] = color;
          auto ret = make_turn(field, color ^ 1, depth - 1);
          if (ret.first > res) {
            res = ret.first;  
          }
        }
        return {res, 0};
      } else {
        res = 1000;
        for (auto turn : turns) {
          int x = turn.first;
          int y = turn.second;
          field[x][y] = color;
          auto ret = make_turn(field, color ^ 1, depth - 1);
          if (ret.first < res) {
            res = ret.first;  
          }
        }
        return {res, 0};
      }
    } else {
      return {estimate(field), 0};
    }
  }
};


int main() {
  Strat strat;
  while (true) {
    string c;
    cin >> c;
    int color;
    if (c == "White") {
      color = WHITE;
    } else {
      color = BLACK;
    }
    vector<vector<int>> field(8, vector<int>(8, -1));
    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 8; ++j) {
        char chr;
        cin >> chr;
        if (chr == '.') {
          field[i][j] = FREE;
        } else if (chr == 'W') {
          field[i][j] = WHITE;
        } else {
          field[i][j] = BLACK;
        }
      }
    }
    auto move = strat.make_turn(field, color);
    cout << move.second + 1 << ' ' << move.first + 1 << endl;
  }

  return 0;
}