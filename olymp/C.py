#!/usr/bin/env python3
# -*- coding: utf-8 -*-

n = int(input())
if n == 1:
    print(1)
    exit(0)
arr = list(map(int, input().split()))

ans = []
sup = [1, 2, 3, 4, 5]
l = 0
r = 4

last = -1
grow = -2
last = arr[0]
s = [[0, 4]]

for i in range(1, n):
    a = arr[i]
    if a > last:
        if grow == 1 or grow == -2:
            grow = 1
            r -= 1
            s.append((l, r))
            if r < l:
                print(-1)
                exit(0)
        else:
            while s:
                l_, r_ = s.pop()
                for i in range(l_, r_ + 1):
                    if not ans or ans[-1] != i:
                        ans.append(i)
                        break
                else:
                    print(-1)
                    exit(0)
            l = 1
            r = 4
            grow = 1
            s.append((l, r))
    elif a < last:
        if grow == 0 or grow == -2:
            grow = 0
            l += 1
            s.append((l, r))
            if r < l:
                print(-1)
                exit(0)
        else:
            while s:
                l_, r_ = s.pop()
                for i in range(r_, l_ - 1, -1):
                    if not ans or ans[-1] != i:
                        ans.append(i)
                        break
                else:
                    print(-1)
                    exit(0)
            l = 0
            r = 3
            grow = 0
            if i != 1:
                s.append((l, r))
    else:
        while s:
            l_, r_ = s.pop()
            if grow == 0:
                for i in range(l_, r_ + 1):
                    if not ans or ans[-1] != i:
                        ans.append(i)
                        break
                else:
                    print(-1)
                    exit(0)
            else:
                for i in range(r_, l_ - 1, -1):
                    if not ans or ans[-1] != i:
                        ans.append(i)
                        break
                else:
                    print(-1)
                    exit(0)
        l = 0
        r = 4
        grow = -1
        s.append((l, r))
    last = a
if len(s) > 5:
    print(-1)
    exit(0)

while s:
    l_, r_ = s.pop()
    for i in range(l_, r_ + 1):
        if not ans or ans[-1] != i:
            ans.append(i)
            break

for i in range(len(ans)):
    print(ans[i] + 1, end=' ')
print()
