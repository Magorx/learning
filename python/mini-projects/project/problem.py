#!/usr/bin/env python3
# -*- coding: utf-8 -*-


from tkinter import *
from PIL import Image, ImageTk

root = Tk()

canvas = Canvas(width=500, height=400)
canvas.pack()

image = ImageTk.PhotoImage(Image.open('./textures/tree.png'))
canvas.create_text(100, 100, text='TEXTTEXTEXTEXTEXT')
canvas.create_image(100, 100, image=image)

root.mainloop()