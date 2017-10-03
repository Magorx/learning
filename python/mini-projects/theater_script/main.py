#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from theater_script import ScriptExecuter


def get_word(string, start_index, end_symbs=[' ']):
    word = ''
    for i in range(start_index, len(string)):
        symb = string[i]
        if symb in end_symbs:
            break
        else:
            word = word + symb
    return word


class Performance(object):
    def __init__(self, scenario):
        self.scenario = scenario

    def parse_scenario(self):
        pass


class Scene(object):
    def __init__(self, text, choices, variants):
        if len(choices) != len(variants):
            raise IndexError

        self.text = text
        self.choices = choices
        self.variants = variants

    def __call__(self):
        text = self.text
        to_print = True
        for symb_index in range(len(text)):
            symb = text[symb_index]
            if symb == '#' and text[symb_index - 1] != '/':
                command = get_word(text, symb_index + 1)
                args = get_word(text, symb_index + len(command), ['\n']).split()
                to_print = script_reader.execute_expr(command + ' ' + args)
            
            if to_print:
                print(symb, end='')


def main():
    global script_reader
    script_reader = ScriptExecuter()


if __name__ == "__main__":
    main()
