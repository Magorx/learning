#!/usr/bin/env python3
# -*- coding: utf-8 -*-

arr = [0, 0, 0, 0, 1] + [-1 for i in range(2000)]

def f(n, player):
    if arr[n] != -1:
        return arr[n] ^ player
    else:
        if player == 0:
            arr[n] = min(f(n - 2, player ^ 1), f(n - 3, player ^ 1))
        else:
            arr[n] = max(f(n - 2, player ^ 1), f(n - 3, player ^ 1))
        return arr[n]

def main():
    n = int(input())
    if f(n, 0) == 0:
        print('First player wins')
    else:
        print('First player loses')

if __name__ == "__main__":
    main()
