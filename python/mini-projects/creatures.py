ANOTHER_PC = False

from math import ceil, floor
import sys

from random import randint
if not ANOTHER_PC:
    from colorama import init
    init(autoreset=True)
    print("\033[H\033[J", end="")


MAPSIZE_X = 10
MAPSIZE_Y = 10
DIRECTIONS = ["up", "down", "left", "right"]

class fruit():
    def __init__(self, mass, x, y):
        self.symb = "%"
        self.mass = mass
        self.x = x
        self.y = y
    def dissapear(self):
        if self.mass <= 0:
            world[self.x][self.y].food = floor()
            return "ok"
        return "alive"

def getchar():
    return sys.stdin.read(1)

class floor():
    symb = "."
    mass = 0

class ground():
    full = False
    cr = floor()
    food = floor()
    def __repr__(self):
        if not isinstance(self.cr, floor):
            return self.cr.symb
        if not isinstance(self.food, floor):
            return self.food.symb
        return "."

 
class creature():
    def __init__(self, mass, symb = chr(randint(ord("a"), ord("z"))),
                 x = 0, y = 0):
        self.symb = symb
        self.hp = 10
        self.power = 2
        self.defence = 0
        
        self.mass = mass
        self.spd = 5
        self.bmass = 0.2
        self.btime = 10
        
        self.x = x
        self.y = y
    def move(self, direction):
        if direction == "up":
            if not world[self.x - 1][self.y].full:
                world[self.x - 1][self.y].full = True
                world[self.x - 1][self.y].cr = self
                world[self.x][self.y].cr = floor_obj
                world[self.x][self.y].full = False
                self.x -= 1
                if self.x < 0:
                    self.x = MAPSIZE_X - 1
                return "up"
            else:
                return "stopped"
        
        if direction == "down":
            if self.x + 1 > MAPSIZE_X - 1:
                if not world[0][self.y].full:
                    world[0][self.y].full = True
                    world[0][self.y].cr = self
                    world[self.x][self.y].cr = floor_obj
                    world[self.x][self.y].full = False
                    self.x = 0
                    return "ok"
                else:
                    return "stopped"
            if not world[self.x + 1][self.y].full:
                world[self.x + 1][self.y].full = True
                world[self.x + 1][self.y].cr = self
                world[self.x][self.y].cr = floor_obj
                world[self.x][self.y].full = False
                self.x += 1
                return "down"
            else:
                return "stopped"
        
        if direction == "left":
            if not world[self.x][self.y - 1].full:
                world[self.x][self.y - 1].full = True
                world[self.x][self.y - 1].cr = self
                world[self.x][self.y].cr = floor_obj
                world[self.x][self.y].full = False
                self.y -= 1
                if self.y < 0:
                    self.y = MAPSIZE_Y - 1
                return "left"
            else:
                return "stopped"
        
        if direction == "right":
            if self.y + 1 == MAPSIZE_Y:
                if not world[self.x][0].full:
                    world[self.x][0].full = True
                    world[self.x][0].cr = self
                    world[self.x][self.y].cr = floor_obj
                    world[self.x][self.y].full = False
                    self.y = 0
                    return "right"
                else:
                    return "stopped"
            if not world[self.x][self.y + 1].full:
                world[self.x][self.y + 1].full = True
                world[self.x][self.y + 1].cr = self
                world[self.x][self.y].cr = floor_obj
                world[self.x][self.y].full = False
                self.y += 1
                return "right"
            else:
                return "stopped"
        
        return "err_dir"

    def die(self):
        if self.hp <= 0 or self.mass <= 0:
            world[self.x][self.y].full = False
            world[self.x][self.y].food = fruit(self.mass // 3, self.x, self.y)
            world[self.x][self.y].cr = floor()
            world[self.x][self.y].food.dissapear()
            return "dead"
        else:
            return "alive"

    def eat(self, direction = ""):        
        x = self.x
        y = self.y
        
        if not direction:
            fruit = world[x][y].food
            if isinstance(fruit, floor):
                    return "floor"
            
            self.mass += min(fruit.mass, max(self.power, 0))
            fruit.mass -= max(self.power, 0)
            if fruit.mass <= 0:
                fruit.dissapear()
                return "dissapeared"
            return "eaten"
        else:
            ret = self.move(direction)
            if ret == "err_dir":
                return "err_dir"
            
            x, y  = count_xy(x, y, direction)
            if ret in DIRECTIONS or ret == "ok":
                fruit = world[x][y].food
                if isinstance(fruit, floor):
                    return "floor"
                fruit.mass -= self.mass // 2
                if fruit.mass <= 0:
                    fruit.dissapear()
                    return "dissapeared"
                else:
                    return self.eat()
            elif ret == "stopped":
                other_cr = world[x][y].cr
                if isinstance(other_cr, floor):
                    return "what"                
                self.mass += min(other_cr.mass, max(self.power // 2, 0))
                other_cr.hp -= max(self.power - other_cr.defence, 0)
                other_cr.mass -= max(self.power // 3, 0)
                if other_cr.hp <= 0 or other_cr.mass <= 0:
                    other_cr.die()
                    return "killed"

    def split(self, mass, direction):
        if mass <= 0 or mass >= self.mass:
            return "err_mass"
        if direction not in DIRECTIONS:
            return "err_dir"

        x = self.x
        y = self.y

        ret = count_xy(x, y, direction)
        if ret == "err_xy":
            return "ERR"
        x, y = ret
        if world[x][y].full:
            return "full"

        world[x][y].full = True
        new_cr = creature(mass, symb = self.symb, x=x, y=y)
        world[x][y].cr = new_cr
                
        self.mass -= ceil(mass * 1.3)
        if self.mass <= 0:
            self.die()
        return "splitted"

    def sence_food(self):
        
    
#==HELP_FUNCTIONS===============================================================
def check_xy(x, y):
    if x >= 0 and x < MAPSIZE_X and y >= 0 and y < MAPSIZE_Y:
        return True
    return False

def count_xy(x, y, direction):
    if not check_xy:
        return "err_xy"
    if direction == "up":
        x -= 1
        if x < 0:
            x = MAPSIZE_X - 1
        return (x, y)
    if direction == "down":
        x += 1
        if x == MAPSIZE_X:
            x = 0
        return (x, y)
    if direction == "left":
        y -= 1
        if y < 0:
            y = MAPSIZE_Y - 1
        return (x, y)
    if direction == "right":
        y += 1
        if y == MAPSIZE_Y:
            y = 0
        return (x, y)
    return "err_dir"

def distance(x1, y1, x2, y2):
    testing_dist1 = max(x1 - x2, x2 -x1) + max(y1 - y2, y2 - y1)
    
    

def pprint(matr):
    for i in range(len(matr)):
        for j in range(len(matr[0])):
            print(matr[i][j], end="")
        print()

#==GAME_FUNCTIONS===============================================================

def init_world():
    for i in range(10):
        x = randint(0, MAPSIZE_X - 1)
        y = randint(0, MAPSIZE_Y - 1)
        if not world[x][y].full:
            world[x][y].food = fruit(randint(2, 4), x, y)

def handle_dir(string):
    if string == "w":
        return "up"
    if string == "s":
        return "down"
    if string == "a":
        return "left"
    if string == "d":
        return "right"

    return string

#==MAIN=========================================================================

floor_obj = floor()
world = [[ground() for i in range(MAPSIZE_Y)] for j in range(MAPSIZE_X)]
for i in range(len(world)):
    for j in range(len(world[0])):
        world[i][j].cr = floor_obj

cr = creature(5, x = 5, y = 5)

world[cr.x][cr.y].cr = cr
world[cr.x][cr.y].full = True

init_world()
pprint(world)
way = ""

while True:
    way = getchar()
    
    if way == "\n":
        continue
    if way == "q":
        break
    if way == "z":
        cr.die()
    
    if not ANOTHER_PC:
        print("\033[H\033[J", end="")
    
    way = handle_dir(way)
    if way in DIRECTIONS:
        cr.move(way)
    
    if way == "e":
        way = getchar()
        way = handle_dir(way)
        
        if way == " " or way == "\n":
            cr.eat()
        else:
            cr.eat(direction = way)

    if way == "b":
        way = getchar()
        way = handle_dir(way)
        print(cr.split(int(getchar()), way))
    
    pprint(world)
    print("===== m = ", cr.mass)
print("THE END")
