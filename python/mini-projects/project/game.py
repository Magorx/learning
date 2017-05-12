#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import tyles
from tkinter import *
from PIL import Image, ImageTk
from random import randint, choice


WORLD_WIDTH = 10
WORLD_HEIGHT = 10

SIDE_PX = 50
ERROR = -1
ERROR_BAD_BINDING_ARGS = -2


root = Tk()
root.config(width=WORLD_WIDTH * SIDE_PX,
            height=WORLD_HEIGHT * SIDE_PX)
root.protocol("WM_DELETE_WINDOW", exit)


TEXTURES = {
        'road' : ImageTk.PhotoImage(Image.open('./textures/road.png')),
        'water' : ImageTk.PhotoImage(Image.open('./textures/water.png')),
        'mountain' : ImageTk.PhotoImage(Image.open('./textures/mountain.png')),
        'tree' : ImageTk.PhotoImage(Image.open('./textures/tree.png')),
        'chosen_corner' : ImageTk.PhotoImage(Image.open('./textures/chosen_corner.png')),
        'men' : ImageTk.PhotoImage(Image.open('./textures/men.png'))
}


def coord_range(x1, y1, x2, y2):
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
        self.spd = 2

    def select(self):
        self.select = True
        for x in range(max(self.x - 2, 0), min(self.x + 2, self.place.width)):
            for y in range(max(self.y - 2, 0), min(self.y + 2, self.place.height)):
                tyle = self.place.map[x][y]
                if coord_range(self.x, self.y, x, y) <= self.spd:
                    tyle.add_texture(texture_name='chosen_corner')


class Clickable_tyle(tyles.TkWorldTyle):
    def __init__(self, world, canvas, x=0, y=0, symb='.'):
        tyles.TkWorldTyle.__init__(self, world, canvas, x, y, symb)
        self.creature = None
    
    def click_handler(self, event):
        if self.creature is None:
            self.set_creature(Creature(world, 'Cr', x=self.x, y=self.y))
        else:
            self.creature.select()
    def set_creature(self, creature):
        self.creature = creature

    def bind(self, button, action):
        try:
            self.canvas.bind(button, action)
            return 0
        except:
            return ERROR_BAD_BINDING_ARGS


def main():
    global world
    world = tyles.TkWorld(10, 10, pre_generated=True, tyle_type=Clickable_tyle,
                          window=root, textures=TEXTURES)
    world.root_window.mainloop()


if __name__ == "__main__":
    main()
