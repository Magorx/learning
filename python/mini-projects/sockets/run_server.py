#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import socket
import time
import pickle
from random import randint, choice

DIRS = [[], [-1, 0], [1, 0], [0, -1], [0, 1]]
UP = 1
DOWN = 2
LEFT = 3
RIGHT = 4

class ground(object):
    def __init__(self):
        self.full = False
        self.symb = '.'

    def __repr__(self):
        return self.symb

    def randomize(self):
        rand_int = randint(0, 7)
        if not rand_int:
            self.symb = '#'
            self.full = True


class thing(object):
    def __init__(self, symb, x, y):
        self.symb = symb
        self.x = x
        self.y = y
        arr[x][y].full = True
        arr[x][y].symb = self.symb

    def move(self, direction):
        x, y = self.x + DIRS[direction][0], self.y + DIRS[direction][1]
        if x < 0 or x >= MAP_X - 1 or y < 0 or y >= MAP_Y - 1:
            return 1
        if not arr[x][y].full:
            arr[x][y].full = True
            arr[x][y].symb = self.symb
            arr[self.x][self.y].full = False
            arr[self.x][self.y].symb = '.'
            self.x = x
            self.y = y

        return 0

    #def fire(self, direction):
        


def handle_input(s, conn):
    print(s)
    if s[0] == 'w':
        things[conn].move(UP)
    if s[0] == 's':
        things[conn].move(DOWN)
    if s[0] == 'a':
        things[conn].move(LEFT)
    if s[0] == 'd':
        things[conn].move(RIGHT)

def map_show(arr):
    print('==============')
    for i in arr:
        print(*i, sep='')

def map_generate():
    global arr
    arr = [[ground() for j in range(MAP_Y)] for i in range(MAP_X)]
    for i in range(MAP_X):
        for j in range(MAP_Y):
            arr[i][j].randomize()

MAP_X = 10
MAP_Y = 10
PLAYER_COUNT = 1

map_generate()
a = thing('@', 5, 5)

def main():
    global conns
    conns = {}
    sock = socket.socket()
    global things
    things = {}
    try:
        sock.bind(('', 10000))
    except:
        sock.bind(('', 10001))
    for i in range(PLAYER_COUNT):
        sock.listen(1)
        conn, adr = sock.accept()
        conns[adr] = conn
        things[conn] = thing(choice(['1', '2', '3', '4', ]), randint(0, MAP_X - 1), randint(0, MAP_Y - 1))
        sock = socket.socket()

    while True:
        for conn in conns.values():
            data = conn.recv(1024)
            print("GOT ", data)
            if data.decode() == 'stop':
                break
            if not data:
                continue
            handle_input(data.decode('utf-8'), conn)
            map_show(arr)
            data = pickle.dumps(arr, 2)
            conn.send(data)
    conn.close()


if __name__ == "__main__":
    main()
