#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import pygame
from random import randint, choice
from time import sleep


DIRS = {'up': (0, -1), 'down': (0, 1), 'left': (-1, 0), 'right': (1, 0)}
BUTTON_TO_COMMAND_DICT = {'w': 'move up',
                          'a': 'move left',
                          's': 'move down',
                          'd': 'move right',
                          'f': 'fire',
                          ' ': 'fire'}

PLAYERS_CONTROL = [{pygame.K_w: 'move up',
                    pygame.K_a: 'move left',
                    pygame.K_s: 'move down',
                    pygame.K_d: 'move right',
                    pygame.K_q: 'rotate_module left',
                    pygame.K_e: 'rotate_module right',
                    pygame.K_SPACE: 'fire'},

                   {pygame.K_UP: 'move up',
                    pygame.K_LEFT: 'move left',
                    pygame.K_DOWN: 'move down',
                    pygame.K_RIGHT: 'move right',
                    pygame.K_RETURN: 'fire'}]

WINDOW_WIDTH = 800
WINDOW_HEIGHT = 500
UNIT_SPEED = WINDOW_WIDTH * WINDOW_HEIGHT / 1400000 # Super magic constant
TYLE_WIDTH = 50
TYLE_HEIGHT = 50
SPAWN_POINTS = [(5, 5),
                (WINDOW_WIDTH - TYLE_WIDTH - 5, WINDOW_HEIGHT - TYLE_HEIGHT - 5),
                (5, WINDOW_HEIGHT - TYLE_HEIGHT - 5),
                (WINDOW_WIDTH - TYLE_WIDTH - 5, 5)]
OBJECTS = []


def shift_by_direction(direction):
    if direction not in DIRS:
        return None

    if direction == 'up':
        return (-1, -2)
    elif direction == 'left':
        return (-2, -1)
    elif direction == 'down':
        return (-1, 0.1)
    elif direction == 'right':
        return (0.1, -1)


def button_to_command(button):
    for control_set in PLAYERS_CONTROL:
        if button in control_set:
            return control_set[button]


def control_set_by_key(key):
    for control_set in PLAYERS_CONTROL:
        if key in control_set:
            return PLAYERS_CONTROL.index(control_set)


def is_key_of_same_control_set_in_arr(arr, key):
    key_control_set = control_set_by_key(key)
    for i in range(len(arr)):
        if key_control_set == control_set_by_key(arr[i]):
            return True
    return False


def in_touch(x1, y1, x2, y2, w1, h1, w2, h2):
    if x1 >= x2 - w1 and x1 <= x2 + w2 and y1 >= y2 - h1 and y1 <= y2 + h2:
        return True
    else:
        return False


def collides(x1, y1, x2, y2, w1, h1, w2, h2):
    if x1 > x2 - w1 and x1 < x2 + w2 and y1 > y2 - h1 and y1 < y2 + h2:
        return True
    else:
        return False


def object_collide(obj, x2, y2, w2, h2):
    x1, y1 = obj.x, obj.your
    w1, h1 = obj.width, obj.height
    return collides(x1, y1, x2, y2, w1, h1, w2, h2)


def objects_collide(first, second):
    x1, y1, x2, y2 = first.x, first.y, second.x, second.y
    w1, h1, w2, h2 = first.width, first.height, second.width, second.height
    return collides(x1, y1, x2, y2, w1, h1, w2, h2)


def objects_in_touch(first, second):
    x1, y1, x2, y2 = first.x, first.y, second.x, second.y
    w1, h1, w2, h2 = first.width, first.height, second.width, second.height
    return in_touch(x1, y1, x2, y2, w1, h1, w2, h2)


