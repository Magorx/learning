#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from time import sleep
from random import randint, choice

def randstr(length, lvl = 3):
    str = ""
    for i in range(length):
        roll = randint(1, lvl)
        if roll == 1:
            c = chr(randint(48, 57))
        elif roll == 2:
            c = chr(randint(65, 90))
        elif roll == 3:
            c = chr(randint(97, 122))
        elif roll == 4:
            c = choice(SYMBS)
        str = str + c
    return str

def main():
    screne_width = int(input('Eneter your screene width: '))
    while True:
        print(randstr(screne_width))
        sleep(0.05)


if __name__ == "__main__":
    main()
