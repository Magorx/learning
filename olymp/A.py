#!/usr/bin/env python3
# -*- coding: utf-8 -*-

n = int(input())
arr = []
for i in range(n):
    arr.append(list(map(int, input().split())) + [i])
arr.sort()
ans = [[-1, -1] for i in range(n)]

last = -1
for i in range(n):
    cur = arr[i]
    if last > cur[1]:
        continue
    ans[cur[2]] = [max(last, cur[0]), cur[1]]
    last = cur[1]

for i in range(n):
    print(*ans[i])