#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys

def file_logger(file=sys.stdout, lvl=1):
    def logger(func):
        def wrapper(*args, **kwargs):
            if lvl > 0:
                print('Called [', func.__name__, ']', sep='', file=file)
            result = func(*args, **kwargs)
            if lvl > 1:
                print('[', func.__name__, '] returned ', result, sep='', file=file)
            return result
        return wrapper
    return logger

@file_logger(lvl=2)
def foo(a, b):
    return a * b


def main():
    print(foo(2, 3))


if __name__ == "__main__":
    main()
