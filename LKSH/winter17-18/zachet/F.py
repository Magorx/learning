#!/usr/bin/env python3
# -*- coding: utf-8 -*-


K = 29
M = 10000007

K_POWS = []


def a():
    n = 1
    for i in range(3000000):
        K_POWS.append(n)
        n = n * K % M


def main():
    a()
    s = input()
    l = len(s)
    if (l == 1):
        print('YES')
        return
    s += s + s

    h1 = [0 for i in range(len(s) + 5)]
    
    for i in range(len(s)):
        h1[i] = h1[i - 1] * K % M + ord(s[i])

    for i in range(l):
        l1 = i
        j = i + l
        r1 = j // 2
        l2 = i
        r2 = l2 + l // 2
        l1 -= 1
        l2 -= 1

        # print(s[l1:r1], s[l2:r2])

        if ((h1[l1] - (h1[r1] * K_POWS[r1 - l1]) % M + M) % M == (h1[l2] - (h1[r2] * K_POWS[r2 - l2]) % M + M) % M):
            print(i + 1)
            return
    print('-1')
    return


if __name__ == "__main__":
    main()
