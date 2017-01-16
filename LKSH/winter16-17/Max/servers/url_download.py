import socket
import re
import socketserver
import requests

regexp = re.compile(r"[1-9]([0-9])*[\+\-\*][1-9]([0-9])*")

class MyHandler(socketserver.BaseRequestHandler):
    def handle(self):
        print('Client connected', self.client_address)
        data = self.request.recv(1024)
        data = data.decode()
        print(data)
        ans = requests.get(data)
        ans = ans.text.encode()
        self.request.send(ans)


class MyServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
    allow_reuse_address = True


server = MyServer(('0.0.0.0', 10002), MyHandler)
server.serve_forever()