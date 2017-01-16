dirs = [(0, -1), (-1, -1), (-1, 0), (-1, 1), (0, 1), (1, 1), (1, 0), (1, -1)]


class robot():
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.direction = 6
        mp[y][x] = "#"

    def rotate(self, direction):
        self.direction += direction
        if self.direction > 7:
            self.direction = 0
        if self.direction < 0:
            self.direction = 7

    def move(self):
        self.x += dirs[self.direction][0]
        self.y += dirs[self.direction][1]


fin = open("input.in", "r")
fout = open("input.out", "w")

w, h, n, m = list(map(int, fin.readline().split()))
robs = []
mp = [["." for i in range(w)] for j in range(h)]
for i in range(n):
    x, y = list(map(int, fin.readline().split()))
    robs.append(robot(x, h - y - 1))

for i in range(m):
    string = fin.readline().split()
    if not string:
        break
    string[1] = int(string[1])
    string[2] = int(string[2])
    ii = string[1]
    times = string[2]
    if string[0] == "left":
        for j in range(times):
            robs[ii].rotate(1)
    if string[0] == "right":
        for j in range(times):
            robs[ii].rotate(-1)
    if string[0] == "forward":
        for j in range(times):
            robs[ii].move()
            mp[robs[ii].y][robs[ii].x] = "#"


for i in mp:
    print(*i, file=fout, sep="")

fin.close()
fout.close()