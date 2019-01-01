#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>

char board[8][9];

int main() {
  while (1) {
    static char color[10];
    assert(scanf("%s", color) == 1);
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        assert(scanf("%s", board[i]) == 1);
      }
    }

    int x, y;
    do {
      x = rand() % 8;
      y = rand() % 8;
    } while (board[x][y] != '.');

    printf("%d %d\n", x, y);
    fflush(stdout);
  }
  return 0;
}
