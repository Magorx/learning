#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import atributes as atrs
import info_window
import textures
from random import randint, choice
from time import sleep

from collections import deque


TYPE_CREATURE = 101
TYPE_BUILDING = 102


STANDART_MOVE_MAP = [[0, 1], [1, 0], [-1, 0], [0, -1]]


class Unit():
    def __init__(self, world, x, y, type, name, char, atributes, team=-1, texture=None, move_map=None):
        self.world = world
        self.x = x
        self.y = y
        self.type = type
        self.name = name
        self.char = char
        self.atributes = atributes
        self.texture = texture

        if move_map is None:
            move_map = STANDART_MOVE_MAP
        self.move_map = move_map
        print(move_map)

        self.visible = True
        self.info_window = None

        self.last_filling_distance = 0

    def delete(self):
        tyle = self.world.map[self.x][self.y]
        tyle.delete_texture_by_name(self.name + '_texture')
        tyle.creature = None
        self.close_filling()

    def draw(self):
        self.world.map[self.x][self.y].add_texture(self.texture, self.name + '_texture')

    def fill_zone(self, distance, coating_func, cur_x=None, cur_y=None, moveable_only=False, texture=None):
        if cur_x is None or cur_y is None:
            self.last_filling_distance = distance
            cur_x = self.x
            cur_y = self.y

        tyle = self.world.map[cur_x][cur_y]
        if moveable_only:
            distance += tyle.passability
        else:
            distance += 1

        q = deque()
        q.append([cur_x, cur_y, distance])
        while q:
            cur_x, cur_y, dist = q.popleft()
            if not self.world.check_coords(cur_x, cur_y):
                continue
            tyle = self.world.map[cur_x][cur_y]

            new_dist = dist
            if moveable_only:
                new_dist -= tyle.passability
            else:
                new_dist -= 1
            if new_dist < 0:
                continue

            if tyle.coating_func:
                continue
            if moveable_only and tyle.passability == -1:
                continue

            tyle.coating_func = coating_func
            if texture:
                tyle.add_texture(texture, texture_name=str(self) + '_filled')

            for shift in self.move_map:
                new_x = cur_x + shift[0]
                new_y = cur_y + shift[1]
                q.append([new_x, new_y, new_dist])

    def close_filling(self, distance=0, cur_x=None, cur_y=None, moveable_only=False, texture_used=True):
        if cur_x is None or cur_y is None:
            cur_x = self.x
            cur_y = self.y
            distance = self.last_filling_distance
            self.last_filling_distance = 0
        if not self.world.check_coords(cur_x, cur_y):
            return
        tyle = self.world.map[cur_x][cur_y]
        if distance < 0:
            return
        if moveable_only and not tyle.moveable:
            return

        tyle.coating_func = None
        if texture_used:
            tyle.delete_texture_by_name(str(self) + '_filled')

        new_distance = distance
        if moveable_only:
            new_distance -= tyle.passability
        else:
            new_distance -= 1

        for shift in self.move_map:
            new_x = cur_x + shift[0]
            new_y = cur_y + shift[1]
            if self.world.check_coords(new_x, new_y):
                self.close_filling(new_distance, new_x, new_y, moveable_only)

    def prepare_move(self):
        self.fill_zone(self.atributes.speed, self.move, moveable_only=True, texture=textures.chosen_corner_blue)

    def move(self, tyle):
        if tyle.creature:
            return
        else:
            self.delete()
            self.x = tyle.x
            self.y = tyle.y
            tyle.creature = self
            self.draw()

    def clicked(self, event):
        if event.tk_event.num == 1:
            self.prepare_move()
        else:
            if self.info_window:
                if self.info_window.active:
                    return
        
            buttons = ['Delete', 'Move']
            commands = [self.delete, self.prepare_move]
            self.info_window = info_window.InfoWindow(buttons, commands)
            self.info_window.activate()

    def cancel_selection(self):
        self.close_filling()
        if self.info_window:
            self.info_window.deactivate()
            self.info_window = None


def spawn_unit(world, x, y, type, name, char, atributes, team, texture):
    unit = Unit(world, x, y, type, name, char, atributes, team, texture)
    tyle = unit.world.map[x][y]
    tyle.creature = unit
    unit.draw()
