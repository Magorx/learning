import random
import time
import tkinter
from PIL import Image, ImageTk

ERR_INVALID_COORDS = -100
ERR_ARGS = -99

STANDART_WORLD_WIDTH = 15
STANDART_WORLD_HEIGHT = 15

SIDE_PX = 50
ERROR = -1


class Tyle(object):
    def __init__(self, symb='.'):
        self.symb = symb
    
    def __repr__(self):
        return self.symb


class WorldTyle(Tyle):
    def __init__(self, world, x, y, symb='.'):
        self.world = world
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
            world.square * percents // 100 will be generated'''

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


class TkWorldTyle(WorldTyle):
    def __init__(self, world, canvas, x=0, y=0, symb='.', prev_tyle=None):
        self.world = world
        self.canvas = canvas
        self.info_window = None

        if prev_tyle is None:
            super(TkWorldTyle, self).__init__(world, x, y, symb=symb)
        else:
            self.x = prev_tyle.x
            self.y = prev_tyle.y
            self.symb = prev_tyle.symb
            self.full = prev_tyle.full

    def choose_texture_name(self):
        symb = self.symb
        if symb == '^':
            self.texture_name = 'mountain'
        elif symb == 'T':
            self.texture_name = 'tree'
        elif symb == '~':
            self.texture_name = 'water'
        elif symb == '.':
            self.texture_name = 'road'
        else:
            self.name = 'ERROR'
            return ERROR

        return 0

    def set_texture(self):
        try:
            self.texture = self.world.textures[self.texture_name]
        except:
            print('! == [ERR][tyle] wrong texture name -> call TkWorldTyle.choose_texture_name(' + self.texture_name + ')')

            if self.choose_texture_name() == ERROR:
                print('! == [ERR][tyle] failed calling\
                      self.choose_texture_name')
                return ERROR
            else:
                self.texture = self.world.textures[self.texture_name]

        return 0

    def set_image(self, image=None):
        self.delete_image()

        if image is not None:
            try:
                self.image = self.canvas.create_image(0, 0, anchor='nw',
                                                      image=image)
            except:
                print('! == [ERR][tyle] failed setting input image')
                return ERROR
            return 0

        try:
            self.image = self.canvas.create_image(0, 0, anchor='nw',
                                              image=self.texture)
        except:
            print('! == [ERR][tyle] wrong texture -> call self.set_texture')
            if self.set_texture() == ERROR:
                print('! == [ERR][tyle] failed calling self.set_texture')
            else:
                self.image = self.canvas.create_image(0, 0, anchor='nw',
                                                      image=self.texture)
        return 0

    def delete_image(self):
        try:
            self.image.delete()
        except:
            return ERROR
        return 0

    def update(self):
        self.choose_texture_name()
        self.set_texture()
        if self.set_image() == ERROR:
            print('! == [ERR][tyle] failed updating')
            return ERROR

    def deselect(self):
        try:
            self.info_window.destroy()
        except:
            pass

        self.update()


class TkWorld(World):
    def __init__(self, width, height, tyle_type=TkWorldTyle, common_symb='.',
                 prev_world=None,
                 side_px=SIDE_PX,
                 pre_generated=False,
                 window=None,
                 textures=None, pil_images=None):
        super(TkWorld, self).__init__(width, height, tyle_type, common_symb)
        if prev_world is None or pre_generated:
            prev_world = World(STANDART_WORLD_WIDTH,
                               STANDART_WORLD_HEIGHT)
        if pre_generated:
            prev_world.GenerateWorld()

        if window is None:
            window = tkinter.Tk()
            window.config(width=STANDART_WORLD_WIDTH * SIDE_PX,
                          height=STANDART_WORLD_HEIGHT * SIDE_PX)
            window.protocol("WM_DELETE_WINDOW", exit)

        if textures is None or pil_images is None:
            textures = {
                'road' : ImageTk.PhotoImage(Image.open('./textures/road.png')),
                'water' : ImageTk.PhotoImage(Image.open('./textures/water.png')),
                'mountain' : ImageTk.PhotoImage(Image.open('./textures/mountain.png')),
                'tree' : ImageTk.PhotoImage(Image.open('./textures/tree.png')),
                'chosen_corner' : ImageTk.PhotoImage(Image.open('./textures/chosen_corner.png'))
            }

            pil_images = {
                'road' : Image.open('./textures/road.png'),
                'water' : Image.open('./textures/water.png'),
                'mountain' : Image.open('./textures/mountain.png'),
                'tree' : Image.open('./textures/tree.png'),
                'chosen_corner' : Image.open('./textures/chosen_corner.png')
            }

        self.common_symb = prev_world.common_symb
        self.time = prev_world.time
        self.width = prev_world.width
        self.height = prev_world.height
        self.square = self.width * self.height
        self.map = [[0 for i in range(self.height)] for j in range(self.width)]

        self.root_window = window
        self.textures = textures
        self.pil_images = pil_images
        for x in range(self.width):
            for y in range(self.height):
                self.map[x][y] = tyle_type(
                    self,
                    tkinter.Canvas(self.root_window,
                        width=side_px, height=side_px,
                        bg='#FFFFFF'),
                    prev_tyle=prev_world.map[x][y])
        
        for x in range(self.width):
            for y in range(self.height):
                self.map[x][y].canvas.place(x=x*side_px, y=y*side_px)

    def full_update(self, to_bind=False):
        for x in range(self.width):
            for y in range(self.height):
                self.map[x][y].update()
                if to_bind:
                    self.map[x][y].canvas.bind('<Button-1>', self.map[x][y].select)



def main():
    pass


if __name__ == "__main__":
    main()
