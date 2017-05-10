#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import tyles
from tkinter import *
from PIL import Image, ImageTk
from random import randint, choice


class Clickable_tyle(tyles.TkWorldTyle):
    def __init__(self, world, canvas, x=0, y=0, symb='.', prev_tyle=None):
        super(Clickable_tyle, self).__init__(world, canvas, x, y, symb, prev_tyle)
    
    def select(self, event):
        print('[SELECTION][tyle]', self.symb, self.x, self.y)
        self.delete_image()

        self.texture = ImageTk.PhotoImage(
            Image.alpha_composite(PIL_IMAGES[self.texture_name],
                                  PIL_IMAGES['chosen_corner']))
        self.texture = choice([TEXTURES['men'], TEXTURES['water']])
        self.image = self.canvas.create_image(0, 0, anchor='nw', 
                                              image=self.texture)


def main():
    world = tyles.TkWorld(10, 10, pre_generated=True, tyle_type=Clickable_tyle)
    world.full_update(to_bind=True)
    global TEXTURES, PIL_IMAGES
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
    world.root_window.mainloop()


if __name__ == "__main__":
    main()
