#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import tyles
from tkinter import *


class MyWorldTyle(tyles.WorldTyle):
    def __init__(self, canvas, symb='.'):
        self.symb = symb
        self.full = False
        self.canvas = canvas

    def update(self):
        symb = self.symb
        if symb == '^':
            self.canvas.config(bg='#000000')
        elif symb == 'T':
            self.canvas.config(bg='#00FF00')
        elif symb == '~':
            self.canvas.config(bg='#0000FF')
        elif symb == '.':
            self.canvas.config(bg='#CCCCCC')
        elif symb == 'X':
            self.canvas.config(bg='#FFFFFF')
        else:
            self.name = 'ERROR'
            self.fore = colorama.Fore.WHITE
            self.back = colorama.Back.WHITE
            self.style = colorama.Style.BRIGHT


class MyWorld(tyles.World):
    def __init__(self, width, height, tyle_type=WorldTyle, common_symb='.'):
        self.map = [[tyle_type(Canvas(width=side_px, height=side_px), 
                     symb=common_symb) for i in range (height)] for j in range(width)]
        self.common_symb = common_symb
        self.time = 0
        self.width = width
        self.height = height
        self.square = width * height

        self.root_window = Tk()
        side_px = 50
        canv_arr = [[self.map[x][y].canvas for i in range(height)] for j in range(width)]
        for x in range(width):
            for y in range(height):
                canv_arr[x][y].grid(self.root, row=x, column=y)
        self.canv_arr = canv_arr

    def full_update(self):
        for i in range(self.width):
            for j in range(self.height):
                self.map[x][y].update()


def main():
    MODE = True # Change this to see some magic <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    if MODE:
        world = MyWorld(35, 130, tyle_type=MyWorldTyle)
        world.full_update()
        world.GenerateWorld(lands_to_generate=95) # delete this parameter to 
                                                  # see absolute power (random)
        world.full_update()
    else:
        world = tyles.World(20, 50, tyle_type=tyles.WorldTyle)
        world.GenerateWorld(lands_to_generate=95)

    world.print()


if __name__ == "__main__":
    main()
