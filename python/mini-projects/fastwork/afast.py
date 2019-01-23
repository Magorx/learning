#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import tkinter as tk
from random import randint, choice, shuffle


def _create_circle(self, x, y, r, **kwargs):
    return self.create_oval(x-r, y-r, x+r, y+r, **kwargs)
tk.Canvas.create_circle = _create_circle


SHIFTS = {'w' : [0, -1], 'a' : [-1, 0], 'd' : [1, 0], 's' : [0, 1]}


class World():
    def __init__(self, width, height, pl_radius, gl_radius):
        self.width = width
        self.height = height

        self.root = tk.Tk()
        self.canvas = tk.Canvas(self.root, width=width, height=height)
        self.root.bind('<KeyPress>', self.press_handler)
        self.root.bind('<KeyRelease>', self.release_handler)
        self.canvas.pack()
        self.key_set = set()

        self.player = Player(self, width // 2, height // 2, 'green', 50)
        self.player.redraw()

        #self.goal = Goal(self, randint(radius, width - radius))

        self.root.after(10, self.handler)


    def handler(self):
        for key in self.key_set:
            if (key in ['w', 'a', 's', 'd']):
                self.player.move(key)
        self.root.after(10, self.handler)

    def start(self):
        self.root.mainloop()

    def press_handler(self, event):
        self.key_set.add(event.char)

    def release_handler(self, event):
        self.key_set.remove(event.char)

class Player():
    def __init__(self, world, x, y, color, radius, speed=5):
        self.world = world
        self.color = color
        self.radius = radius
        self.x = x
        self.y = y

        self.speed = speed

        self.sprite = None

    def redraw(self):
        if self.sprite:
            self.world.canvas.delete(self.sprite)
        self.sprite = self.world.canvas.create_circle(self.x, self.y, self.radius, fill=self.color)

    def move(self, dir='w'):
        if dir not in SHIFTS:
            return

        dx, dy = SHIFTS[dir]
        self.x += dx * self.speed
        self.y += dy * self.speed
        self.redraw()


class Goal():
    def __init__(self, world, x, y, color, radius):
        pass


def main():
    w = World(500, 500, 50, 50)
    w.start()


if __name__ == "__main__":
    main()