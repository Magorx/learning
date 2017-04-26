#!/usr/bin/env python3
# -*- coding: utf-8 -*-


BACK_LINKS = ['back', 'Back']


class Menu(object):
    def __init__(self, buttons, links, parent=None, name='', id=0,
                 back_links=BACK_LINKS):
        if len(buttons) != len(links):
            raise IndexError

        self.buttons = buttons
        self.links = links
        self.parent = parent
        self.name = name
        self.id = id
        self.back_links = back_links

    def print_buttons(self):
        for i in range(len(self.buttons)):
            print('{}. {}'.format(i, self.buttons[i]))

    def button_pressed(self, button_index):
        if self.links[button_index] in self.back_links:
            return 'Back'
        link = self.links[button_index]
        if callable(link):
            link()
        elif isinstance(link, Menu):
            link.call()

    def call(self):
        while True:
            print('--{}--'.format(self.name))
            self.print_buttons()
            print('-' * (len(self.name) + 4))
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
