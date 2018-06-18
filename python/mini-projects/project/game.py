#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import worlds
from tkinter import *
from PIL import Image, ImageTk
from random import randint, choice


WORLD_WIDTH = 10
WORLD_HEIGHT = 10
LOG_WIDTH = 40
LOG_HEIGHT = 5
LOG_FONT = 12

SIDE_PX = 50
ERROR = -1
ERROR_BAD_BINDING_ARGS = -2


root = Tk()
root.config(width=WORLD_WIDTH * SIDE_PX + int(LOG_WIDTH*LOG_FONT*0.86),
            height=WORLD_HEIGHT * SIDE_PX)
root.protocol("WM_DELETE_WINDOW", exit)

TEXTURES = {
    'road' : ImageTk.PhotoImage(Image.open('./textures/road.png')),
    'water' : ImageTk.PhotoImage(Image.open('./textures/water.png')),
    'mountain' : ImageTk.PhotoImage(Image.open('./textures/mountain.png')),
    'tree' : ImageTk.PhotoImage(Image.open('./textures/tree.png')),
    'men' : ImageTk.PhotoImage(Image.open('./textures/men.png')),
    'transparent' : ImageTk.PhotoImage(Image.open('./textures/transparent.png')),
    'chosen_corner_red' : ImageTk.PhotoImage(Image.open('./textures/chosen_corner_red.png')),
    'chosen_corner_blue' : ImageTk.PhotoImage(Image.open('./textures/chosen_corner_blue.png')),
    'chosen_corner_green' : ImageTk.PhotoImage(Image.open('./textures/chosen_corner_green.png')),
    'chosen_corner_golden' : ImageTk.PhotoImage(Image.open('./textures/chosen_corner_golden.png')),
    'chosen_corner_brown' : ImageTk.PhotoImage(Image.open('./textures/chosen_corner_brown.png'))
}

CORNERS_TEXTURES = {
    'chosen_corner_red' : TEXTURES['chosen_corner_red'],
    'chosen_corner_blue' : TEXTURES['chosen_corner_blue'],
    'chosen_corner_green' : TEXTURES['chosen_corner_green'],
    'chosen_corner_golden' : TEXTURES['chosen_corner_golden'],
    'chosen_corner_brown' : TEXTURES['chosen_corner_brown']
}


def coord_range(x1, y1, x2, y2):
    return abs(x1 - x2) + abs(y1 - y2)


def write_to_log(string, end='\n'):
    LOG.insert(END, string + end)
    LOG.see(END)
    return 0


class Creature(object):
    def __init__(self, place, name, team=0, atk=1, hp=1, mp=1, 
                 x=0, y=0, texture=TEXTURES['men']):
        self.place = place
        self.name = name
        self.team = team
        self.atk = atk
        self.max_hp = hp
        self.hp = hp
        self.max_mp = mp
        self.mp = mp
        self.x = x
        self.y = y
        self.selected = False
        self.speed = 2
        self.texture = texture
        place.creature = self

        self.info = worlds.TkTyleInfo(place, place.map[x][y].canvas)
        self.update_info()

    def delete_self_texture(self):
        tyle = self.place.map[self.x][self.y]
        tyle.delete_texture(tyle.textures.index(self.texture))

    def update_info(self, new_canvas = False):
        if new_canvas:
            x, y, place = self.x, self.y, self.place
            self.delete_info()
            self.info = worlds.TkTyleInfo(place,
                                          place.map[x][y].canvas)
        self.info.add_info_text(0, 0, self.mp, mark='mp', anchor=NW, 
                                color='blue')
        self.info.add_info_text(0, SIDE_PX, self.hp, mark='hp', anchor=SW,
                                color='red')
        self.info.add_info_text(SIDE_PX, SIDE_PX, self.atk, mark='atk', anchor=SE,
                                color='#800000')

    def delete_info(self):
        self.info.delete_texture('hp')
        self.info.delete_texture('mp')
        self.info.delete_texture('atk')

    def delete_info(self):
        self.info.delete_info('hp')
        self.info.delete_info('mp')
        self.info.delete_info('atk')

    def check_alive(self):
        if self.hp > 0:
            return True
        else:
            return False

    def die(self):
        self.unselect()
        self.delete_info()

        tyle = self.place.map[self.x][self.y]
        tyle.creature = None
        self.delete_self_texture()

    def select(self):
        self.selected = True
        for x in range(max(self.x - 2, 0), min(self.x + 3, self.place.width)):
            for y in range(max(self.y - 2, 0), min(self.y + 3, self.place.height)):
                tyle = self.place.map[x][y]
                cr = tyle.creature
                if coord_range(self.x, self.y, x, y) <= self.speed:
                    if not cr:
                        if not tyle.creature_can_move:
                            tyle.creature_moving(self)
                    else:
                        if tyle.creature_can_attack:
                            continue
                        if (not self.team or 
                           (self.team and self.team != cr.team)):
                            tyle.creature_attacking(self)
                        if cr == self:
                            tyle.add_texture(
                                self.place.textures['chosen_corner_golden'])
        self.update_info()


    def unselect(self):
        self.selected = False
        for x in range(max(self.x - 2, 0), min(self.x + 3, self.place.width)):
            for y in range(max(self.y - 2, 0), min(self.y + 3, self.place.height)):
                if coord_range(self.x, self.y, x, y) > self.speed:
                    continue

                tyle = self.place.map[x][y]
                cr = tyle.creature
                if cr is not None:
                    cr.update_info()

                to_clear = False
                if tyle.creature_can_move == self:
                    tyle.creature_can_move = None
                    to_clear = True
                if tyle.creature_can_attack == self:
                    tyle.creature_can_attack = None
                    to_clear = True
                if self == cr:
                    to_clear = True

                if to_clear:
                    tyle.set_click_handler('default')
                    for corner in CORNERS_TEXTURES:
                        i = 0
                        while i < len(tyle.textures):
                            if tyle.textures[i] == CORNERS_TEXTURES[corner]:
                                tyle.delete_texture(i)
                            i += 1


    def move(self, x, y):
        from_tyle = self.place.map[self.x][self.y]
        to_tyle = self.place.map[x][y]
        if to_tyle.creature is not None:
            return 0

        self.delete_self_texture()
        from_tyle.creature = None

        to_tyle.set_creature(self)

        self.x = x
        self.y = y
        self.update_info(new_canvas=True)

        write_to_log('{} moved to [{}][{}]'.format(self.name, x, y))

    def attack(self, defender):
        if defender is None or (self.team and self.team == defender.team):
            return 0

        defender.hp -= self.atk
        write_to_log('{} hit {}'.format(self.name, defender.name))
        write_to_log('{} dmg dealt'.format(self.atk))
        if not defender.check_alive():
            defender.die()
            write_to_log('{} killed {}'.format(self.name, defender.name))

        return 0


