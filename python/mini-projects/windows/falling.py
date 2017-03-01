import time
import random

class ball:
    x = 0
    y = 0
    symb = "0"
    def move_down(self):
        self.x += 1
    def move_right(self):
        self.y += 1
    def move_left(self):
        self.y -= 1

def foo(ball):
    if map[ball.x+1][ball.y] != wall_symb:
        map[ball.x][ball.y] = back_symb
        ball.move_down()
        map[ball.x][ball.y] = ball.symb
        return DOWN
    if map[ball.x][ball.y-1] != wall_symb and map[ball.x][ball.y+1] != wall_symb:
        if random.randint(1, 2) == 1:
            map[ball.x][ball.y] = back_symb
            ball.move_left()
            map[ball.x][ball.y] = ball.symb
            return LEFT
        else:
            map[ball.x][ball.y] = back_symb
            ball.move_right()
            map[ball.x][ball.y] = ball.symb
            return RIGHT
    if map[ball.x][ball.y-1] != wall_symb and map[ball.x][ball.y+1] == wall_symb:
        map[ball.x][ball.y] = back_symb
        ball.move_left()
        map[ball.x][ball.y] = ball.symb
        return LEFT
    if map[ball.x][ball.y-1] == wall_symb and map[ball.x][ball.y+1] != wall_symb:
        map[ball.x][ball.y] = back_symb
        ball.move_right()
        map[ball.x][ball.y] = ball.symb
        return RIGHT
    
def map_show(map):
    for i in map:
        print(*i)
    print("=" * size * 2)
    return 0

print("\n" * 50)
LEFT = 1
RIGHT = 2
UP = 3
DOWN = 4
STAY = 5
size = 10
wall_symb = '|'
back_symb = '*'
ball_symb = "0"
thing = ball()
thing.x = 1
thing.y = 2
thing.symb = ball_symb
arr = [0 for i in range(5)]
map = [[back_symb for i in range(1, size + 1)] for i in range(size)]
for i in range(5):
    thing.y += 1
    arr[i] = ball()
    arr[i].x = thing.x
    arr[i].y = thing.y
    map[arr[i].x][arr[i].y] = thing.symb
for i in range(size):
    left = (size - i) // 2
    right = i + left
    for j in range(size):
        if j < right and j > left:
            map[i][j] = wall_symb
map = [["|", "*", "*", "*", "*", "*", "*", "*", "*", "|"],
       ["|", "*", "*", "*", "*", "*", "*", "*", "*", "|"],
       ["|", "*", "*", "*", "*", "*", "*", "*", "*", "|"],
       ["|", "*", "*", "*", "|", "|", "|", "*", "*", "|"],
       ["|", "*", "|", "|", "|", "*", "|", "*", "*", "|"],
       ["|", "*", "*", "*", "*", "*", "*", "*", "*", "|"],
       ["|", "*", "*", "*", "*", "*", "*", "*", "*", "|"],
       ["|", "*", "*", "*", "*", "*", "*", "*", "*", "|"],
       ["|", "*", "*", "*", "*", "*", "*", "*", "*", "|"],
       ["|", "|", "|", "|", "|", "|", "|", "|", "|", "|"],]
map_show(map)
for i in range(100):
    print("\n" * 50)
    time.sleep(0.3)
    for j in range(len(arr)):
        foo(arr[j])
    map_show(map)
    a = input()
