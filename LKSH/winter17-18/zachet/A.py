#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# ZADACHA NA PROVERKY VOZMOJNOSTI PREVRASHENIA STR1 V STR2 PYTEM SHIFRA ZAMENI


def main():
    str1 = input()
    str2 = input()
    if (len(str1) != len(str2)):
        print('NO')
        return
    arr1 = []
    arr2 = []
    for i in range(len(str1)):
        if str1[i] >= 'a' and str1[i] <= 'z':
            arr1.append(1)
        elif str1[i] >= 'A' and str1[i] <= 'Z':
            arr1.append(2)
        else:
            arr1.append(0)
        if str2[i] >= 'a' and str2[i] <= 'z':
            arr2.append(1)
        elif str2[i] >= 'A' and str2[i] <= 'Z':
            arr2.append(2)
        else:
            arr2.append(0)
    if arr1 != arr2:
        print('NO')
        return
    str1 = str1.lower()
    str2 = str2.lower()
    
    d1 = dict()
    d2 = dict()
    for c in range(ord('z') - ord('a') + 1):
        d1[chr(ord('a') + c)] = 0
        d2[chr(ord('a') + c)] = 0
    for i in range(len(str1)):
        c1 = str1[i]
        c2 = str2[i]
        if c1 < 'a' or c1 > 'z':
            if c1 == c2:
                continue
            else:
                print('NO')
                return
        if c2 < 'a' or c2 > 'z':
            if c1 == c2:
                continue
            else:
                print('NO')
                return
        # print(c1, c2, d1[c1], d2[c2])
        if d1[c1] == 0:
            if d2[c2] != c1 and d2[c2] != 0:
                print('NO')
                return
            d1[c1] = c2
            d2[c2] = c1
        elif d2[c2] == 0:
            if d1[c1] != c2 and d1[c1] != 0:
                print('NO')
                return
            d2[c2] = c1
            d1[c1] = c2
        else:
            if d1[c1] != c2 or d2[c2] != c1:
                print('NO')
                return
    print('YES')
    return


if __name__ == "__main__":
    main()
