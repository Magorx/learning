#!/usr/bin/env python3
# -*- coding: utf-8 -*-


BACK_LINKS = ['back', 'Back']


class Menu(object):
    def __init__(self, buttons, links, parent=None, name='', id=0,
                 back_links=BACK_LINKS):
        if len(buttons) != len(links):
            raise IndexError

        self.buttons = \
            [['Back', 0]] + [[buttons[i], links[i]] for i in range(len(buttons))]
        self.parent = parent
        self.name = name
        self.id = id
        self.back_links = back_links

        self.update_longest_button()

    def update_longest_button(self):
        max_len = 0
        for button in self.buttons:
                button_name = button[0]
                try:
                    button_name = str(button_name)
                except Exception:
                    continue
                if len(button_name) > max_len:
                    max_len = len(button_name)
        self.max_button_name_len = max_len

    def print_self(self):
        for i in range(1, len(self.buttons)):
            print('|{: ^{max}}|'.format('{}. {}'.format(i, self.buttons[i][0]), max=self.max_button_name_len+3))

    def button_pressed(self, button_index):
        if button_index == 0:
            return None
        link = self.buttons[button_index][1]
        if callable(link):
            link()
            return 0

    def __call__(self):
        while True:
            print('_' * (self.max_button_name_len + 5))
            self.print_self()
            print('_' * (self.max_button_name_len + 5))
            pressed = input()
            try:
                pressed = int(pressed)
            except Exception:
                print('Input should be integer')
                continue
            if pressed >= len(self.buttons) or pressed < 0:
                print('Input must be chosen from variants')
                continue
            to_do = self.button_pressed(pressed)
            if to_do is None:
                return 0


def main():
    def hi():
        print('HELLO')
    def bye():
        print('GOODBYE')
    third = Menu(['Bye', 'back'], [bye, 'back'])
    second = Menu(['Hello', 'back'], [hi, 'back'])
    one = Menu(['Hi_menu', 'Bye_menu', 'exit'], [second, third, exit])
    one()


if __name__ == "__main__":
    main()
