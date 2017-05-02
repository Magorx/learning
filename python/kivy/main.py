#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from random import random
from kivy.app import App
from kivy.uix.gridlayout import GridLayout
from kivy.uix.widget import Widget
from kivy.uix.button import Button
from kivy.graphics import Color, Ellipse, Line


class MyPaintWidget(Widget):

    def on_touch_down(self, touch):
        color = (random(), 1, 1)
        with self.canvas:
            Color(*color, mode='hsv')
            d = 30.
            Ellipse(pos=(touch.x - d / 2, touch.y - d / 2), size=(d, d))
            touch.ud['line'] = Line(points=(touch.x, touch.y))

    def on_touch_move(self, touch):
        touch.ud['line'].points += [touch.x, touch.y]


class MyPaintApp(App):

    def build(self):
        parent = Widget()
        self.painter = MyPaintWidget()
        clearbtn = Button(text='Clear')
        clearbtn.bind(on_release=self.clear_canvas)
        parent.add_widget(self.painter)
        parent.add_widget(clearbtn)
        return parent

    def clear_canvas(self, obj):
        self.painter.canvas.clear()


class MyApp(App):

    def build(self):
        self.number = 0
        parent = Widget()
        layout = GridLayout(cols=2)
        plus = Button(text='Plus')
        minus = Button(text='Minus')
        plus.bind(on_release=self.Plus)
        minus.bind(on_release=self.Minus)
        num = Button(text=str(self.number))
        layout.add_widget(plus)
        layout.add_widget(minus)
        layout.add_widget(num)

        return layout

    def Plus(self, touch):
        self.number += 1

    def Minus(self, touch):
        self.number -= 1
        print(self.number)




if __name__ == '__main__':
    MyApp().run()
