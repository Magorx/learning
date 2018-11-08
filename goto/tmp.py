#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from queue import deque
shifts = [[0, 1], [1, 0], [0, -1], [-1, 0]]
w, h = map(int, input().split())
visited = [[0 for i in range(w)] for j in range(h)]
q = deque()
arr = []
for i in range(w):
    arr.append(list((input())))
    if arr[-1].count('@') == 1:
        start_x, start_y = i, arr[-1].index('@')

q.append([start_x, start_y])
cnt = 0
while len(q):
    cur_x, cur_y = q.popleft()
    if arr[cur_x][cur_y] == '*':
        cnt += 1
    for shift in shifts:
        new_x, new_y = cur_x + shift[0], cur_y + shift[1]
        if (new_x < 0 or new_x >= w or new_y < 0 or new_y >= h):
            continue
        if arr[new_x][new_y] == '#':
            continue
        if not visited[new_x][new_y]:
            q.append([new_x, new_y])
            visited[new_x][new_y] = 1

print(cnt)