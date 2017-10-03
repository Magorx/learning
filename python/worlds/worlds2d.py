#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import random
import time
import tkinter
from PIL import Image, ImageTk

ERR_INVALID_COORDS = -100
ERR_ARGS = -99

STANDART_WORLD_WIDTH = 15
STANDART_WORLD_HEIGHT = 15
STANDART_SYMB_TEXTURE_DICT = {'.' : 'road',
                              '~' : 'water',
                              'T' : 'tree',
                              '^' : 'mountain',
                              '@' : 'men',
                              'error' : 'error'}
DIRS = {'up': (-1, 0), 'down': (1, 0), 'left': (0, -1), 'right': (0, 1)}
BUTTON_TO_COMMAND_DICT = {'w': 'move up',
                          'a': 'move left',
                          's': 'move down',
                          'd': 'move right',
                          'f': 'attack',
                          ' ': ''}

SIDE_PX = 50
ERROR = -1
ERROR_TEXTURE_NOT_EXIST = -2


class Tyle(object):
    def __init__(self, symb='.'):
        self.symb = symb
    
    def __repr__(self):
        return self.symb


class WorldTyle(Tyle):
    def __init__(self, world, x, y, type='solid', symb='.'):
        self.world = world
        self.x = x
        self.y = y
        self.default_symb = symb
        self.full = False
        self.creature = None

    @property
    def symb(self):
        if self.creature:
            return self.creature.symb
        else:
            return self.default_symb

    @symb.setter
    def symb(self, symb):
        self.default_symb = symb


