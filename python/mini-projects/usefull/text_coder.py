#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import random
from random import randint

def encode(file, output_file_name='encoded.txt', seed=None):
    fout = open(output_file_name, 'w')
    if seed is None or seed == 0:
        seed = randint(1, 4284967)
    print(bin(seed)[2:], file=fout)
    random.seed(seed)

    file_text = file.read()
    for symb in file_text:
        new_line_symb = randint(10000, 50000)
        space_symb = randint(50001, 100000)
        fractal = randint(1, 10000)

        if symb == '\n':
            print(bin(new_line_symb)[2:], file=fout)
        elif symb == ' ':
            print(bin(space_symb)[2:], file=fout)
        else:
            print(bin(ord(symb) * fractal)[2:], file=fout)
    
    fout.close()
    return 0

def decode(file, output_file_name='decoded.txt', seed=None):
    fout = open(output_file_name, 'w')
    if seed is None or seed == 0:
        seed = int(file.readline(), 2)
    else:
        file.readline()
    random.seed(seed)
    
    file_text = file.readlines()
    if BEAUTY_PRINT_MODE in MODES or FULL_MODE in MODES:
        print('-----')
    for byte_num in file_text:
        if str(byte_num)[0] == '~':
            continue
        new_line_symb = randint(10000, 50000)
        space_symb = randint(50001, 100000)
        fractal = randint(1, 10000)

        int_num = int(byte_num, 2)
        if int_num == new_line_symb:
            print(file=fout)
            if BEAUTY_PRINT_MODE in MODES or FULL_MODE in MODES:
                print()
        elif int_num == space_symb:
            print(end=' ', file=fout)
            if BEAUTY_PRINT_MODE in MODES or FULL_MODE in MODES:
                print(end=' ')
        else:
            print(chr(int_num // fractal), end='', file=fout)
            if BEAUTY_PRINT_MODE in MODES or FULL_MODE in MODES:
                print(chr(int_num // fractal), end='')

    if BEAUTY_PRINT_MODE in MODES or FULL_MODE in MODES:
        print('\n-----')

    fout.close()
    return 0


FULL_MODE = 10
BEAUTY_PRINT_MODE = 5
OWN_SEED_MODE = 3

def main():
    global MODES
    MODES = [OWN_SEED_MODE]
    seed = None

    if FULL_MODE in MODES:
        print('You are using FULL_MODE mode! YES to continue')
        if input():
            exit(0)

    print('Which file do you want to use?')
    file_name = input()
    try:
        file = open(file_name, 'r')
    except:
        print('Failed founding file')
        exit(0)

    print('Do you want to encode or decode it? (e/d)')
    ans = input()

    print('How to name output file?')
    new_file_name = input()
    if not new_file_name:
        new_file_name = 'coder_result.txt'

    if OWN_SEED_MODE in MODES or FULL_MODE in MODES:
        print('Which seed do you want to use?')
        try:
            seed = input()
            if not seed:
                seed = None
            else:
                seed = int(seed)
        except:
            print('Invalid seed')
            seed = None

    if ans[0] == 'e':
        encode(file, new_file_name, seed=seed)
    elif ans[0] == 'd':
        decode(file, new_file_name, seed=seed)
    else:
        print('Invalid answer')
        exit(0)



    '''resourses
    d = {}
    string = ''
    while True:
        string = input()
        if string == 'stop':
            break
        if string == 'show':
            print('---Resourses now---')
            for i in d:
                print(i, d[i])
            print('-------------------')
            continue

        string = string.split()
        if len(string) > 2:
            key = ''
            for i in range(len(string) - 1):
                if key == '':
                    key = string[i]
                else:
                    key = key + ' ' + string[i]
        else:
            key = string[0]

        val = string[-1]
        val = int(val[1:len(val) - 1])
        if key in d:
            d[key] += val
        else:
            d[key] = val
    '''


if __name__ == "__main__":
    main()