class Movable(object):
    def __init__(self, x, y, sprite=None, speed=1, on_touch=None, on_collision=None,
                 on_window_touch=None, logic=None, direction='up',
                 sprite_name=''):
        self.x = x
        self.y = y
        if sprite is not None:
            self.width = sprite.get_rect().width
            self.height = sprite.get_rect().height
        self.direction = direction
        self.speed = speed
        self.sprite = sprite
        self.sprite_name = sprite_name

        self._on_touch = on_touch
        self._on_collision = on_collision
        self._on_window_touch = on_window_touch
        self.logic = logic

        OBJECTS.append(self)

    def _move(self, direction):
        if direction not in DIRS:
            return 'error'

        if self.direction != direction:
            if self.sprite_name:
                self.sprite = pygame.image.load(
                    './sprites/{}/{}.png'.format(self.sprite_name, direction))
            self.direction = direction

        delta_x, delta_y = DIRS[direction]
        delta_x *= self.speed
        delta_y *= self.speed
        x, y, = self.x, self.y
        new_x, new_y = x + delta_x, y + delta_y

        if (new_x + self.width > WINDOW_WIDTH or
           new_y + self.height > WINDOW_HEIGHT or
           new_x < 0 or new_y < 0):
            if self._on_window_touch is not None:
                self._on_window_touch()
            return None

        self.x = new_x
        self.y = new_y

        if self.collides():
            if self._on_collision is not None:
                self._on_collision(self.collides())
            self.x = x
            self.y = y

        if self.in_touch():
            if self._on_touch is not None:
                self._on_touch(self.in_touch())

    def collides(self):
        for obj in OBJECTS:
            if objects_collide(self, obj):
                if obj is self:
                    pass
                else:
                    return obj

    def in_touch(self):
        for obj in OBJECTS:
            if objects_in_touch(self, obj):
                if obj is self:
                    pass
                else:
                    return obj

    def render(self):
        screen.blit(self.sprite, (self.x, self.y))

    def delete(self):
        del OBJECTS[OBJECTS.index(self)]


class Base(pygame.sprite.Sprite):
    def __init__(self, sprite, hp, angle=0):
        self.rect = sprite.get_rect()
        self.width = self.rect.width
        self.height = self.rect.height
        self.sprite = sprite
        self.angle = angle
        self.modules = []
        self.modules_coords = []
        self.hp = hp

    def get_image(self):
        return self.sprite

class Module(pygame.sprite.Sprite):
    def __init__(self, sprite, angle=0, turn_speed=UNIT_SPEED/2):
        self.rect = sprite.get_rect()
        self.width = self.rect.width
        self.height = self.rect.height
        self.sprite = sprite
        self.angle = angle

    def get_image(self):
        image = pygame.transform.rotate(self.sprite, self.angle)
        self.rect = image.get_rect(center=self.rect.center)
        return image, self.rect


class Weapon(Module):
    def __init__(self, sprite, damage, hp, turn_speed=UNIT_SPEED/2):
        super(Weapon, self).__init__(sprite, turn_speed=turn_speed)
        self.damage = damage
        self.hp = hp
        self.turn_speed = turn_speed


class Unit(Movable):
    def __init__(self, x, y, base, modules, modules_coords, speed=UNIT_SPEED, angle=0, direction='up'):
        super(Unit, self).__init__(x, y, speed=speed, direction=direction)
        self.base = base
        self.width = base.width
        self.height = base.height
        self.modules = modules
        self.modules_coords = modules_coords
        self.last_shoot_time = 0
        self._on_collision = self.on_collision
        self.direction = direction

        self.hp = base.hp + sum(list(map(lambda obj: obj.hp, modules)))

    def install_module(self, x, y, module):
        self.modules.append(module)
        self.modules_coords.append((x, y))

    def move(self, direction):
        self._move(direction)

    def rotate_modules(self, direction):
        if direction == 'right':
            shift = 1
        elif direction == 'left':
            shift = -1
        else:
            return None

        for module in self.modules:
            print(module.turn_speed)
            module.angle += module.turn_speed * shift

    def on_collision(self, obj, called=False):
        if obj._on_collision is not None and not called:
            obj._on_collision(self, called=(not called))

    def fire(self, missle_type, speed=UNIT_SPEED*2):
        if pygame.time.get_ticks() - self.last_shoot_time < 1000:
            return None
        else:
            self.last_shoot_time = pygame.time.get_ticks()

        direction = self.direction
        delta_x, delta_y = DIRS[self.direction]
        shift_x, shift_y = shift_by_direction(direction)
        try:
            sprite = pygame.image.load(
                './sprites/{}/{}.png'.format(missle_type, direction))
        except Exception:
            print('ERROR finding missle_type "{}"'.format(missle_type))
            return None

        width = sprite.get_rect().width
        height = sprite.get_rect().height
        x = self.x + self.width / 2 + self.width / 2 * delta_x + \
            width / 2 * shift_x
        y = self.y + self.height / 2 + self.height / 2 * delta_y + \
            height / 2 * shift_y

        self.missle = Missle(self, x, y, sprite, speed=speed,
                             direction=direction, damage=self.damage)

    def die(self):
        self.delete()

    def handle_command(self, command):
        if command is None:
            return None
        command = command.split()

        if len(command) == 1:
            if command[0] == 'fire':
                self.fire('bullet')
        elif len(command) == 2:
            if command[0] == 'move':
                self.move(command[1])
            if command[0] == 'rotate_module':
                self.rotate_modules(command[1])

    def act(self):
        rect = self.base.sprite.get_rect()
        rect.x = self.x
        rect.y = self.y
        self.base.rect = rect
        print(self.base.rect)
        if self.hp <= 0:
            self.die()

    def render(self):
        base_rect = self.base.rect
        screen.blit(self.base.get_image(), (self.x, self.y))
        for i in range(len(self.modules)):
            image, rect = self.modules[i].get_image()
            x, y = self.x + self.modules_coords[i][0], self.y + self.modules_coords[i][1]
            rect.x = x
            rect.y = y
            rect.center = base_rect.center
            screen.blit(image, rect)


