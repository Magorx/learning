#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from random import randint, choice

class tyle(object):
    def __init__(self):
        self.defined = False
        self.symb = '.'

    def __repr__(self):
        return self.symb

    def set(self, symb):
        self.defined = True
        self.symb = symb

    def define(self, arr, x, y):
        if arr[x][y].defined:
            return self.symb
        elif arr[x][y - 1].defined:
            self.symb = arr[x][y - 1].symb
        elif arr[x - 1][y].defined:
            self.symb = arr[x - 1][y].symb
        else:
            self.symb = choice([chr(i) for i in range(ord('a'), ord('z') + 1)])
        self.defined = True

        return self.symb




def main():
    MAP_X = 10
    MAP_Y = 10
    arr = [[tyle() for i in range(MAP_Y)] for i in range(MAP_X)]
    for i in range(len(arr)):
        for j in range(len(arr[i])):
            arr[i][j].define(arr, i, j)
    for i in arr:
        print(*i)


if __name__ == "__main__":
    main()
