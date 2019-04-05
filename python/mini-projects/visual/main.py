#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import tkinter as tk
from random import randint, choice
import math


root = tk.Tk()


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


def _create_circle(self, x, y, r, **kwargs):
    return self.create_oval(x-r, y-r, x+r, y+r, **kwargs)
tk.Canvas.create_circle = _create_circle


def noised(arr, delta):
    ret = arr[::]
    for i in range(len(ret)):
        ret[i] += randint(-delta, +delta)
    return ret


class Visual:
    def __init__(self, world, name='NoName'):
        self.world = world
        self.name = name
        self.canvas_object = None

    def render(self):
        pass # define this function


class Point(Visual):
    def __init__(self, world, x, y, radius, color, name='NoName'):
        super(Point, self).__init__(world, name)
        self.x = x
        self.y = y
        self.radius = radius
        self.color = color

        self.canvas_object = None

    def clear(self):
        canvas = self.world.canvas
        if self.canvas_object:
            canvas.delete(self.canvas_object)

    def render(self):
        canvas = self.world.canvas
        if self.canvas_object:
            canvas.delete(self.canvas_object)
        self.canvas_object = canvas.create_circle(self.x, self.y, self.radius, fill=self.color, outline=self.color)

    def vector(self):
        return Vector(self.world, self.x, self.y, 1, self.color)

    def __sub__(self, other):
        return self.vector() - other.vector()


class Vector(Point):
    def __init__(self, world, x, y, width, color, name='NoName'):
        super(Vector, self).__init__(world, x, y, 0, color, name)
        self.width = width

    def copied(self, new_x, new_y):
        return Vector(self.world, new_x, new_y, self.width, self.color)

    def __add__(self, other):
        return Vector(self.world, self.x + other.x, self.y + other.y, self.width, self.color)

    def __sub__(self, other):
        x = self.x - other.x
        y = self.y - other.y
        return self.copied(x, y)

    def __mul__(self, number):
        x = self.x * number
        y = self.y * number
        return self.copied(x, y)

    def angle(self):
        return math.atan2(self.x, self.y)

    def len(self):
        return math.sqrt(self.x * self.x + self.y * self.y)

    def normalize(self):
        l = self.len()
        self.x = self.x / l
        self.y = self.y / l

    def normalized(self):
        l = self.len()
        x = self.x / l
        y = self.y / y
        return self.copied(x, y)

    def rotate_clockwise(self):
        new_x = self.y
        new_y = -self.x
        self.x = new_x
        self.y = new_y

    def rotate_conterclockwise(self):
        new_x = -self.y
        new_y = self.x
        self.x = new_x
        self.y = new_y

    def coords(self):
        return [self.x, self.y]


class Segment(Visual):
    def __init__(self, world, p1, p2, width, color, name='NoName'):
        super(Segment, self).__init__(world, name)
        self.p1 = p1
        self.p2 = p2
        self.width = width
        self.color = color

    def render(self):
        canvas = self.world.canvas
        if self.canvas_object:
            canvas.delete(self.canvas_object)

        v = self.p2 - self.p1
        v.rotate_clockwise()
        v.normalize()
        v *= self.width
        p1 = self.p1.vector() + v
        p2 = self.p2.vector() + v
        v = v * (-1)
        p3 = self.p2.vector() + v
        p4 = self.p1.vector() + v
        points = [point.coords() for point in [p1, p2, p3, p4]]

        self.canvas_object = canvas.create_polygon(points, fill=self.color)


class Lightning(Visual):
    def __init__(self, world, p1, p2, seg_num, width, delta, color, name='NoName'):
        super(Lightning, self).__init__(world, name)
        self.p1 = p1
        self.p2 = p2
        self.width = width
        self.color = color
        self.seg_num = seg_num
        self.delta = delta

    def clear(self):
        canvas = self.world.canvas
        if self.canvas_object:
            for obj in self.canvas_object:
                canvas.delete(obj)

    def render(self):
        canvas = self.world.canvas
        if self.canvas_object:
            for obj in self.canvas_object:
                canvas.delete(obj)

        v = self.p2 - self.p1
        points = []
        seg_num = self.seg_num
        delta = self.delta
        for k in range(seg_num + 1):
            pk = self.p1.vector() + v * (k / seg_num)
            pk.x += randint(-delta, +delta)
            pk.y += randint(-delta, +delta)
            points.append(pk)

        segs = []
        for i in range(len(points) - 1):
            p1 = points[i]
            p2 = points[i + 1]
            segs.append(Segment(self.world, p1, p2, self.width, self.color))

        self.canvas_object = []
        for seg in segs:
            seg.render()
            self.canvas_object.append(seg.canvas_object)


class World:
    def __init__(self, width, height, tps=30, visuals=[], window=None, name='NoName'):
        self.name = name
        self.width = width
        self.height = height
        self.tps = tps
        self.visuals = visuals

        if window is None:
            window = root

        window.title('AILSUV')
        self.screen_width = root.winfo_screenwidth()
        self.screen_height = root.winfo_screenheight()
        self.window_width = self.width
        self.window_height = self.height
        self.window_standard_x = (self.screen_width - self.window_width) // 2
        self.window_standard_y = (self.screen_height - self.window_height) // 2
        window.geometry('{}x{}+{}+{}'.format(self.window_width, self.window_height, 
                                             self.window_standard_x, self.window_standard_y))
        window.protocol("WM_DELETE_WINDOW", exit)
        self.root = window

        self.canvas = tk.Canvas(self.root, width=width, height=height)
        self.canvas.bind('<Button-1>', self.on_click)
        self.canvas.bind('<Motion>', self.update_cursor_position)
        self.canvas.pack()

        self.new_point = None
        self.cursor_x = 0
        self.cursor_y = 0

    def on_click(self, event):
        x = event.x
        y = event.y
        if self.new_point is None:
            point = Point(self, x, y, 0, '#000000')
            self.new_point = point
        else:
            p1 = self.new_point
            p2 = Point(self, x, y, 0, '#000000')
            l = Lightning(self, p1, p2, 20, 3, 5, self.visuals[-1].color)
            self.visuals[-1].clear()
            self.visuals.pop()
            self.visuals.append(l)
            self.visuals.append(p1)
            self.new_point = None

    def update_cursor_position(self, event):
        x = event.x
        y = event.y
        self.cursor_x = x
        self.cursor_y = y

        if self.new_point:
            p1 = self.new_point
            p2 = Point(self, x, y, 0, '#000000')
            l = Lightning(self, p1, p2, 20, 3, 5, randcolor())
            self.visuals[-1].clear()
            self.visuals.pop()
            self.visuals.append(l)
            l.render()

    def add_visual(self, visual):
        self.visuals.append(visual)

    def render_all(self):
        for visual in self.visuals:
            visual.render()

    def tick(self):
        self.render_all()

        self.root.after(1000 // self.tps, self.tick)

    def start(self):
        self.root.after(1000 // self.tps, self.tick)
        self.root.mainloop()


def main():
    w = World(500, 500)
    p = Point(w, 0, 0, 0, '#000000')
    w.add_visual(p)
    w.start()


if __name__ == "__main__":
    main()
