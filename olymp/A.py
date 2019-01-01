#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def read():
    s = input()
    letter = s[0]
    first = ord(letter) - ord('a') 
    second = int(s[1])
    return (first, second)

def f(a, b):
    return abs(a - b)

x1, y1 = read()
x2, y2 = read()
print(min(f(x1, x2), f(y1, y2)), max(f(x1, x2), f(y1, y2)))