class World(object):
    def __init__(self, width, height, tyle_type=WorldTyle, common_symb='.',
                 landshafts=None, lands_to_generate=90, is_tor=False):
        self.map = [[tyle_type(self, j, i, symb=common_symb) for i in range (height)]
                    for j in range(width)]
        self.common_symb = common_symb
        self.time = 0
        self.width = width
        self.height = height
        self.square = width * height
        self.is_tor = is_tor
        self.to_handle = []
        self.landshafts = landshafts
        self.lands_to_generate = lands_to_generate

    def print(self, clear_screan=True):
        if clear_screan:
            print('\n'*19)
        for x in range(self.width):
            for y in range(self.height):
                print(self.map[x][y], end='')
            print()

    def GenerateLandshaft(self, square, symb, start_x, start_y,
                          forbiden=[], replacements=[-1, 1],
                          to_update=False, delay_between_updates=0):
        if (start_x < 0 or start_y < 0 or
           start_x >= self.width or start_y >= self.height):
           return ERR_INVALID_COORDS
        if square < 0 or len(replacements) != 2:
            return ERR_ARGS

        width = self.width
        height = self.height
        cur_square = 0
        x = start_x
        y = start_y
        itters = 0

        while cur_square < square:
            itters += 1
            if itters > square * 10:
                break

            if self.map[x][y].symb in forbiden:
                if x == start_x and y == start_y:
                    break
                x = start_x
                y = start_y

            if self.map[x][y].symb == symb:
                rand_int = random.randint(0, replacements[1])
                if replacements[0] > rand_int:
                    self.map[x][y].symb = self.common_symb
                    cur_square -= 1
            else:
                self.map[x][y].symb = symb
                cur_square += 1
                if to_update:
                    self.map[x][y].update()
                    if delay_between_updates:
                        time.sleep(delay_between_updates)
                        self.print()
            x += random.randint(-1, 1)
            y += random.randint(-1, 1)
            if x < 0 or y < 0 or x >= width or y >= height:
                x = start_x
                y = start_y
        return cur_square

    def GenerateWorld(self,
                      lands_to_generate=None, defined_land_square = 0,
                      landshafts=None,
                      to_update=False, delay_between_updates=0):
        if not landshafts:
            if self.landshafts is not None:
                landshafts = self.landshafts
            else:
                landshafts = ['~', '^', 'T']
        if not lands_to_generate:
            if self.lands_to_generate is not None:
                lands_to_generate = self.lands_to_generate
            else:
                lands_to_generate = 90
        self.ClearWorld(to_update=to_update)
        ''' lands_to_generate must be given as percents
            world.square * percents // 100 will be generated'''

        if lands_to_generate < 0:
            lands_to_generate = random.randint(15, 90)
        if lands_to_generate > 100:
            lands_to_generate = 100

        cur_square = 0
        while cur_square < self.square * lands_to_generate // 100:
            if not defined_land_square:
                land_square = \
                    max(random.randint(self.square // 60, self.square // 10),
                        2)
            else:
                land_square = defined_land_square

            start_x = random.randint(0, self.width - 1)
            start_y = random.randint(0, self.height - 1)
            symb = random.choice(landshafts)
            other_symbs = set(landshafts) - {symb}
            generated = self.GenerateLandshaft(land_square, symb, start_x, 
                                               start_y, forbiden=other_symbs, 
                                               to_update=to_update,
                                               delay_between_updates=\
                                               delay_between_updates)
            cur_square += generated
            if cur_square >= self.square * 0.99:
                for x in range(self.width):
                    for y in range(self.height):
                        if self.map[x][y].symb == self.common_symb:
                            self.map[x][y].symb = random.choice(landshafts)
                            if to_update:
                                self.map[x][y].update()
                            cur_square += 1
                break

    def ClearWorld(self, to_update=False):
        for x in range(self.width):
            for y in range(self.height):
                self.map[x][y].symb = self.common_symb
                if to_update:
                    self.map[x][y].update()
            
        return 0


class Creature(object):
    def __init__(self, place, x, y, symb='@', name='cr'):
        if (x < 0 or x >= place.width or
           y < 0 or y >= place.height):
            if place.is_tor:
                x = max(0, x % place.width)
                y = max(0, y % place.height)
            else:
                return ERR_INVALID_COORDS
        self.place = place
        self.x = x
        self.y = y
        self.symb = symb
        self.name = name

        place.map[x][y].creature = self

    def move(self, direction):
        if direction not in DIRS: 
            return 'error'

        place = self.place
        is_tor = place.is_tor
        delta_x, delta_y = DIRS[direction]
        x, y, = self.x, self.y
        new_x, new_y = x + delta_x, y + delta_y
        if (new_x < 0 or new_x >= place.width or
           new_y < 0 or new_y >= place.height):
            if is_tor:
                new_x = max(0, new_x % place.width)
                new_y = max(0, new_y % place.height)
            else:
                return 'Something on the way'

        if place.map[new_x][new_y].full:
            return 'Something on the way'

        place.map[x][y].creature = None
        place.map[new_x][new_y].creature = self
        self.x, self.y = new_x, new_y

    def wait(self):
        pass

    def handle_command(self, command):
        if len(command) == 0:
            return None

        if len(command) == 1:
            if command[0] == 'wait':
                self.wait()

        if len(command) == 2:
            if command[0] == 'move':
                movement_result = self.move(command[1])
                return movement_result


class StandardCreatureButtonInputHandler(object):
    def __init__(self, creature):
        self.creature = creature

    def __call__(self, button):
        if len(button) != 1:
            return None

        if button in BUTTON_TO_COMMAND_DICT:
            command = BUTTON_TO_COMMAND_DICT[button].split()
            self.creature.handle_command(command)
        else:
            return None


class TkWorldTyle(WorldTyle):
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

    def remove_texture(self):
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

    def update(self, to_set_texture_by_symb=False):
        if to_set_texture_by_symb or not self.textures:
            self.clear_images()
            self.add_texture_by_symb()
        self.redraw()

    def click_handler(self, event):
        print('hi')
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


class TkWorld(World):
    def __init__(self, width, height, tyle_type=TkWorldTyle, common_symb='.',
                 side_px=SIDE_PX,
                 pre_generated=False,
                 window=None,
                 textures=None):
        super(TkWorld, self).__init__(width, height, common_symb=common_symb)
        self.side_px = side_px

        if pre_generated:
            self.GenerateWorld()

        if window is None:
            window = tkinter.Tk()
            window.config(width=STANDART_WORLD_WIDTH * SIDE_PX,
                          height=STANDART_WORLD_HEIGHT * SIDE_PX)
            window.protocol("WM_DELETE_WINDOW", exit)

        if textures is None:
            textures = {
                'road' : ImageTk.PhotoImage(Image.open('./textures/road.png')),
                'water' : ImageTk.PhotoImage(Image.open('./textures/water.png')),
                'mountain' : ImageTk.PhotoImage(Image.open('./textures/mountain.png')),
                'tree' : ImageTk.PhotoImage(Image.open('./textures/tree.png')),
                'chosen_corner' : ImageTk.PhotoImage(Image.open('./textures/chosen_corner.png')),
                'error' : ImageTk.PhotoImage(Image.open('./textures/error.png'))
            }

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
                tyle.canvas.bind('<Button-1>', self.map[x][y].click_handler)
                tyle.add_texture(tyle.texture_by_symb(tyle.symb),
                                 tyle._texture_name_by_symb(tyle.symb))

    def click_handler(self):
        pass # You should use your own, if need

    def full_update(self, to_bind=False):
        for x in range(self.width):
            for y in range(self.height):
                self.map[x][y].update()


def main():
    options = {'gen world': ''}
    print('What do you want to do?')
    print(options)
    choice = input()
    if choice not in options:
        print('NOthing like that in options')

    if  choice == 'gen world':
        print('Enter row_count and column_count: ', end='')
        row_count, column_count = list(map(int, input().split()))
        print('Enter common_symb: ', end='')
        common_symb = input()
        print('Enter landshafts: ', end='')
        landshafts = input().split()
        print('Enter how many percents of land to generate: ', end='')
        lands_to_generate = int(input())

        world = World(row_count, column_count, common_symb=common_symb,
                      landshafts=landshafts,
                      lands_to_generate=lands_to_generate)
        world.GenerateWorld(delay_between_updates=1)
        world.print()

if __name__ == "__main__":
    main()

# gen world
# 30 100
# *
# $
# 50
