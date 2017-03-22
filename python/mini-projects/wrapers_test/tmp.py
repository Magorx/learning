#!/usr/bin/env python3
# -*- coding: utf-8 -*-

'''from tkinter import *
from random import randint, choice
from time import sleep

def foo(event):
    x, y = randint(0, X - 1), randint(0, Y - 1)
    arr[x][y].create_image(SIDE // 2, SIDE // 2, image=choice([bulb, tree]))


root = Tk()

HEIGHT = 500
WIDTH = 500
canvas = Canvas(root, width=WIDTH, height=HEIGHT, bg='#FF0000')
canvas.pack()
b = Button(root, text='HIIIIIIIII')
b.bind('<Button-1>', foo)
b.pack()

bulb = PhotoImage(file="bulb.png")
tree = PhotoImage(file="tree.png")

SIDE = 50
X = WIDTH // SIDE
Y = HEIGHT // SIDE
print(X, Y)

arr = [[0 for i in range(X)] for j in range(Y)]
for i in range(Y):
    for j in range(X):
        new_canv = Canvas(canvas, width=SIDE, height=SIDE)
        new_canv.grid(row=i, column=j)
        new_canv.create_image(SIDE // 2, SIDE // 2, image=choice([bulb, tree]))
        arr[i][j] = new_canv
        
mainloop()

for i in range(1000):
    sleep(0.1)
    x, y = randint(0, X - 1), randint(0, Y - 1)
    arr[x][y].create_image(SIDE // 2, SIDE // 2, image=choice([bulb, tree]))

#canvas.create_rectangle((x1, y1), (x2, y2))\
'''

import tyles
from tkinter import *
from PIL import Image, ImageTk

main_root = Tk()

TEXTURES = {
    'road' : ImageTk.PhotoImage(Image.open('road.png')),
    'water' : ImageTk.PhotoImage(Image.open('water.png')),
    'mountain' : ImageTk.PhotoImage(Image.open('mountain.png')),
    'tree' : ImageTk.PhotoImage(Image.open('tree.png'))
}

class MyWorldTyle(tyles.WorldTyle):
    def __init__(self, canvas, prev_tyle=None):
        if prev_tyle is None:
            prev_tyle = tyles.WorldTyle()

        self.symb = prev_tyle.symb
        self.full = prev_tyle.full
        self.canvas = canvas

    def update(self):
        symb = self.symb
        if symb == '^':
            self.texture = TEXTURES['mountain']
        elif symb == 'T':
            self.texture = TEXTURES['tree']
        elif symb == '~':
            self.texture = TEXTURES['water']
        elif symb == '.':
            self.texture = TEXTURES['road']
        else:
            self.name = 'ERROR'
            self.symb = 'ERROR'
            return ERROR

        self.canvas.create_image(25, 25, image=self.texture)

STANDART_WORLD_WIDTH = 15
STANDART_WORLD_HEIGHT = 15

class MyWorld(tyles.World):
    def __init__(self, prev_world_class=None, side_px=50, pre_generated=False):
        if prev_world_class is None or pre_generated:
            prev_world_class = tyles.World(STANDART_WORLD_WIDTH, STANDART_WORLD_HEIGHT)
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
                self.map[x][y].canvas.grid(row=x, column=y)

    def full_update(self):
        for x in range(self.width):
            for y in range(self.height):
                self.map[x][y].update()


def main():
    global world
    MODE = True # Change this to see some magic <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    if MODE:
        world = MyWorld()
        #world.full_update()
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
