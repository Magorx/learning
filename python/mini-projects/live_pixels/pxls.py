#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from time import sleep
from random import randint, random, choice, shuffle
from math import sqrt
import tkinter as tk


COLOR_SYMBS = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F']


# OPTIONS - OPTIONS - OPTIONS - OPTIONS - OPTIONS - OPTIONS - OPTIONS - OPTIONS

# VISUALS AND PRODUCTIVITY
FULL_SCREEN_MODE = True # withoout this window will be opened with some strange
                        # set of params

PIXEL_SIZE = 40 # make this bigger if having lags
TICKS_PER_SECOND = 30 # make this lower if having lags
                      # and keep balance ^

#BATTLE MODES
BASIC = 1 # chance of winning in each pixel's attack is 50%

STABLE_TECH_BASED = 2 # chances are based on TECH, that becomes bigger if
                      # civilization is dying and becomes less, while not
                      # !WARNING! this option leads to endless game

UNSTABLE_TECH_BASED = 3 # chances are based on TECH and strange formula
                        # (check choice_for_two). Idk how everything works here

BATTLE_MODE = 2 # choose battle mode, stable_tech recommended

# OPTIONS - OPTIONS - OPTIONS - OPTIONS - OPTIONS - OPTIONS - OPTIONS - OPTIONS


def randstr(length, lvl=3):
    s = ""
    for i in range(length):
        roll = randint(1, lvl)
        if roll == 1:
            c = chr(randint(48, 57))
        elif roll == 2:
            c = chr(randint(65, 90))
        elif roll == 3:
            c = chr(randint(97, 122))
        elif roll == 4:
            c = choice(SYMBS)
        s = s + c
    return s


def randstrchoice(length, chars):
    s = []
    for i in range(length):
        s.append(choice(chars))
    return ''.join(s)


def randcolor():
    return '#' + randstrchoice(6, COLOR_SYMBS)


def weighted_choice(arr, weihts):
    cur_s = 0
    rand = randint(1, sum(weihts))
    for i in range(len(arr)):
        cur_s += weihts[i]
        if cur_s >= rand:
            return arr[i]


def choice_for_two(fist, second, first_w=1, second_w=1):
    arr = [first, second]
    if second_w > first_w:
        arr.reverse()

    coef_of_magicity = 2
    rand = random()
    delta = first_w - second_w
    edge = 1 / (1 + sqrt(abs(delta)) * coef_of_magicity)
    
    return arr[int(rand > edge)]


def stop_programm():
    exit(0)


SHIFTS = [[1, 0], [0, 1], [-1, 0], [0, -1]]


class Pixel():
    def __init__(self, world, x, y, owner):
        self.world = world
        self.x = x
        self.y = y
        self.owner = owner
        self.delayed_change = self.owner

        self.active = True
        self.rect = self.world.canvas.create_rectangle(x * PIXEL_SIZE, y * PIXEL_SIZE, x * PIXEL_SIZE + PIXEL_SIZE, y * PIXEL_SIZE + PIXEL_SIZE, fill=self.owner.color)

    def tick(self):
        if not self.active:
            return
        
        shifts = SHIFTS[:]
        shuffle(shifts)
        if self.owner.main_direction:
            shifts = [SHIFTS[self.owner.main_direction]] + shifts
        for i in range(len(shifts)):
            dx, dy = shifts[i]
            nx = (self.x + dx) % self.world.width
            ny = (self.y + dy) % self.world.height # new_x new_y
            if self.attack(self.world.field[nx][ny]):
                return
        self.active = False

    def attack(self, other):
        if self.owner == other.owner:
            return False

        if BATTLE_MODE == BASIC:
            winner = choice([self, other])
        elif BATTLE_MODE == STABLE_TECH_BASED:
            winner = weighted_choice([self, other], [self.owner.tech_level, other.owner.tech_level])
        elif BATTLE_MODE == UNSTABLE_TECH_BASED:
            winner = choice_for_two(self, other, self.owner.tech_level, other.owner.tech_level)

        if self is winner:
            other.delayed_change = self.owner
        else:
            pass
        return True

    def change_owner(self, new_owner):
        del self.owner.pixels[self.owner.pixels.index(self)]
        self.owner = new_owner
        new_owner.pixels.append(self)
        self.world.canvas.itemconfig(self.rect, fill=self.owner.color)
        self.neighbours_to_active()

    def neighbours_to_active(self):
        for i in range(len(SHIFTS)):
            dx, dy = SHIFTS[i]
            nx = (self.x + dx) % self.world.width
            ny = (self.y + dy) % self.world.height
            self.world.field[nx][ny].active = True

