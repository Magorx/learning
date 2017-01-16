import socket
import re
import socketserver

regexp = re.compile(r"[1-9]([0-9])*[\+\-\*][1-9]([0-9])*")

class MyHandler(socketserver.BaseRequestHandler):
    def handle(self):
        print('Client connected', self.client_address)
        data = self.request.recv(1024)
        data = data.decode()
        print(data)
        ret = re.fullmatch(regexp, data[:len(data) - 1])
        if ret:
            self.request.send(str(eval(data)).encode())
        else:
            self.request.send("OH! invalid expression!".encode())


class MyServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
    allow_reuse_address = True


server = MyServer(('0.0.0.0', 10001), MyHandler)
server.serve_forever()