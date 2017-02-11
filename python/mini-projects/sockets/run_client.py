#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import socket
import pickle

class ground(object):
    def __init__(self):
        self.full = False
        self.symb = '.'

    def __repr__(self):
        return self.symb


def map_show(arr):
    print('\n' * 30)
    for i in arr:
        print(*i, sep='')


def main():
    sock = socket.socket()
    try:
        sock.connect(('127.0.0.1', 10005))
    except:
        sock.connect(('127.0.0.1', 10006))
    
    data = ''
    while True:
        data = input().encode('utf-8')
        if data == 'stop':
            sock.close()
            return 0
        sock.send(data)

        data = sock.recv(10000)
        arr = pickle.loads(data)
        map_show(arr)


if __name__ == "__main__":
    main()
