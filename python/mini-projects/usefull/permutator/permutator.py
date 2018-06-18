#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Use this to generate all permutations

ERR_MAX_PERMUTATION_REACHED = -1


class Permutator:
    def __init__(self, elements, permutation_length,
                 to_print_while_calculating=False,
                 output_file_name='result.txt'):
        self.elements = elements
        self.elements_count = len(elements)
        self.permutation_length = permutation_length
        self.output_file_name = output_file_name
        self.to_print_while_calculating = to_print_while_calculating
        
        # current_permutation[i] is an index of element, that will be used on place number i
        self.current_permutation = [0 for _ in range(permutation_length)]
        
        file = open(output_file_name, 'w')
        file.close()
    
    def get_current_permutation(self):
        permutation = []
        for i in range(self.permutation_length):
            permutation.append(self.elements[self.current_permutation[i]])
        return permutation
    
    def store_cureent_permutation(self):
        file = open(self.output_file_name, 'a')
        print(''.join(self.get_current_permutation()), file=file)
        file.close()
    
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
        self.current_permutation = [0 for _ in range(self.permutation_length)]
        file = open(self.output_file_name, 'w')
        print(''.join(self.get_current_permutation()), file=file)
        
        while not self.generate_next_permutation(self.to_print_while_calculating):
            print(''.join(self.get_current_permutation()), file=file)
        
        file.close()


def read_int(message='', end=''):
    print(message, end=end)
    try:
        number = int(input())
    except Exception:
        print('Bad input, shutting down.')
        exit(0)
    
    return number

def main():
    print('Enter all symbols, that will be included to elements of permutations, (will be splited by "").')
    elements = list(input())
    
    print('Now enter number of complex elements - string variables that will be used in permutations (will be splited by "\\n")')
    number_of_complex_elements = read_int()
    
    for i in range(number_of_complex_elements):
        elements.append(input())
        
    print('How many elements do you want to see in every permutation?')
    permutation_length = read_int()
    
    print('Enter name of a file, that you want to see a result in?')
    output_file_name = input()
    if not(output_file_name):
        print('Bad input, shutting down.')
        exit(0)
    
    print('OK, calculating...')
    
    permutator = Permutator(elements, permutation_length, output_file_name)
    permutator.caclulate_all_permutations()
    
    print('Done! Have a look at your file.')
    

main()

# TEST
