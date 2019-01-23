#!/usr/bin/env python3
# -*- coding: utf-8 -*-


def binpow(n, p):
    if p == 0:
        return 1
    elif p == 1:
        return n
    else:
        if p % 2:
            return binpow(n, p - 1) * n
        else:
            a = binpow(n, p // 2)
            return a * a


n, s, a, b = map(int, input().split())
if n == 1:
    print(1)
x = binpow(2 / (n * (n - 1)), s)
for i in range(s):
    
if a == b:
    print(1 - x * (n - 1))
else:
    print(x)