#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import tkinter as tk
from random import randint
import math


root = tk.Tk()


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
        self.canvas.pack()

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
    green = '#22FF22'
    blue = '#2222FF'
    w = World(500, 500)
    p1 = Point(w, 0, 0, 20, '#33FF33')
    p2 = Point(w, 500, 500, 20, '#33FF33')
    p3 = Point(w, 0, 500, 20, '#33FF33')
    p4 = Point(w, 500, 0, 20, '#33FF33')
    l1 = Lightning(w, p1, p2, 20, 2, 10, green)
    l2 = Lightning(w, p3, p4, 20, 2, 10, blue)
    w.add_visual(l1)
    w.add_visual(l2)
    w.start()


if __name__ == "__main__":
    main()
