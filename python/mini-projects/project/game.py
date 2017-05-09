#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import tyles
from tkinter import *
from PIL import Image, ImageTk


class Clickable_tyle(tyles.TkWorldTyle):
    def __init__(self, world, canvas, x=0, y=0, symb='.', prev_tyle=None):
        super(Clickable_tyle, self).__init__(world, canvas, x, y, symb, prev_tyle)
    
    def select(self, event):
        print('[SELECTION][tyle]', self.symb, self.x, self.y)
        self.delete_image()

        self.texture = ImageTk.PhotoImage(
            Image.alpha_composite(PIL_IMAGES[self.texture_name],
                                  PIL_IMAGES['chosen_corner']))
        self.image = self.canvas.create_image(0, 0, anchor='nw', 
                                              image=self.texture)

        self.info_window = Tk()
        info_window = self.info_window
        info_window.title('INFO')
        info_window.protocol("WM_DELETE_WINDOW", self.deselect)

        ent = Text(info_window, width=3, height=1, font=20)
        ent.pack()
        Label(info_window, text=(' x:' + str(self.x) + 
                                 ' y:' + str(self.y))).pack()
        Label(info_window, text='T - tree').pack()
        Label(info_window, text='~ - water').pack()
        Label(info_window, text='^ - mountain').pack()
        Label(info_window, text='Enter to update').pack()

        def update(event):
            self.symb = ent.get(1.0, END)[0]
            self.update()
            self.deselect()

        info_window.bind('<Return>', update)
        info_window.focus()
        ent.focus()
        info_window.mainloop()



def main():
    world = tyles.TkWorld(10, 10, pre_generated=True, tyle_type=Clickable_tyle)
    world.full_update(to_bind=True)
    global TEXTURES, PIL_IMAGES
    TEXTURES = {
        'road' : ImageTk.PhotoImage(Image.open('./textures/road.png')),
        'water' : ImageTk.PhotoImage(Image.open('./textures/water.png')),
        'mountain' : ImageTk.PhotoImage(Image.open('./textures/mountain.png')),
        'tree' : ImageTk.PhotoImage(Image.open('./textures/tree.png')),
        'chosen_corner' : ImageTk.PhotoImage(Image.open('./textures/chosen_corner.png'))
    }

    PIL_IMAGES = {
        'road' : Image.open('./textures/road.png'),
        'water' : Image.open('./textures/water.png'),
        'mountain' : Image.open('./textures/mountain.png'),
        'tree' : Image.open('./textures/tree.png'),
        'chosen_corner' : Image.open('./textures/chosen_corner.png')
    }
    world.root_window.mainloop()


if __name__ == "__main__":
    main()
