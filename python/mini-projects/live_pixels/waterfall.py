#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from time import sleep
from random import randint, random, choice, shuffle
from math import sqrt
import tkinter as tk


COLOR_SYMBS = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F']


# OPTIONS - OPTIONS - OPTIONS - OPTIONS - OPTIONS - OPTIONS - OPTIONS - OPTIONS

# VISUALS AND PRODUCTIVITY

WIDTH = 30  # width  of created world in macro_pixels
HEIGHT = 20 # height of created world in macro_pixels

FULL_SCREEN_MODE = True # dominate width and height | PIXEL_SIZE IS IMPORTANT

PIXEL_SIZE = 40 # make this bigger if having lags | NOW IS MAGIC NUMBER
TICKS_PER_SECOND = 30 # make this lower if having lags
                      # and keep balance ^

# LIQUIDS
LIQUID_MOBILITY = 50 # the smaller - the faster

DARK_WATER = '#334488'  # generated water will have color in limit from this
LIGHT_WATER = '#3344EE' # to that

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


def color_to_rgb(color):
    r = int(color[1:3], 16)
    g = int(color[3:5], 16)
    b = int(color[5:7], 16)
    return [r, g, b]


def rgb_to_color(rgb):
    r = hex(rgb[0])[2:]
    if len(r) == 1:
        r = '0' + r
    g = hex(rgb[1])[2:]
    if len(g) == 1:
        g = '0' + g
    b = hex(rgb[2])[2:]
    if len(b) == 1:
        b = '0' + b
    return '#' + r + g + b


def color_from_limit(first, second):
    rgb_first = color_to_rgb(first)
    rgb_second = color_to_rgb(second)
    rgb_output = []
    for i in range(3):
        lim_1 = rgb_first[i]
        lim_2 = rgb_second[i]
        if lim_1 > lim_2:
            lim_1, lim_2 = lim_2, lim_1
        rgb_output.append(randint(lim_1, lim_2))
    return rgb_to_color(rgb_output)


