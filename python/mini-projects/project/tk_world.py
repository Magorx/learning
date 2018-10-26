#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import tkinter
root = tkinter.Tk()

import world
import info_window
import textures

import random
import time


STANDART_SYMB_TEXTURE_DICT = {'.' : 'road',
                              '~' : 'water',
                              'T' : 'tree',
                              '^' : 'mountain',
                              '@' : 'unit',
                              'error' : 'error'}

STANDART_TEXTURE_PACK = {
    'road' : textures.road,
    'water' : textures.water,
    'mountain' : textures.mountain,
    'tree' : textures.tree,
    'chosen_corner' : textures.chosen_corner,
    'error' : textures.error}

SIDE_PX = 50
ERROR = -1
ERROR_TEXTURE_NOT_EXIST = -2


class TkWorldTyle(world.WorldTyle):
    def __init__(self, world, canvas, x=0, y=0, symb='.'):
        super(TkWorldTyle, self).__init__(world, x, y, symb=symb)
        self.canvas = canvas
        self.textures = []
        self.textures_names = []
        self.images = []

    def insert_texture(self, pos, texture=None, texture_name=None,
                       redraw=True):
        if texture_name is None:
            texture_name = 'error'
        if texture is None:
            texture = self.world.textures[texture_name]

        self.textures.insert(pos, texture)
        self.textures_names.insert(pos, texture_name)

        if redraw:
            self.redraw()

    def add_texture(self, texture=None, texture_name=None, redraw=True):
        self.insert_texture(len(self.textures), texture, texture_name, redraw)

    def delete_texture(self, pos):
        try:
            del self.textures[pos]
            del self.textures_names[pos]
            self.canvas.delete(self.images[pos])
            del self.images[pos]
        except Exception:
            print('ERROR DELETING TEXTURE')
            return ERROR

    def delete_texture_by_name(self, name):
        for i in range(len(self.textures_names)):
            if name == self.textures_names[i]:
                self.delete_texture(i)
                return
        return ERROR

    def delete_top_texture(self):
        self.delete_texture(len(self.textures) - 1)

    def redraw(self):
        self.clear_images()
        if not self.textures and self.textures_names:
            for name in self.textures_names:
                try:
                    self.textures.append(self.world.textures[name])
                except:
                    self.textures.append(self.world.textures['error'])

        for texture in self.textures:
            self.images.append(self.canvas.create_image(self.world.side_px//2,
                                                        self.world.side_px//2,
                                                        anchor=tkinter.CENTER, 
                                                        image=texture))

    def _texture_name_by_symb(self, symb,
                              symb_texture_dict=STANDART_SYMB_TEXTURE_DICT):
        d = symb_texture_dict
        if symb in d:
            return d[symb]
        else:
            return 'error'

    def texture_by_symb(self, symb,
                        symb_texture_dict=STANDART_SYMB_TEXTURE_DICT):
        texture_name = self._texture_name_by_symb(symb, symb_texture_dict)
        if texture_name not in self.world.textures:
            return self.world.textures['error']
        else:
            return self.world.textures[texture_name]

    def add_texture_by_symb(self, symb,
                           symb_texture_dict=STANDART_SYMB_TEXTURE_DICT):
        self.add_texture(self.texture_by_symb(symb),
                         self._texture_name_by_symb(symb))

    def clear_images(self):
        for i in range(len(self.images)):
            try:
                self.canvas.delete(self.images[i])
            except:
                return ERROR
        self.images = []

    def update(self, to_set_texture_by_symb=True):
        if to_set_texture_by_symb or not self.textures:
            self.clear_images()
            self.add_texture_by_symb(self.symb)
        self.redraw()

    def clicked(self, event):
        self.world.clicked()
        pass # You should use your own, if need


class TkTyleInfo(object):
    def __init__(self, tyle, canvas):
        self.tyle = tyle
        self.canvas = canvas
        self.infos = {}

    def add_info_text(self, x, y, text, mark='', anchor=tkinter.CENTER,
                      color='black'):
        if not mark:
            mark = text
        if mark in self.infos:
            self.canvas.delete(self.infos[mark])

        self.infos[mark] = self.canvas.create_text(x, y, font=20,
                                                   text=text, anchor=anchor,
                                                   fill=color)
        return 0

    def delete_info(self, mark):
        if mark in self.infos:
            self.canvas.delete(self.infos[mark])
        return 0


class TkWorld(world.World):
    def __init__(self,
                 width, height, 
                 tyle_type=TkWorldTyle, 
                 common_symb=world.STANDART_COMMON_SYMB,
                 side_px=SIDE_PX,
                 pre_generated=False,
                 window=None,
                 textures=None):
        super(TkWorld, self).__init__(width, height, tyle_type=tyle_type, common_symb=common_symb)
        self.side_px = side_px

        if pre_generated:
            self.GenerateWorld()

        if window is None:
            window = root
        window.config(width=self.width * SIDE_PX,
                      height=self.height * SIDE_PX)
        window.protocol("WM_DELETE_WINDOW", exit)

        if textures is None:
            textures = STANDART_TEXTURE_PACK

        self.root_window = window
        self.textures = textures

        for x in range(self.width):
            for y in range(self.height):
                prev_tyle = self.map[x][y]
                self.map[x][y] = tyle_type(
                    self,
                    tkinter.Canvas(self.root_window,
                                   width=side_px, height=side_px, 
                                   bg='#FFFFFF'),
                x, y, prev_tyle.symb)
        
        for x in range(self.width):
            for y in range(self.height):
                tyle = self.map[x][y]
                tyle.canvas.place(x=x*side_px, y=y*side_px)
                tyle.canvas.bind('<Button-1>', self.map[x][y].clicked)
                tyle.canvas.bind('<Button-2>', self.map[x][y].clicked)
                tyle.canvas.bind('<Button-3>', self.map[x][y].clicked)
                tyle.add_texture(tyle.texture_by_symb(tyle.symb), tyle._texture_name_by_symb(tyle.symb))

    def full_update(self, to_set_texture_by_symb=True):
        for x in range(self.width):
            for y in range(self.height):
                self.map[x][y].update(to_set_texture_by_symb=to_set_texture_by_symb)

    def clicked():
        pass # You should use your own, if need

    def LoadTheWorld(self, file_name):
        super(TkWorld, self).LoadTheWorld(file_name)


def main():
    world = TkWorld(10, 10, window=root)
    world.GenerateWorld(lands_to_generate=100, defined_land_square=20)
    world.full_update(to_set_texture_by_symb=True)
    world.root_window.mainloop()


if __name__ == "__main__":
    main()
