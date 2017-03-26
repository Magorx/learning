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

main_root = Tk()
main_root.title('main_root')
main_root.config(width=WORLD_WIDTH * SIDE_PX, height=WORLD_HEIGHT * SIDE_PX)
main_root.protocol("WM_DELETE_WINDOW", exit)

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
    def __init__(self, canvas, world, prev_tyle=None):
        if prev_tyle is None:
            prev_tyle = tyles.WorldTyle()

        self.x = prev_tyle.x
        self.y = prev_tyle.y
        self.symb = prev_tyle.symb
        self.full = prev_tyle.full
        self.canvas = canvas
        self.info_window = None

    def choose_texture_name(self):
        symb = self.symb
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
            return ERROR

        return 0

    def set_texture(self):
        try:
            self.texture = TEXTURES[self.texture_name]
        except:
            print('! == [ERR][tyle] wrong texture name -> \
                  call self.choose_texture_name')

            if self.choose_texture_name() == ERROR:
                print('! == [ERR][tyle] failed calling\
                      self.choose_texture_name')
                return ERROR
            else:
                self.texture = TEXTURES[self.texture_name]

        return 0

    def set_image(self, image=None):
        self.delete_image()

        if image is not None:
            try:
                self.image = self.canvas.create_image(0, 0, anchor='nw',
                                                      image=image)
            except:
                print('! == [ERR][tyle] failed setting input image')
                return ERROR
            return 0

        try:
            self.image = self.canvas.create_image(0, 0, anchor='nw',
                                              image=self.texture)
        except:
            print('! == [ERR][tyle] wrong texture -> call self.set_texture')
            if self.set_texture() == ERROR:
                print('! == [ERR][tyle] failed calling self.set_texture')
            else:
                self.image = self.canvas.create_image(0, 0, anchor='nw',
                                                      image=self.texture)
        return 0

    def delete_image(self):
        try:
            self.image.delete()
        except:
            return ERROR
        return 0

    def update(self):
        self.choose_texture_name()
        self.set_texture()
        if self.set_image() == ERROR:
            print('! == [ERR][tyle] failed updating')
            return ERROR

        return 0

    def select(self, event):
        print('[SELECTION][tyle]', self.symb, self.x, self.y)
        self.delete_image()

        self.texture = ImageTk.PhotoImage(
            Image.alpha_composite(PIL_IMAGES[self.texture_name],
                                  PIL_IMAGES['chosen_corner']))
        self.image = self.canvas.create_image(0, 0, anchor='nw', 
                                              image=self.texture)

        self.info_window = Tk()
        info_window = self.info_window
        info_window.title('INFO')
        info_window.protocol("WM_DELETE_WINDOW", self.deselect)

        ent = Text(info_window, width=3, height=1, font=20)
        ent.pack()
        Label(info_window, text=(' x:' + str(self.x) + 
                                 ' y:' + str(self.y))).pack()
        Label(info_window, text='T - tree').pack()
        Label(info_window, text='~ - water').pack()
        Label(info_window, text='^ - mountain').pack()
        Label(info_window, text='Enter to update').pack()

        def update(event):
            self.symb = ent.get(1.0, END)[0]
            self.update()
            self.deselect()

        info_window.bind('<Return>', update)
        info_window.focus()
        ent.focus()
        info_window.mainloop()

    def deselect(self):
        try:
            self.info_window.destroy()
        except:
            pass

        self.update()




class MyWorld(tyles.World):
    def __init__(self,
                 prev_world=None,
                 side_px=SIDE_PX,
                 pre_generated=False):
        if prev_world is None or pre_generated:
            prev_world = tyles.World(WORLD_WIDTH,
                                           WORLD_HEIGHT)
        if pre_generated:
            prev_world.GenerateWorld()

        self.common_symb = prev_world.common_symb
        self.time = prev_world.time
        self.width = prev_world.width
        self.height = prev_world.height
        self.square = self.width * self.height
        self.a = prev_world.a
        self.map = [[0 for i in range(self.height)] for j in range(self.width)]

        self.root_window = main_root
        for x in range(self.width):
            for y in range(self.height):
                self.map[x][y] = MyWorldTyle(
                    Canvas(self.root_window,
                           width=side_px, height=side_px,
                           bg='#FFFFFF'),
                    self,
                    prev_world.map[x][y])
        
        for x in range(self.width):
            for y in range(self.height):
                self.map[x][y].canvas.bind('<Button-1>', self.map[x][y].select)
                self.map[x][y].canvas.place(x=x*side_px, y=y*side_px)

    def full_update(self):
        for x in range(self.width):
            for y in range(self.height):
                self.map[x][y].update()


def main():
    global world
    MODE = True
    if MODE:
        world = MyWorld()
        world.full_update()
        world.GenerateWorld(lands_to_generate=100)
        world.full_update()
        world.root_window.mainloop()
    else:
        world = tyles.World(20, 50, tyle_type=tyles.WorldTyle)
        world.GenerateWorld(lands_to_generate=95)


if __name__ == "__main__":
    main()