def mean_color(first, second):
    rgb_first = color_to_rgb(first)
    rgb_second = color_to_rgb(second)
    rgb_mean = []
    for i in range(3):
        rgb_mean.append((rgb_first[i] + rgb_second[i]) // 2)
    return rgb_to_color(rgb_mean)


def colors_delta(first, second):
    rgb_first = color_to_rgb(first)
    rgb_second = color_to_rgb(second)
    delta = 0
    for i in range(3):
        delta += abs(rgb_first[i] - rgb_second[i])
    return delta


def colors_are_equal(first, second):
    delta = colors_delta(first, second)
    if delta <= 6:
        return True
    else:
        return False


def stop_programm():
    exit(0)


SHIFTS = [[1, 0], [0, 1], [-1, 0], [0, -1]]
SHIFTS_LIQUID_MAIN = [[0, -1], [1, -1], [-1, -1]]
SHIFTS_LIQUID_SIDE = [[1, 0], [-1, 0]]


TYPE_GAS = 0
TYPE_SOLID = 1
TYPE_LIQUID = 2

COLOR_AIR = '#DDDDDD'
COLOR_EARTH = '#835C3B'
COLOR_WATER = '#3B6182'


class Pixel():
    def __init__(self, world, x, y, type=TYPE_GAS, color=COLOR_AIR, color_limits=None):
        self.world = world
        self.x = x
        self.y = y
        self.type = type

        if not color_limits is None:
            color = color_from_limit(color_limits[0], color_limits[1])
        self.color = color
        
        self.used = 0
        self.active = True
        self.world.next_active.append(self)

        self.rect = None
        self.render()

    def tick(self):
        if not self.active or self.world[self.x][self.y] != self:
            return False

        if self.type == TYPE_GAS:
            if colors_delta(self.color, COLOR_AIR) > 255 // 3:
                self.color = mean_color(self.color, COLOR_AIR)
            else:
                self.color = COLOR_AIR
                self.active = False
            self.render()
            if self.active:
                self.world.next_active.append(self)
        elif self.type == TYPE_SOLID:
            self.active = False
        elif self.type == TYPE_LIQUID:
            self.world.next_active.append(self)
            if not randint(0, 1):
                SHIFTS_LIQUID_MAIN[1], SHIFTS_LIQUID_MAIN[2] = SHIFTS_LIQUID_MAIN[2], SHIFTS_LIQUID_MAIN[1] # random to left and right
                shuffle(SHIFTS_LIQUID_SIDE)
            shifts = SHIFTS_LIQUID_MAIN[::]
            if not randint(0, 0):
                shifts += SHIFTS_LIQUID_SIDE

            world = self.world
            x = self.x
            y = self.y
            for shift in shifts:
                dx, dy = shift
                nx, ny = x + dx, y + dy
                if not world.checkxy(nx, ny):
                    continue
                other = world[nx][ny]
                if other.type == TYPE_GAS or (other.type == TYPE_LIQUID and not randint(0, LIQUID_MOBILITY)):
                    if other.type == TYPE_GAS:
                        other.color = self.color
                        other.active = True
                        world.active.append(other)
                    world[x][y] = other
                    world[nx][ny] = self
                    self.x, self.y = nx, ny
                    other.x, other.y = x, y
                    
                    other.render()
                    self.render()
                    break

        #if self.active:
            #self.world.next_active.append(self)

    def render(self):
        if self.rect:
            self.world.canvas.delete(self.rect)

        x = self.x
        y = self.y
        x_pos = self.x * PIXEL_SIZE
        y_pos = (self.world.height - self.y - 1) * PIXEL_SIZE
        self.rect = self.world.canvas.create_rectangle(x_pos, y_pos, x_pos + PIXEL_SIZE, y_pos + PIXEL_SIZE, fill=self.color)

    def __repr__(self):
        return str(self.type)


class World():
    def __init__(self, width, height, livetime=60, tps=10, fullscreen=False):
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
        self.canvas = tk.Canvas(root, width=width*PIXEL_SIZE, height=height*PIXEL_SIZE)
        self.canvas.bind('<Button-1>', self.on_click)
        self.canvas.bind('<Button-3>', self.on_click)
        self.canvas.bind('<B1-Motion>', self.lmb_motion)
        self.canvas.bind('<B3-Motion>', self.rmb_motion)
        self.canvas.bind('<Motion>', self.update_cursor_position)
        self.root.bind('<KeyPress>', self.press_handler)
        self.root.bind('<KeyRelease>', self.release_handler)
        self.root.bind('<ButtonRelease-1>', self.on_release)
        self.canvas.pack()

        self.key_set = set()

        self.width = width
        self.height = height
        self.square = width * height
        self.livetime = livetime
        self.tps = tps
        self.fullscreen = fullscreen

        root.title('WTRFLL')
        self.screen_width = root.winfo_screenwidth()
        self.screen_height = root.winfo_screenheight()
        self.window_width = self.width * PIXEL_SIZE
        self.window_height = self.height * PIXEL_SIZE
        self.window_standard_x = (self.screen_width - self.window_width) // 2
        self.window_standard_y = (self.screen_height - self.window_height) // 2
        root.geometry('{}x{}+{}+{}'.format(self.window_width, self.window_height, 
                                             self.window_standard_x, self.window_standard_y))
        root.protocol("WM_DELETE_WINDOW", exit)

        cursor_position = [-1, -1]

        self.active = []
        self.next_active = []
        self.field = [[Pixel(self, j, i, TYPE_GAS, COLOR_AIR) for i in range(height)] for j in range(width)]

        for i in range(self.width):
            for j in range(self.height):
                if i == 0 or j == 0 or i == self.width - 1 or j == self.height - 1:
                    self.field[i][j] = Pixel(self, i, j, TYPE_SOLID, COLOR_EARTH)
                self.active.append(self[i][j])

        self.on_release(None)

    def __getitem__(self, arg):
        return self.field[arg]

    def update_cursor_position(self, event):
        x, y = event.x, event.y
        self.cursor_position = [x, y]

    def on_click(self, event):
        x = event.x // PIXEL_SIZE
        y = self.height - event.y // PIXEL_SIZE - 1
        if not self.checkxy(x, y):
            return

        if event.num == 1:
            self[x][y] = Pixel(self, x, y, TYPE_LIQUID, color_limits=[DARK_WATER, LIGHT_WATER])
        else:
            self[x][y] = Pixel(self, x, y, TYPE_SOLID, COLOR_EARTH)

    def on_release(self, event):
        r = randint(0 + 50, 255 - 50)
        g = randint(0 + 50, 255 - 50)
        b = randint(0 + 50, 255 - 50)
        self.color_limits = [rgb_to_color([r - 50, b - 50, g - 50]), rgb_to_color([r + 50, b + 50, g + 50])]

    def lmb_motion(self, event):
        event.num = 1
        self.on_click(event)

    def rmb_motion(self, event):
        event.num = 3
        self.on_click(event)

    def press_handler(self, event):
        self.key_set.add(event.char)

    def release_handler(self, event):
        self.key_set.remove(event.char)

    def start(self):
        self.root.after(1000 // self.tps, self.tick)
        self.root.mainloop()

    def tick(self):
        self.next_active = []
        print(len(self.active))
        for pxl in self.active:
            pxl.tick()

        for i in range(self.width):
            for j in range(self.height):
                self[i][j].used = False

        for key in self.key_set:
            if key == ' ':
                x = self.cursor_position[0] // PIXEL_SIZE
                y = self.height - self.cursor_position[1] // PIXEL_SIZE - 1
                self[x][y] = Pixel(self, x, y, TYPE_GAS, COLOR_AIR)

        self.active = self.next_active
        self.root.after(1000 // self.tps, self.tick)

    def checkxy(self, x, y):
        if x < 0 or x >= self.width or y < 0 or y >= self.height:
            return False
        else:
            return True


def main():
    w = World(WIDTH, HEIGHT, livetime=300, tps=TICKS_PER_SECOND, fullscreen=FULL_SCREEN_MODE)
    # yo man ud better go to options, check top of this file
    w.start()


if __name__ == "__main__":
    main()
