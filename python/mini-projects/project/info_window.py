#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import tkinter
import random
import time


class InfoWindow(object):
    def __init__(self, choices, commands, imgs=[], side_px=50, button_height=2, button_width=10):
        if len(choices) != len(commands) or len(choices) < 1:
            raise IndexError
        if imgs and len(imgs) != len(choice):
            raise IndexError

        self.choices = choices
        self.commands = commands
        self.imgs = imgs
        self.side_px = side_px
        self.button_height = button_height
        self.button_width = button_width
        self.window = None
        self.to_return = None

        self.active = False

    def die(self, event):
        time.sleep(1)
        self.deactivate()

    def activate(self):
        if self.window is not None:
            return 0
        self.active = True

        window = tkinter.Toplevel()
        side_px = self.side_px
        for i in range(len(self.choices)):
            canvas = tkinter.Canvas(window, width=side_px, height=side_px, bg='green')
            if self.imgs:
                canvas.create_image(i * side_px, i * side_px, image=self.imgs[i])
            button = tkinter.Button(canvas, text=str(self.choices[i]), command=self.commands[i], width=self.button_width, height=self.button_height)
            button.pack()
            canvas.pack()
        self.window = window

    def deactivate(self, tk_event=None):
        self.active = False
        self.window.destroy()
        self.window = None
        print('QUCH')

    def return_by_index(self, i):
        print('returned ', self.i)
        self.deactivate()
        return self.commands[i]


def main():
    world = tk_worlds.TkWorld(15, 15)
    world.GenerateWorld(lands_to_generate=100, defined_land_square=20)
    world.full_update(to_set_texture_by_symb=True)
    world.root_window.mainloop()


if __name__ == "__main__":
    main()