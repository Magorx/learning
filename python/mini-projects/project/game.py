#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import tyles
from tkinter import *
from PIL import Image, ImageTk
from random import randint, choice


STANDART_WORLD_WIDTH = 5
STANDART_WORLD_HEIGHT = 5

SIDE_PX = 50
ERROR = -1
ERROR_BAD_BINDING_ARGS = -2


root = Tk()
root.config(width=STANDART_WORLD_WIDTH * SIDE_PX,
            height=STANDART_WORLD_HEIGHT * SIDE_PX)
root.protocol("WM_DELETE_WINDOW", exit)


TEXTURES = {
        'road' : ImageTk.PhotoImage(Image.open('./textures/road.png')),
        'water' : ImageTk.PhotoImage(Image.open('./textures/water.png')),
        'mountain' : ImageTk.PhotoImage(Image.open('./textures/mountain.png')),
        'tree' : ImageTk.PhotoImage(Image.open('./textures/tree.png')),
        'chosen_corner' : ImageTk.PhotoImage(Image.open('./textures/chosen_corner.png')),
        'men' : ImageTk.PhotoImage(Image.open('./textures/men.png'))
}

PIL_IMAGES = {
        'road' : Image.open('./textures/road.png'),
        'water' : Image.open('./textures/water.png'),
        'mountain' : Image.open('./textures/mountain.png'),
        'tree' : Image.open('./textures/tree.png'),
        'chosen_corner' : Image.open('./textures/chosen_corner.png'),
        'men' : Image.open('./textures/men.png')
}


def length(x1, y1, x2, y2):
    return abs(x1 - x2) + abs(y1 - y2)


class Creature(object):
    def __init__(self, place, name, atk=1, hp=1, x=0, y=0, texture=TEXTURES['men']):
        self.place = place
        self.name = name
        self.atk = atk
        self.hp = hp
        self.x = x
        self.y = y
        self.selected = False

    def select(self):
        self.select = True


class Clickable_tyle(tyles.TkWorldTyle):
    def __init__(self, world, canvas, x=0, y=0, symb='.', prev_tyle=None):
        tyles.TkWorldTyle.__init__(self, world, canvas, x, y, symb, prev_tyle)
        self.creature = None
        print(self.canvas, x, y)
        self.bind('<Button-1>', exit)
    
    def select(self, event):
        print(self.canvas)
        if randint(0, 1):
            self.add_texture(TEXTURES['men'], 'men')
        else:
            self.add_texture(TEXTURES['water'], 'water')

    def set_creature(self, creature):
        self.creature = creature
        self.a = 0

    def bind(self, button, action):
        try:
            self.canvas.bind(button, action)
        except:
            return ERROR_BAD_BINDING_ARGS


def main():
    world = tyles.TkWorld(10, 10, pre_generated=True, tyle_type=Clickable_tyle,
                          window=root, textures=TEXTURES, pil_images=PIL_IMAGES)
    world.full_update()
    print(world.map[5][5].canvas)

    world.root_window.mainloop()


if __name__ == "__main__":
    main()
