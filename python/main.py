#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import tkinter
from random import randint


root = tkinter.Tk()


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

    def render(self):
        # define this function


class Circle(Visual):
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
        self.canvas_object = canvas.create_circle(self.x, self.y, self.radius, color=self.color)


class Segment(Visual):
    def __init__(self, world, ):
        super(Segmnet, self).__init__(world, name)
        self


class World:
    def __init__(self, width, height, visuals=[], window=None, name='NoName'):
        self.name = name
        self.width = width
        self.height = height
        self.visuals = visuals

        if window is None:
            window = root

        window.title('AILSUV')
        self.screen_width = root.winfo_screenwidth()
        self.screen_height = root.winfo_screenheight()
        self.window_width = self.width * SIDE_PX
        self.window_height = self.height * SIDE_PX
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

    def render(self):
        for visual in self.visuals:
            visual.render()


def main():
    w = World(500, 500)
    p1 = Circle(w, 100, 100, 20, '#CCFFCC')
    w.add_visual(p1)
    w.render()


if __name__ == "__main__":
    main()
