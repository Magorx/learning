#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import re

# Use this to generate all permutations
ERR_MAX_PERMUTATION_REACHED = -1


class Permutator:
    def __init__(self, elements, permutation_length,
                 to_print_while_calculating=False):
        self.elements = elements
        self.elements_count = len(elements)
        self.permutation_length = permutation_length
        self.to_print_while_calculating = to_print_while_calculating
        
        # current_permutation[i] is an index of element, that will be used on place number i
        self.current_permutation = [0 for _ in range(permutation_length)]
    
    def get_current_permutation(self):
        permutation = []
        for i in range(self.permutation_length):
            permutation.append(self.elements[self.current_permutation[i]])
        return permutation
    
    def store_cureent_permutation(self):
        pass
    
    def generate_next_permutation(self, to_print=False):
        elements_count = self.elements_count
        for increasing_element_position in range(self.permutation_length - 1, -1, -1):
            if self.current_permutation[increasing_element_position] != elements_count - 1:
                self.current_permutation[increasing_element_position] += 1
                for nullifieing_element_position in range(increasing_element_position + 1, self.permutation_length):
                    self.current_permutation[nullifieing_element_position] = 0
                if (to_print):
                    print(''.join(self.get_current_permutation()))
                return 0
            
        return ERR_MAX_PERMUTATION_REACHED
    
    def caclulate_all_permutations(self):
        arr = []
        self.current_permutation = [0 for _ in range(self.permutation_length)]
        arr.append(''.join(self.get_current_permutation()))
        
        while not self.generate_next_permutation(self.to_print_while_calculating):
            arr.append(''.join(self.get_current_permutation()))
        return arr


def read_int(message='', end=''):
    print(message, end=end)
    try:
        number = int(input())
    except Exception:
        print('Bad input, shutting down.')
        exit(0)
    
    return number


def main():
    n, k = map(int, input().split())

    all_perms = Permutator([str(i) for i in range(k)], n).caclulate_all_permutations()
    setik = set()
    for s in all_perms:
        max_s = ''
        for i in range(len(s)):
            max_s = max(s, max_s)
            s = s[-1] + s[:-1]
        setik.add(max_s)
    arr = sorted(list(setik))
    arr.reverse()
    
    for i in range(len(arr)):
        m = re.search('^(.+?)\\1*$', arr[i])
        arr[i] = m.group(1)

    print(*arr, sep='')
    

main()
