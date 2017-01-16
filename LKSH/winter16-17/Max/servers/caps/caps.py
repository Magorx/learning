import socket
import socketserver

# Create TCP client

## s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# s = socket.socket()
# s.connect(('82.56.101.203', 10000))
# s.send(b"Hello\n")
# answer = s.recv(1024)
# print(answer.decode())

# Create TCP server

class MyHandler(socketserver.BaseRequestHandler):
    def handle(self):
        print('Client connected', self.client_address)
        while True:
            data = self.request.recv(1024)
            data = data.decode()
            ans = ""
            for i in range(len(data)):
                if data[i] in [chr(i) for i in range(ord("a"), ord("z") + 1)]:
                    ans = ans + chr(ord(data[i]) - 32)
                else:
                    ans = ans + data[i]
            self.request.send(ans.encode())


class MyServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
    allow_reuse_address = True


server = MyServer(('0.0.0.0', 10000), MyHandler)
server.serve_forever()