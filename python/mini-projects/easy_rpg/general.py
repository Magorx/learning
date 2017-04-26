#!/usr/bin/env python3
# -*- coding: utf-8 -*-

class Menu(object):
    def __init__(self, buttons, links, name='', id=0):
        if len(buttons) != len(links):
            raise IndexError
        self.buttons = ['Back'] + buttons
        self.links = ['Back'] + links
        self.name = name
        self.id = id

    def print_buttons(self):
        for i in range(len(self.buttons)):
            print('{}. {}'.format(i, self.buttons[i]))

    def button_pressed(self, button_index):
        if button_index == 0:
            return 'Back'
        link = self.links[button_index]
        if callable(link):
            link()
        elif isinstance(link, Menu):
            link.call()

    def call(self):
        while True:
            print('-- {} --'.format(self.name))
            self.print_buttons()
            print('-' * (len(self.name) + 6))
            pressed = input()
            try:
                pressed = int(pressed)
            except Exception:
                print('Input should be integer')
                continue
            if pressed >= len(self.links):
                print('Input must be chosen from variants')
                continue
            to_do = self.button_pressed(pressed)
            if to_do == 'Back':
                return 0

                
def main():
    pass


if __name__ == "__main__":
    main()
