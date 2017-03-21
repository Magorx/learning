#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from random import randint, choice
import colorama
import tyles

colorama.init(autoreset=True)

class MyWorldTyle(tyles.WorldTyle):
    def __init__(self, symb='.'):
        self.symb = symb
        self.full = False
        self.fore = colorama.Fore.BLACK
        self.back = colorama.Back.BLACK
        self.style = colorama.Style.NORMAL

    def update(self):
        symb = self.symb
        if symb == '^':
            self.name = 'mountain'
            self.fore = colorama.Fore.BLACK
            self.back = colorama.Back.BLACK
            self.style = colorama.Style.BRIGHT
        elif symb == 'T':
            self.name = 'tree'
            self.fore = colorama.Fore.GREEN
            self.back = colorama.Back.GREEN
            self.style = colorama.Style.BRIGHT
        elif symb == '~':
            self.name = 'water'
            self.fore = colorama.Fore.CYAN
            self.back = colorama.Back.CYAN
            self.style = colorama.Style.BRIGHT
        elif symb == '.':
            self.name = 'road'
            self.fore = colorama.Fore.YELLOW
            self.back = colorama.Back.YELLOW
            self.style = colorama.Style.NORMAL
        elif symb == 'X':
            self.name = 'treasure'
            self.fore = colorama.Fore.RED
            self.back = colorama.Back.YELLOW
            self.style = colorama.Style.BRIGHT
        else:
            self.name = 'ERROR'
            self.fore = colorama.Fore.WHITE
            self.back = colorama.Back.WHITE
            self.style = colorama.Style.BRIGHT

    def __repr__(self):
        return self.fore + self.back + self.style + self.symb


class MyWorld(tyles.World):
    def full_update(self):
        for x in range(self.width):
            for y in range(self.height):
                self.map[x][y].update()
        
    def print(self):
        for x in range(self.width):
            for y in range(self.height):
                tyle = self.map[x][y]
                print(tyle, end='')
            print()

def main():
    MODE = True # Change this to see some magic <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    if MODE:
        world = MyWorld(35, 130, tyle_type=MyWorldTyle)
        world.full_update()
        world.GenerateWorld(lands_to_generate=95, to_update=True) # delete this parameter to 
                                                  # see absolute power (random)
        world.full_update()
    else:
        world = tyles.World(20, 50, tyle_type=tyles.WorldTyle)
        world.GenerateWorld(lands_to_generate=95)

    world.print()


if __name__ == '__main__':
    main()
