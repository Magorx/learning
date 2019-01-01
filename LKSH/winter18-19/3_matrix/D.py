#!/usr/bin/env python3
# -*- coding: utf-8 -*-


def zareshat(a, b):
    r = 0
    c = 0
    was_free = False
    row_cnt = len(a)
    column_cnt = len(a[0])

    while (r < row_cnt and c < column_cnt):
        free = True
        for i in range(r, row_cnt):
            if a[i][c] != 0:
                free = False
                tmp = a[i][::]
                a[i] = a[r][::]
                a[r] = tmp[::]
                tmp = b[i]
                b[i] = b[r]
                b[r] = tmp
                break
        if not free:
            for j in range(row_cnt):
                if j != r:
                    t = a[j][c]
                    for k in range(column_cnt):
                        a[j][k] = a[j][k] * a[r][c] - a[r][k] * t
                    b[j] = b[j] * a[r][c] - b[r] * t
            r += 1
        else:
            was_free = True
        c += 1

    while r < row_cnt:
        if b[r]:
            return 0
        r += 1

    if was_free:
        return 1

    ans = []
    for i in range(column_cnt):
        ans.append(b[i] / a[i][i])
    return ans


n = int(input())
a = []
b = []
for i in range(n):
    arr = list(map(float, input().split()))
    a.append(arr[:-1])
    b.append(arr[-1])

ret = zareshat(a, b)
if ret == 0:
    print('impossible')
elif ret == 1:
    print('infinity')
else:
    print('single')
    print(*ret)
