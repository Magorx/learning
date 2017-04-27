#!/usr/bin/env python3
# -*- coding: utf-8 -*-


def attack(lvl):
    res = 1.05
    for i in range(1, lvl + 1):
        res *= res
    return int(res)


def defence(lvl):
    res = 0
    for i in range(1, lvl + 1):
        res += 1.10 ** i
    return int(res)


def main():
    for i in range(10):
        print(i, attack(i), defence(i))


if __name__ == "__main__":
    main()