class Missle(Movable):
    def __init__(self, launcher, x, y, sprite, speed=UNIT_SPEED*2,
                 direction='up', damage=1):
        super(Missle, self).__init__(x, y, sprite, speed=speed,
                                     direction=direction)
        self.launcher = launcher
        self.damage = damage
        self._on_collision = self.on_collision
        self._on_touch = None
        self._on_window_touch = self.on_window_touch

    def move(self, direction):
        self._move(direction)

    def act(self):
        self.move(self.direction)

    def on_collision(self, obj, called=False):
        if isinstance(obj, Missle) and not called:
            obj.on_collision(obj, called=True)
        elif isinstance(obj, Unit):
            if obj is not self.launcher:
                obj.hp -= self.damage

        self.delete()

    def on_window_touch(self):
        self.delete()


class Player(object):
    def __init__(self, unit, control):
        self.unit = unit
        self.unit_alive = True
        self.control = control

    def act(self):
        if self.unit.hp <= 0:
            self.unit_alive = False


def main():
    print(UNIT_SPEED)
    global window
    global screen
    global hero

    window = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
    pygame.display.set_caption('Game')

    screen = pygame.Surface((WINDOW_WIDTH, WINDOW_HEIGHT))

    tank_sprite = pygame.image.load('./sprites/tank/tank.png')
    player_count = 1
    players = []

    for i in range(player_count):
        if i >= len(SPAWN_POINTS):
            print('not enough spawn points for all players')
            break
        if i >= len(PLAYERS_CONTROL):
            print('not enough controls for all players')
            break
        x, y = SPAWN_POINTS[i]
        base_sprite = pygame.image.load('./sprites/base/base.png')
        base = Base(base_sprite, 5)
        weapon_sprite = pygame.image.load('./sprites/weapon/weapon.png')
        weapon = Weapon(weapon_sprite, 5, 5)
        unit = Unit(200, 200, base, [weapon], [(0, 0)])
        player = Player(unit, PLAYERS_CONTROL[i])
        players.append(player)

    pygame.key.set_repeat(50, 1)
    done = False
    keys_active = []
    keys_down = []
    pygame.init()
    while not done:
        screen.fill((80, 80, 80))
        for obj in OBJECTS:
            try:
                obj.act()
            except Exception:
                pass
            obj.render()

        for player in players:
            player.act()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                done = True

            if event.type == pygame.KEYDOWN:
                key = event.key
                if key not in keys_active:
                    keys_active.append(key)
                else:
                    pass

            if event.type == pygame.KEYUP:
                key = event.key
                if key in keys_active:
                    del keys_active[keys_active.index(key)]

        for key in keys_active:
            for player in players:
                if key in player.control and player.unit_alive:
                    player.unit.handle_command(button_to_command(key))

        window.blit(screen, (0, 0))
        pygame.display.flip()


if __name__ == "__main__":
    main()
