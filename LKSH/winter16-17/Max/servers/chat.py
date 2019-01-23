#!/usr/bin/env python
# -*- coding: utf-8 -*-

import socket
import re
import socketserver
import requests

regexp = re.compile(r"[1-9]([0-9])*[\+\-\*][1-9]([0-9])*")
ID = dict()
# ID["172.16.101.64"] = "OsCar"
# ID["172.16.101.51"] = "Bee"
# ID["172.16.102.21"] = "Maximus"
# ID["172.16.101.59"] = "AndreY Gain"
# ID["172.16.101.57"] = "Barbara"
coc = []


class MyHandler(socketserver.BaseRequestHandler):
    def handle(self):
        itr = 0
        print('Client connected', self.client_address)
        if self.client_address[0] not in ID:
            self.request.send(b"What is you name (for this seession)? \n")
            name = self.request.recv(10)
            name = name.decode()
            ID[self.client_address[0]] = name[:len(name) - 1]
        name = ID[self.client_address[0]]
        coc.append(self.request)
        while True and itr < 100:
            data = self.request.recv(1024)
            data = data.decode("utf-8")
            if not data:
                continue
            data = name + " : " + data
            #self.request.send(str(name + " : ").encode())
            print(data)
            #ans = input().encode()
            data = data.encode("utf-8")
            for i in coc:
                if i != self.request:
                    i.send(data)
            # self.request.send(data)
            itr += 1


class MyServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
    allow_reuse_address = True


server = MyServer(('0.0.0.0', 10006), MyHandler)
server.serve_forever()
