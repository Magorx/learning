#!/usr/bin/env python3
# -*- coding: utf-8 -*-

class Vector:
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z


class Map:
    def __init__(self, objects):
        self.objects = objects

    def add_object(self, obj):
        self.objects.append(obj)

    def get_txt(self):
        text = '{"name":"New Krunker Map","modURL":"","shadowR":1024,"ambient":"#97a0a8","light":"#f2f8fc","sky":"#dce8ed","fog":"#8d9aa0","fogD":900,"camPos":[0,0,0],"spawns":[],"objects":['

        for obj in self.objects:
            text += obj.get_txt() + ','
        text = text[:-1]
        text += ']}'
        return text


class Cube:
    def __init__(self, pos, scale):
        self.pos = pos
        self.scale = scale

    def get_txt(self):
        pos = self.pos
        scale = self.scale
        return '{' + '"p":[{},{},{}],"s":[{},{},{}]'.format(pos.x, pos.y, pos.z, scale.x, scale.y, scale.z) + '}'


cubes = []
for y in range(1, 10):
    c = Cube(Vector(0, y * 50, 0), Vector(111, 10, 100))
    cubes.append(c)
    c = Cube(Vector(50, y * 50 , 0), Vector(10, 50, 100))
    cubes.append(c)
    c = Cube(Vector(-50, y * 50 , 0), Vector(10, 50, 100))
    cubes.append(c)
    c = Cube(Vector(0, y * 50 , 50), Vector(100, 50, 10))
    cubes.append(c)
    c = Cube(Vector(0, y * 50 , -50), Vector(100, 50, 10))
    cubes.append(c)
m = Map(cubes)

fout = open('map.txt', 'w')
print(m.get_txt(), file=fout)
fout.close()
