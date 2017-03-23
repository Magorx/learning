import random
import time

ERR_INVALID_COORDS = -100
ERR_ARGS = -99

STANDART_WORLD_WIDTH = 15
STANDART_WORLD_HEIGHT = 15

class Tyle(object):
    def __init__(self, symb='.'):
        self.symb = symb
    
    def __repr__(self):
        return self.symb


class WorldTyle(Tyle):
    def __init__(self, world, x, y, symb='.'):
        self.x = x
        self.y = y
        self.symb = symb
        self.full = False


class World(object):
    def __init__(self, width, height, tyle_type=WorldTyle, common_symb='.'):
        self.map = [[tyle_type(self, j, i, symb=common_symb) for i in range (height)]
                                 for j in range(width)]
        self.common_symb = common_symb
        self.time = 0
        self.width = width
        self.height = height
        self.square = width * height

    def print(self):
        for x in range(self.width):
            for y in range(self.height):
                print(self.map[x][y], end='')
            print()

    def GenerateLandshaft(self, square, symb, start_x, start_y,
                          forbiden=[], replacements=[-1, 1],
                          to_update=False, delay_between_updates=0):
        if (start_x < 0 or start_y < 0 or
           start_x >= self.width or start_y >= self.height):
           return ERR_INVALID_COORDS
        if square < 0 or len(replacements) != 2:
            return ERR_ARGS

        width = self.width
        height = self.height
        self.map = self.map
        cur_square = 0
        x = start_x
        y = start_y
        itters = 0

        while cur_square < square:
            itters += 1
            if itters > square * 10:
                break

            if self.map[x][y].symb in forbiden:
                if x == start_x and y == start_y:
                    break
                x = start_x
                y = start_y

            if self.map[x][y].symb == symb:
                rand_int = random.randint(0, replacements[1])
                if replacements[0] > rand_int:
                    self.map.symb[x][y] = self.common_symb
                    cur_square -= 1
            else:
                self.map[x][y].symb = symb
                cur_square += 1
                if to_update:
                    self.map[x][y].update()
                    time.sleep(delay_between_updates)
            #print('\n' * 35)
            #self.print()
            #time.sleep(0.1)
            x += random.randint(-1, 1)
            y += random.randint(-1, 1)
            if x < 0 or y < 0 or x >= width or y >= height:
                x = start_x
                y = start_y
        return cur_square

    def GenerateWorld(self,
                      lands_to_generate=90, defined_land_square = 0,
                      landshafts=['~', '^', 'T'],
                      to_update=False, delay_between_updates=0):
        self.ClearWorld(to_update=to_update)
        ''' lands_to_generate must be given as percents
            world.square * percents // 100 will be generated into somthing'''

        if lands_to_generate < 0:
            lands_to_generate = random.randint(15, 90)
        if lands_to_generate > 100:
            lands_to_generate = 100

        cur_square = 0
        while cur_square < self.square * lands_to_generate // 100:
            if not defined_land_square:
                land_square = \
                    max(random.randint(self.square // 50, self.square // 10),
                        2)
            else:
                land_square = defined_land_square

            start_x = random.randint(0, self.width - 1)
            start_y = random.randint(0, self.height - 1)
            symb = random.choice(landshafts)
            other_symbs = set(landshafts) - {symb}
            generated = self.GenerateLandshaft(land_square, symb, start_x, 
                                                start_y, forbiden=other_symbs, 
                                                to_update=to_update,
                                                delay_between_updates=\
                                                delay_between_updates)
            cur_square += generated
            if cur_square * 1.01 >= self.square:
                for x in range(self.width):
                    for y in range(self.height):
                        if self.map[x][y].symb == self.common_symb:
                            self.map[x][y].symb = random.choice(landshafts)
                            if to_update:
                                self.map[x][y].update()
                            cur_square += 1
                break

    def ClearWorld(self, to_update=False):
        for x in range(self.width):
            for y in range(self.height):
                self.map[x][y].symb = self.common_symb
                if to_update:
                    self.map[x][y].update()
            
        return 0