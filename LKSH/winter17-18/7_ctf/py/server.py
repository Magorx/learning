#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import socket
import socketserver

class MyHandler(socketserver.BaseRequestHandler):
    def handle(self):
        print('Client connected', self.client_address)
        data = self.request.recv(100)
        self.request.send(data)
        self.request.send(b"How are you?")


class MyServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
    pass

def main():
    server = MyServer(('0.0.0.0', 10000), MyHandler)
    server.serve_forever()

if __name__ == "__main__":
    main()
