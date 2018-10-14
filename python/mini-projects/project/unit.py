#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import atributes as atrs
from random import randint, choice


TYPE_CREATURE = 101
TYPE_BUILDING = 102


class Unit():
    def __init__(self, world, x, y, type, name, char, atributes, team=-1, texture=None):
        self.world = world
        self.x = x
        self.y = y
        self.type = type
        self.name = name
        self.char = char
        self.atributes = atributes
        self.texture = texture

    def draw(self):
        self.world.map[self.x][self.y].add_texture(self.texture)


def spawn_unit(world, x, y, type, name, char, atributes, team, texture):
    unit = Unit(world, x, y, type, name, char, atributes, team, texture)
    tyle = unit.world.map[x][y]
    tyle.creature = unit
    unit.draw()
