#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from time import sleep
from random import randint, choice, shuffle
import tkinter as tk


PIXEL_SIZE = 20
COLOR_SYMBS = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F']


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

        #self.canvas = tk.Canvas(world.root,
                                #width=PIXEL_SIZE,
                                #height=PIXEL_SIZE,
                                #bg=owner.color)
        #self.canvas.place(x=x*PIXEL_SIZE, y=y*PIXEL_SIZE)
        self.rect = self.world.canvas.create_rectangle(x * PIXEL_SIZE, y * PIXEL_SIZE, x * PIXEL_SIZE + PIXEL_SIZE, y * PIXEL_SIZE + PIXEL_SIZE, fill=self.owner.color)

    def tick(self):
        if not self.active:
            return

        shuffle(SHIFTS)
        for i in range(len(SHIFTS)):
            dx, dy = SHIFTS[i]
            nx = (self.x + dx) % self.world.width
            ny = (self.y + dy) % self.world.height # new_x new_y
            if self.attack(self.world.field[nx][ny]):
                return
        self.active = False

    def attack(self, other):
        if self.owner == other.owner:
            return False

        winner = weighted_choice([self, other], [self.owner.tech_level, other.owner.tech_level])
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
    def __init__(self, width, height, civ_number, livetime=60, tps=10):
        self.width = width
        self.height = height
        self.square = width * height
        self.livetime = livetime
        self.tps = tps
        
        self.civ_number = civ_number
        self.civs = [Civilization(self, randcolor(), id=i) for i in range(civ_number)]

        self.root = tk.Tk()
        root = self.root
        self.canvas = tk.Canvas(root, width=width*PIXEL_SIZE, height=height*PIXEL_SIZE)
        self.canvas.pack()

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
        for i in range(1, self.livetime * self.tps):
            self.root.after(i * 1000 // self.tps, self.tick)
        self.root.after(1000 * self.livetime, self.print_score)
        self.root.after(1000 * (self.livetime + 10), stop_programm)
        self.root.mainloop()

    def mainloop(self):
        for i in range(100):
            sleep(1)
            print('Clck')
            self.tick()

    def tick(self):
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
                self.civs.append(Civilization(self, randcolor(), tech_level=civ.tech_level+1, id=len(self.civs)))
                choice(civ.pixels).change_owner(self.civs[-1])

            civ.update_statistic()


class Civilization():
    def __init__(self, world, color, name=None, tech_level=1, id=-1):
        if name is None:
            name = randstr(randint(3, 8))

        self.world = world
        self.color = color
        self.name = name
        self.tech_level = tech_level
        self.id = id
        self.pixels = []

        self.max_tech_level = 1
        self.max_popul = 1

    def update_statistic(self):
        self.max_tech_level = max(self.tech_level, self.max_tech_level)
        self.max_popul = max(len(self.pixels), self.max_popul)

    def popul(self):
        return len(self.pixels)


def main():
    w = World(30, 30, 10, livetime=300, tps=15)
    w.start()


if __name__ == "__main__":
    main()
