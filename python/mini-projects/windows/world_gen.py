#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import fixpath
from colorama import init, Fore, Back, Style
from random import randint, choice
from time import sleep
from getch import getch 

FORES = [ Fore.BLACK, Fore.RED, Fore.GREEN, Fore.YELLOW, Fore.BLUE, Fore.MAGENTA, Fore.CYAN, Fore.WHITE ]
BACKS = [ Back.BLACK, Back.RED, Back.GREEN, Back.YELLOW, Back.BLUE, Back.MAGENTA, Back.CYAN, Back.WHITE ]
STYLES = [ Style.DIM, Style.NORMAL, Style.BRIGHT ]
init(autoreset = True)
#pos = lambda y, x: '\x1b[%d;%dH' % (y, x)


def pos(y, x):
    return '\x1b[{};{}H'.format(y, x)

class player:
    hp = randint(5, 15)
    x = -1
    y = -1
    fore = Fore.BLACK
    back = Back.BLACK
    style = Style.NORMAL
    symb = "@"
    name = "Dummy"
    def construct(self, world):
        while True:
            x = randint(0, len(world) - 1)
            y = randint(0, len(world[0]) - 1)
            if not world[x][y].full:
                print("!")
                world[x][y].full = 1
                self.x = x
                self.y = y
                break
        self.fore = choice(FORES)
        self.back = choice(BACKS)
        self.style = Style.BRIGHT
    def move(self, world, direction):
        if direction == UP and self.x - 1 >= 0:
            if not world[self.x - 1][self.y].full :
                world[self.x - 1][self.y].full = 1
                world[self.x][self.y].full = 0
                self.x -= 1
        if direction == DOWN and self.x + 1 < len(world):
            if not world[self.x + 1][self.y].full :
                world[self.x + 1][self.y].full = 1
                world[self.x][self.y].full = 0
                self.x += 1
        if direction == LEFT and self.y - 1 >= 0:
            if not world[self.y - 1][self.y].full :
                world[self.y - 1][self.y].full = 1
                world[self.x][self.y].full = 0
                self.y -= 1
        if direction == RIGHT and self.y + 1 < len(world[0]):
            if not world[self.y + 1][self.y].full :
                world[self.y + 1][self.y].full = 1
                world[self.x][self.y].full = 0
                self.y += 1
        


class map_tile:
    name = "SPACE"
    fore = Fore.BLACK
    back = Back.BLACK
    style = Style.NORMAL
    symb = "#"
    full = 0
    
    def gen_symb_tile(self, symb):
        self.symb = symb
        if symb == "^":
            self.name = "mountain"
            self.fore = Fore.BLACK
            self.back = Back.BLACK
            self.style = Style.BRIGHT
        elif symb == "T":
            self.name = "tree"
            self.fore = Fore.GREEN
            self.back = Back.GREEN
            self.style = Style.BRIGHT
        elif symb == "~":
            self.name = "water"
            self.fore = Fore.CYAN
            self.back = Back.CYAN
            self.style = Style.BRIGHT
        elif symb == ".":
            self.name = "road"
            self.fore = Fore.YELLOW
            self.back = Back.YELLOW
            self.style = Style.NORMAL
        elif symb == "X":
            self.name = "treasure"
            self.fore = Fore.RED
            self.back = Back.YELLOW
            self.style = Style.BRIGHT
        else:
            self.name = "ERROR"
            self.fore = Fore.WHITE
            self.back = Back.WHITE
            self.style = Style.BRIGHT

#=General=======================================================================
def print_frame(x_st, y_st, x_end, y_end, symb = " ", fore = Fore.WHITE,
                back = Back.WHITE, style = Style.NORMAL):
    init(autoreset = False)
    print(fore + back + style, end="")
    print(pos(x_st, y_st) + symb * (y_end - y_st), end="")
    for i in range(x_st, x_end - x_st + 1):
        print(pos(i, x_end - 1) + fore + back + style + symb, end="")
        print(pos(i, x_st) + fore + back + style + symb, end="")
    print(pos(x_end - 1, y_st) + fore + back + style + symb * (y_end - y_st),
          end="")
    init(autoreset = True)

def getchar():
    return str(getch())[2]

def copy_style(fr, to):
    to.fore = fr.fore
    to.back = fr.back
    to.style = fr.style
