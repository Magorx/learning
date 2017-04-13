#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from random import randint, choice
from time import sleep

SYMBS = [chr(i) for i in range(ord('a'), ord('z') - 1)]

def check_xy(x, y):
    if x < 0:
        return -1
    if y < 0:
        return -2
    if x >= MAP_X:
        return 1
    if y >= MAP_Y:
        return 2

    return 0

class tyle(object):
    def __init__(self):
        self.defined = False
        self.symb = '.'
        self.visit_count = 0

    def __repr__(self):
        return self.symb

    def set(self, symb):
        self.defined = True
        self.symb = symb
        return self.symb

    def define(self, arr, x, y):
        if arr[x][y].defined:
            return self.symb

        self.visit_count += 1
        if self.visit_count > 3:
            return self.set(choice(SYMBS))

        self.symb = ord(define(arr, x - 1, y)) + ord(define(arr, x + 1 , y)) +\
                    ord(define(arr, x, y - 1)) + ord(define(arr, x, y + 1))
        self.symb %= len(SYMBS)
        self.symb = SYMBS[self.symb]
        self.defined = True

        return self.symb


def define(arr, x, y):
    if check_xy(x, y) != 0:
        symb = choice(SYMBS)
        return symb
    else:
        return arr[x][y].define(arr, x, y)


def main():
    global MAP_X, MAP_Y
    MAP_X = 10
    MAP_Y = 10
    arr = [[tyle() for i in range(MAP_Y)] for i in range(MAP_X)]
    arr[0][0].symb = 'a'
    arr[0][0].defined = True
    for z in range(1):
        for i in range(len(arr)):
            for j in range(len(arr[i])):
                arr[i][j].define(arr, i, j)
        for a in range(len(arr)):
            for b in range(len(arr[a])):
                print(arr[a][b], end=' ')
                sleep(0.01)
            print()


if __name__ == "__main__":
    main()
