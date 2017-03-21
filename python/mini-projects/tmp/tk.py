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
            self.canvas.create_image(25, 25, image=PhotoImage(file='mountain.png'))
        elif symb == 'T':
            self.canvas.create_image(25, 25, image=PhotoImage(file='tree.png'))
        elif symb == '~':
            self.canvas.create_image(25, 25, image=PhotoImage(file='water.png'))
        elif symb == '.':
            self.canvas.create_image(25, 25, image=PhotoImage(file='road.png'))
        elif symb == 'X':
            self.canvas.config(bg='#FFFFFF')
        else:
            self.name = 'ERROR'
            self.fore = colorama.Fore.WHITE
            self.back = colorama.Back.WHITE
            self.style = colorama.Style.BRIGHT


class MyWorld(tyles.World):
    def __init__(self, width, height, side_px=50, tyle_type=None, common_symb='.'):
        self.root_window = Tk()
        self.map = [[tyle_type(Canvas(self.root_window, width=side_px, height=side_px), 
                     symb=common_symb) for i in range (height)] for j in range(width)]
        self.common_symb = common_symb
        self.time = 0
        self.width = width
        self.height = height
        self.square = width * height
        
        canv_arr = [[self.map[x][y].canvas for y in range(height)] for x in range(width)]
        for x in range(width):
            for y in range(height):
                canv_arr[x][y].grid(row=x, column=y)
        self.canv_arr = canv_arr

    def full_update(self):
        for x in range(self.width):
            for y in range(self.height):
                self.map[x][y].update()


def main():
    MODE = True # Change this to see some magic <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    if MODE:
        world = MyWorld(10, 10, tyle_type=MyWorldTyle)
        world.full_update()
        world.GenerateWorld(lands_to_generate=100) # delete this parameter to 
                                                  # see absolute power (random)
        world.full_update()
        world.print()
        world.root_window.mainloop()
    else:
        world = tyles.World(20, 50, tyle_type=tyles.WorldTyle)
        world.GenerateWorld(lands_to_generate=95)


if __name__ == "__main__":
    main()