#==Map==========================================================================
def mapshow(map_arg, players_arg, x = 2, y = 2, mode = 1):
    x = max(2, x)
    y = max(2, y)
    if mode:
        print_frame(x - 1, y - 1, x + MAPSIZE + 1, y + MAPSIZE + 1)
        for i in range(len(map_arg)):
            for j in range(len(map_arg)):
                tile = map_arg[i][j]
                print(pos(i + x, j + y) + tile.fore + tile.back +
                      tile.style + tile.symb, end="")
    for i in players_arg:
        print(pos(i.x + x, i.y + y) + i.fore + i.back + i.style + i.symb, end="")
    print(pos(20, 1))


def gen_landshaft(world, sk_len, symb, start_x , start_y, ignore = [],
                  allowed = [], replace_chance = 15, start_symb = "",
                  forbiden = []):

    ignored = ["@", "X"]
    for i in range(len(ignore)):
        ignored.append(ignore[i])
    x = start_x
    y = start_y
    
    sk_now = 1
    abs_len = 0
    mode = 0
    if allowed:
        mode = 1
    if len(start_symb) == 1:
        world[x][y].symb = start_symb
        ignored.append(start_symb)

    last = 0
    while sk_now < sk_len:
        if world[x][y].symb in forbiden:
            if last == UP:
                x += 1
            elif last == DOWN:
                x -= 1
            elif last == LEFT:
                y += 1
            elif last == RIGHT:
                y -= 1
            else:
                x = start_x
                y = start_y
        abs_len += 1
        if world[x][y].symb not in ignored:
            if mode == 0 and world[x][y].symb != symb:
                world[x][y].symb = symb
                world[x][y].gen_symb_tile(symb)
                sk_now += 1
            elif mode == 1:
                if world[x][y].symb in allowed:
                    world[x][y].symb = symb
                sk_now += 1
            else:
                roll = randint(0, replace_chance)
                if roll == 1:
                    world[x][y].symb = "#"
                    sk_now -= 1
        
        roll = randint(0, (MAPSIZE_X * MAPSIZE_Y))
        if not roll:
            if world[x][y].symb == symb:
                world[x][y].symb = "X"
            continue
        else:
            roll = randint(1, 4)
        last = roll
        if roll == UP and x - 1 >= 0:
            x -= 1
        if roll == DOWN and x + 1 < MAPSIZE:
            x += 1
        if roll == LEFT and y - 1 >= 0:
            y -= 1
        if roll == RIGHT and y + 1 < MAPSIZE:
            y += 1
        if abs_len > 999:
            break


def gen_world():
    world = [[map_tile() for i in range(MAPSIZE)] for j in range(MAPSIZE)]
    landshaft_symbs = ["X", "^", "T", "~"]
    tiped_tiles = MAPSIZE * MAPSIZE // (len(landshaft_symbs))
    for i in range(1, len(landshaft_symbs)):
        roll = randint(4, 7)
        for j in range(roll):
            gen_landshaft(world, max(tiped_tiles // roll, 2), landshaft_symbs[i],
                          randint(0, MAPSIZE - 1), randint(0, MAPSIZE - 1),
                          ignore = landshaft_symbs, forbiden = landshaft_symbs)
            if SLOWMODE:
                mapshow(world, [], x = MSP, y  = MSP)
                sleep(0.1)
            
    for i in range(MAPSIZE):
        for j in range(MAPSIZE):
            if world[i][j].symb not in landshaft_symbs:
                world[i][j].symb = "."
    
    for i in range(MAPSIZE):
        for j in range(MAPSIZE):
            world[i][j].gen_symb_tile(world[i][j].symb)
    return world


#=Player's movement=============================================================
def handle_input(in_arg, player, world):
    MOVE_SYMBS = ["w", "s", "a", "d"]
    if in_arg in MOVE_SYMBS:
        player.move(world, MOVE_SYMBS.index(in_arg) + 1)
        

#=Main==========================================================================
MAPSIZE = 15
SLOWMODE = 0
MSP = 2
MAPSIZE_X = 25
MAPSIZE_Y = 40
UP = 1
DOWN = 2
LEFT = 3
RIGHT = 4
world = gen_world()
p = player()
p.construct(world)
mapshow(world, [p], x = MSP, y = MSP)
while True:
    a = getchar()
    if a == "q":
        break
    handle_input(a, p, world)
    mapshow(world, [p], x = MSP, y = MSP)
print(pos(20, 1))

