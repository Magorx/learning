#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from time import sleep
from random import randint, random, choice, shuffle
from math import sqrt
import tkinter as tk
import pygame

from color import *
from vector import *
from particle import *


SHIFTS = [[1, 0], [0, 1], [-1, 0], [0, -1]]


# OPTIONS - OPTIONS - OPTIONS - OPTIONS - OPTIONS - OPTIONS - OPTIONS - OPTIONS

FULL_SCREEN_MODE = True

COLOR = [255, 128, 64]

PIXEL_SIZE = 16 # less = more beautiful
PIXEL_CNT = 25 # TRY 20, 25, 32, 40
TICKS_PER_SECOND = 20 # FROM 10 TO 30 RECOMMENDED
PARTICLE_LIVETIME = 11 # 7-13, more = brighter and worse
PARTICLES_PER_TICK = 1 # CAN BE FROM 0 TO 1
MAGIC_COEF = 1 # <=1 - more light, >=1 - less light
MAGIC_POWER = 1.1 # how fast light is extinguished

# OPTIONS - OPTIONS - OPTIONS - OPTIONS - OPTIONS - OPTIONS - OPTIONS - OPTIONS


class Pixel():
    def __init__(self, world, x, y, color):
        self.world = world
        self.x = x
        self.y = y
        self.color = color.cp()
        self.delayed_color = self.color.cp()
        self.active = True
        
        self.rect = pygame.Rect(x * PIXEL_SIZE + 1, y * PIXEL_SIZE + 1, PIXEL_SIZE, PIXEL_SIZE)
        pygame.draw.rect(screen, self.color.to_rgb(), self.rect)

    def tick(self):
        if not self.active:
            return

        if not self.color == self.delayed_color:
            self.rect = pygame.Rect(self.x * PIXEL_SIZE + 1, self.y * PIXEL_SIZE + 1, PIXEL_SIZE, PIXEL_SIZE)
            pygame.draw.rect(screen, self.delayed_color.to_rgb(), self.rect)
            self.delayed_color = self.color.cp()

    def neighbours_to_active(self):
        for i in range(len(SHIFTS)):
            dx, dy = SHIFTS[i]
            nx = (self.x + dx) % self.world.width
            ny = (self.y + dy) % self.world.height
            self.world.field[nx][ny].active = True

class World():
    def __init__(self, width, height, livetime=60, tps=10, fullscreen=False):
        self.width = width
        self.height = height
        self.square = width * height
        self.livetime = livetime
        self.tps = tps
        self.fullscreen = fullscreen

        self.field = [[None for i in range(height)] for j in range(width)]
        self.tickable = []

        for x in range(width):
            for y in range(height):
                color = Color(0, 0, 0)
                self.field[x][y] = Pixel(self, x, y, color)
                self.tickable.append(self.field[x][y])

        self.particles = []

    def start(self):
        for i in range(10000000):
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    exit(0)
            self.tick()

    def tick(self):
        for i in range(self.square):
            x = i % self.width
            y = i // self.width
            pxl = self.field[x][y]
            pxl.delayed_color = pxl.color
            for part in self.particles:
                d = Vector(x, y, 0).dist(part.coords)
                if d == 0:
                    d = 1
                pxl.delayed_color = (pxl.delayed_color + part.color * (1/d**MAGIC_POWER)) * (1/MAGIC_COEF)
                
            self.field[x][y].tick()

        if False:
            for x in range(self.width):
                for y in range(self.height):
                    pxl = self.field[x][y]
        
        for it in self.tickable:
            it.tick()
        pygame.display.flip()

def free(s):
    return

def main():
    global screen
    
    pygame.init()
    pygame.display.set_caption("VSL")
    screen = pygame.display.set_mode((PIXEL_SIZE * PIXEL_CNT, PIXEL_SIZE * PIXEL_CNT))
    pygame.display.flip()   
    
    tps = TICKS_PER_SECOND
    height = PIXEL_CNT
    width = height
    w = World(width, height, tps=tps)
    s = ParticleSource(w, Vector(width // 2, int(height * 0.9), 0), color_from_rgb(COLOR), color_from_rgb(COLOR), fire, particles_per_tick=PARTICLES_PER_TICK, particles_livetime=PARTICLE_LIVETIME)
    s.spawn_particle()
    w.tickable.append(s)
    w.start()
    
main()