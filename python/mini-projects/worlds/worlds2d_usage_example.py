#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import worlds2d as worlds
from random import randint, choice


def main():
    world = worlds.World(15, 15, is_tor=True)
    world.GenerateWorld()
    cr = worlds.Creature(world, 19, 19)
    handler = worlds.StandardCreatureButtonInputHandler(cr)
    string = ''
    while string != 'stop':
        world.print()
        string = input()
        handler(string)


if __name__ == "__main__":
    main()
