#!/usr/bin/env python3
# -*- coding: utf-8 -*-


from random import randint, choice
from time import sleep
import re

pat = re.compile(r'[0-9]+\.')



class Defenition:
    def __init__(self, id, name, definition):
        self.id = id
        self.name = name
        self.text = definition

    def __repr__(self):
        return str(self.id) + '. ' + self.name + ' - ' + self.text


class Dict:
    def __init__(self):
        self.dict = []
        self.len = 0

    def get_random(self):
        return choice(self.dict)

    def add(self, defenition):
        self.dict.append(defenition)
        self.len += 1


DICT = Dict()



def parse(file):
    text = open(file, 'r').read()

    index = 0
    name = ''
    def_text = ''
    name_ended = False

    for word in text.split():
        if re.fullmatch(pat, word):
            new_def = Defenition(index, name, def_text)
            print(new_def)
            DICT.add(new_def)
            index += 1
            name = ''
            def_text = ''
            name_ended = False
        elif word == '-' or word == '--':
            name_ended = True
        else:
            if name_ended:
                def_text = def_text + ' ' + word
            else:
                name = name + ' ' + word

parse('defs.txt')