class Clickable_tyle(worlds.TkWorldTyle):
    def __init__(self, world, canvas, x=0, y=0, symb='.'):
        worlds.TkWorldTyle.__init__(self, world, canvas, x, y, symb)
        self.creature = None
        self.creature_can_move = None
        self.creature_can_attack = None
        self.click_handler = self.handler_default
        self.click_menu = worlds.WindowedChoice(['1', '2'], ['2', '3'])

    def handler_default(self, event):
        #self.click_menu.activate(self.canvas)
        if self.creature is None:
            self.set_creature(Creature(world, 'Cr', x=self.x, y=self.y, 
                                       hp=randint(1, 4), atk=randint(1, 2),
                                       mp=randint(2, 5)))
            self.creature.update_info()
        else:
            self.creature.select()

    def set_click_handler(self, handler):
        if handler == 'default':
            self.click_handler = self.handler_default
        if handler == 'creature_moved':
            self.click_handler = self.handler_creature_moved
        if handler == 'creature_attacked':
            self.click_handler = self.handler_creature_attacked

        self.canvas.bind('<Button-1>', self.click_handler)
        return 0

    def handler_creature_moved(self, event):
        cr = self.creature_can_move
        cr.unselect()
        cr.move(self.x, self.y)
        
        return 0

    def handler_creature_attacked(self, event):
        self.creature_can_attack.attack(self.creature)
        self.creature_can_attack.unselect()
        return 0


    def creature_moving(self, creature):
        if self.creature_can_move is not None:
            return 0

        self.creature_can_move = creature
        self.add_texture(texture_name='chosen_corner_brown')
        self.set_click_handler('creature_moved')

    def creature_attacking(self, creature):
        cr = self.creature
        if not cr or cr == creature:
            return 0
        if cr.team and cr.team == creature.team:
            return 0

        self.add_texture(creature.place.textures['chosen_corner_red'])
        self.creature_can_attack = creature
        self.set_click_handler('creature_attacked')

    def set_creature(self, creature):
        self.creature = creature
        self.add_texture(creature.texture)

    def bind(self, button, action):
        try:
            self.canvas.bind(button, action)
            return 0
        except:
            return ERROR_BAD_BINDING_ARGS


def main():
    global world
    world = worlds.TkWorld(WORLD_WIDTH, WORLD_HEIGHT, pre_generated=True,
                          tyle_type=Clickable_tyle, side_px=SIDE_PX,
                          window=root, textures=TEXTURES)
    global LOG
    LOG = Text(font=LOG_FONT, wrap=WORD, width=LOG_WIDTH, height=LOG_HEIGHT)
    LOG.place(x=WORLD_WIDTH*SIDE_PX + 1, y=0)
    world.root_window.mainloop()


if __name__ == "__main__":
    main()