class World():
    def __init__(self, width, height, civ_number, livetime=60, tps=10, fullscreen=False, shuffle_time=100000, main_dirs=False):
        self.root = tk.Tk()
        root = self.root
        if fullscreen:
            w = root.winfo_screenwidth()
            h = root.winfo_screenheight()
            pxl_in_width = w // PIXEL_SIZE
            pxl_in_height = h // PIXEL_SIZE
            width = pxl_in_width
            height = pxl_in_height
            tmp = 10000 // (width * height)
            livetime = livetime * 10
            shuffle_time = 15
        self.canvas = tk.Canvas(root, width=width*PIXEL_SIZE, height=height*PIXEL_SIZE)
        self.canvas.pack()

        self.width = width
        self.height = height
        self.square = width * height
        self.livetime = livetime
        self.tps = tps
        self.fullscreen = fullscreen
        self.shuffle_time = shuffle_time * tps
        self.shuffle_cnt = 0

        self.civ_number = civ_number
        self.civs = [Civilization(self, randcolor(), id=i, main_direction=-1 if main_dirs else None) for i in range(civ_number)]

        root.title('PXLS')
        self.screen_width = root.winfo_screenwidth()
        self.screen_height = root.winfo_screenheight()
        self.window_width = self.width * PIXEL_SIZE
        self.window_height = self.height * PIXEL_SIZE
        self.window_standard_x = (self.screen_width - self.window_width) // 2
        self.window_standard_y = (self.screen_height - self.window_height) // 2
        root.geometry('{}x{}+{}+{}'.format(self.window_width, self.window_height, 
                                             self.window_standard_x, self.window_standard_y))
        root.protocol("WM_DELETE_WINDOW", exit)

        self.field = [[None for i in range(height)] for j in range(width)]

        for x in range(width):
            for y in range(height):
                civ = choice(self.civs)
                self.field[x][y] = Pixel(self, x, y, civ)
                civ.pixels.append(self.field[x][y])

    def print_score(self):
        for civ in self.civs:
            print('[{}] popul: {} | max_popul {} | tech_lvl {} | max_tech: {}'.format(civ.name, civ.popul(), civ.max_popul, civ.tech_level, civ.max_tech_level))

    def start(self):
        self.root.after(1000 // self.tps, self.tick)
        self.root.mainloop()

    def mainloop(self):
        for i in range(100):
            sleep(1)
            print('Clck')
            self.tick()

    def tick(self):
        self.shuffle_cnt += 1
        if self.shuffle_cnt % self.shuffle_time == 0:
            for civ in self.civs:
                civ.color = randcolor()

        arr = [i for i in range(self.square)]
        shuffle(arr)
        for i in range(self.square):
            x = arr[i] % self.width
            y = arr[i] // self.width
            self.field[x][y].tick()

        for x in range(self.width):
            for y in range(self.height):
                pxl = self.field[x][y]
                pxl.change_owner(pxl.delayed_change)

        max_popul = 0
        for civ in self.civs:
            max_popul = max(max_popul, civ.popul())

        for civ in self.civs:
            if civ.popul() < max_popul // 3:
                civ.tech_level += 1
            elif civ.popul() > max_popul // 1.5:
                civ.tech_level = max(civ.tech_level - 1, 1) 
            if civ.popul() == max_popul and civ.popul() > self.square // 2:
                self.civs.append(Civilization(self, randcolor(), tech_level=civ.tech_level+2, id=len(self.civs)))
                choice(civ.pixels).change_owner(self.civs[-1])

            civ.update_statistic()
        self.root.after(1000 // self.tps, self.tick)


class Civilization():
    def __init__(self, world, color, name=None, tech_level=1, id=-1, main_direction=None):
        if name is None:
            name = randstr(randint(3, 8))
        if main_direction == -1:
            main_direction = randint(0, 3)

        self.world = world
        self.color = color
        self.name = name
        self.tech_level = tech_level
        self.id = id
        self.pixels = []
        self.main_direction = main_direction

        self.max_tech_level = 1
        self.max_popul = 1

    def update_statistic(self):
        self.max_tech_level = max(self.tech_level, self.max_tech_level)
        self.max_popul = max(len(self.pixels), self.max_popul)

    def popul(self):
        return len(self.pixels)


def main():
    w = World(30, 30, 10, livetime=300, tps=TICKS_PER_SECOND, fullscreen=FULL_SCREEN_MODE)
    # yo man ud better go to options, check top of this file
    w.start()


if __name__ == "__main__":
    main()
