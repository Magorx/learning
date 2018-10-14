#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import game_world


def main():
    world = game_world.GameWorld(20, 20, pre_generated=True)
    world.root_window.mainloop()


if __name__ == '__main__':
    main()