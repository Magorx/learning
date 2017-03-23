#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import tyles
from tkinter import *
from PIL import Image, ImageTk

WORLD_WIDTH = 15
WORLD_HEIGHT = 15
SIDE_PX = 50

main_root = Tk()
main_root.title('main_root')
main_root.config(width=WORLD_WIDTH * SIDE_PX, height=WORLD_HEIGHT * SIDE_PX)

TEXTURES = {
    'road' : ImageTk.PhotoImage(Image.open('road.png')),
    'water' : ImageTk.PhotoImage(Image.open('water.png')),
    'mountain' : ImageTk.PhotoImage(Image.open('mountain.png')),
    'tree' : ImageTk.PhotoImage(Image.open('tree.png')),
    'chosen_corner' : ImageTk.PhotoImage(Image.open('chosen_corner.png'))
}

PIL_IMAGES = {
    'road' : Image.open('road.png'),
    'water' : Image.open('water.png'),
    'mountain' : Image.open('mountain.png'),
    'tree' : Image.open('tree.png'),
    'chosen_corner' : Image.open('chosen_corner.png')
}

class MyWorldTyle(tyles.WorldTyle):
    def __init__(self, canvas, prev_tyle=None):
        if prev_tyle is None:
            prev_tyle = tyles.WorldTyle()

        self.x = prev_tyle.x
        self.y = prev_tyle.y
        self.symb = prev_tyle.symb
        self.full = prev_tyle.full
        self.canvas = canvas

    def update(self):
        symb = self.symb
        try:
            self.image.delete()
        except:
            pass
        if symb == '^':
            self.texture_name = 'mountain'
        elif symb == 'T':
            self.texture_name = 'tree'
        elif symb == '~':
            self.texture_name = 'water'
        elif symb == '.':
            self.texture_name = 'road'
        else:
            self.name = 'ERROR'
            self.symb = 'ERROR'
            return ERROR

        self.texture = TEXTURES[self.texture_name]
        self.image = self.canvas.create_image(0, 0, anchor='nw', image=self.texture)

    def chosen(self, event):
        print(self.symb, self.x, self.y, 'chosen')
        try:
            self.image.delete()
        except:
            pass
        self.texture = ImageTk.PhotoImage(Image.alpha_composite(PIL_IMAGES[self.texture_name], PIL_IMAGES['chosen_corner']))
        self.image = self.canvas.create_image(0, 0, anchor='nw', image=self.texture)



class MyWorld(tyles.World):
    def __init__(self,
                 prev_world_class=None,
                 side_px=SIDE_PX,
                 pre_generated=False):
        if prev_world_class is None or pre_generated:
            prev_world_class = tyles.World(WORLD_WIDTH,
                                           WORLD_HEIGHT)
        if pre_generated:
            prev_world_class.GenerateWorld()

        self.common_symb = prev_world_class.common_symb
        self.time = prev_world_class.time
        self.width = prev_world_class.width
        self.height = prev_world_class.height
        self.square = self.width * self.height
        self.map = [[0 for i in range(self.height)] for j in range(self.width)]

        self.root_window = main_root
        for x in range(self.width):
            for y in range(self.height):
                self.map[x][y] = MyWorldTyle(
                    Canvas(self.root_window,
                           width=side_px, height=side_px,
                           bg='#FFFFFF'),
                    prev_world_class.map[x][y])
        
        for x in range(self.width):
            for y in range(self.height):
                self.map[x][y].canvas.bind('<Button-1>', self.map[x][y].chosen)
                self.map[x][y].canvas.place(x=x*side_px, y=y*side_px)

    def full_update(self):
        for x in range(self.width):
            for y in range(self.height):
                self.map[x][y].update()


def main():
    global world
    MODE = True # Change this to see some magic <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    if MODE:
        world = MyWorld()
        world.full_update()
        world.GenerateWorld(lands_to_generate=100) # delete this parameter to 
                                                  # see absolute power(random)
        world.full_update()
        world.print()
        world.root_window.mainloop()
    else:
        world = tyles.World(20, 50, tyle_type=tyles.WorldTyle)
        world.GenerateWorld(lands_to_generate=95)


if __name__ == "__main__":
    main()
