#!/usr/bin/env python3
# -*- coding: utf-8 -*-


def main():
    s = input()
    if s == '':
        print('(a|b|c)(a|b|c)*', end='')
        print()
        return

    for i in range(len(s)):
        print('(', end='')
        for j in range(i):
            print('(a|b|c)', end='')
        print(')|', end='')

    for i in range(len(s)):
        print('(', end='')
        for j in range(i):
            print('(a|b|c)', end='')
        if s[i] == 'a':
            print('(b|c)', end='')
        if s[i] == 'b':
            print('(a|c)', end='')
        if s[i] == 'c':
            print('(b|a)', end='')
        for j in range(i, len(s) - 1):
            print('(a|b|c)', end='')
        print(')|', end='')

    print('(', end='')
    for i in range(len(s) + 1):
        print('(a|b|c)', end='')
    print('(a|b|c)*)', end='')
    print()


if __name__ == "__main__":
    main()
