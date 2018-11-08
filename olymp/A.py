#!/usr/bin/env python3
# -*- coding: utf-8 -*-

n = int(input())
arr = list(map(int, list(input())))

pref_s = 0
s = 0
last_index = 0

for i in range(n - 1):
    pref_s += arr[i]
    last_index = i + 1

    flag = True
    s = 0
    while (last_index < n and flag):
        for j in range(last_index, n):
            s += arr[j]
            if s > pref_s:
                flag = False
                break
            elif s == pref_s:
                s = 0
                last_index = j + 1
                break
        else:
            flag = False
    if flag and s == 0:
        #print(i, pref_s, last_index, s)
        print('YES')
        exit(0)

print('NO')