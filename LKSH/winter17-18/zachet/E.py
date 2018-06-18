#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# CHECK HOW MANY EMAILS IN TEXT


import re


def main():
    regexp = re.compile('([a-zA-Z][a-zA-Z]*(\.[^@. ])*)+@[a-zA-Z]([a-zA-Z]*(\.[^@. ])*)*')
    cnt = 0
    text = open('email.in').read()
    for word in text.split():
        if regexp.fullmatch(word):
            cnt += 1
    print(cnt)


if __name__ == "__main__":
    main()
