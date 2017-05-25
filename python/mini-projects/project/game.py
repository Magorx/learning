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
        self.speed = 2
        self.texture = texture

    def select(self):
        self.selected = True
        for x in range(max(self.x - 2, 0), min(self.x + 3, self.place.width)):
            for y in range(max(self.y - 2, 0), min(self.y + 3, self.place.height)):
                tyle = self.place.map[x][y]
                if coord_range(self.x, self.y, x, y) <= self.speed:
                    if tyle.creature_could_move is None:
                        tyle.creature_moving(self)

    def move(self, x, y):
        from_tyle = self.place.map[self.x][self.y]
        to_tyle = self.place.map[x][y]
        if to_tyle.creature is not None:
            return 0

        from_tyle.delete_texture(from_tyle.textures.index(self.texture))
        from_tyle.creature = None

        to_tyle.set_creature(self)

        self.x = x
        self.y = y


class Clickable_tyle(tyles.TkWorldTyle):
    def __init__(self, world, canvas, x=0, y=0, symb='.'):
        tyles.TkWorldTyle.__init__(self, world, canvas, x, y, symb)
        self.creature = None
        self.creature_could_move = None
        self.click_handler = self.handler_default

    def handler_default(self, event):
        if self.creature is None:
            self.set_creature(Creature(world, 'Cr', x=self.x, y=self.y))
        else:
            self.creature.select()

    def set_click_handler(self, handler):
        if handler == 'default':
            self.click_handler = self.handler_default
        if handler == 'creature_moved':
            self.click_handler = self.handler_creature_moved

        self.canvas.bind('<Button-1>', self.click_handler)

    def handler_creature_moved(self, event):
        cr = self.creature_could_move
        for x in range(max(cr.x - 2, 0), min(cr.x + 3, cr.place.width)):
            for y in range(max(cr.y - 2, 0), min(cr.y + 3, cr.place.height)):
                tyle = cr.place.map[x][y]
                if coord_range(cr.x, cr.y, x, y) <= cr.speed:
                    if tyle.creature_could_move == cr:
                        tyle.set_click_handler('default')
                        tyle.remove_texture()
                        tyle.creature_could_move = None
        cr.move(self.x, self.y)

    def creature_moving(self, creature):
        if self.creature_could_move is not None:
            return 0
        self.creature_could_move = creature
        self.add_texture(texture_name='chosen_corner')
        self.set_click_handler('creature_moved')

    def set_creature(self, creature):
        self.creature = creature
        self.add_texture(creature.texture)
        self.creature_could_move = None

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
