#!/usr/bin/env python
# -*- coding: utf-8 -*-

import socket
import socketserver
import threading

# Create TCP client

# s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

def send():
    it = 1
    while it:
        it += 1
        s.send(input().encode())


def hear():
    it = 1
    while it:
        it += 1
        print(s.recv(100))


s = socket.socket()
print("What's your name? ")
s.connect(('0.0.0.0', 10006))
itt = 0

th1 = threading.Thread(target=send)
th2 = threading.Thread(target=hear)
th2.start()
th1.start()
while True and itt < 100:
    string = input()
    s.send(string.encode())
    itt += 1

#     answer = s.recv(1024)
#     print(answer.decode())