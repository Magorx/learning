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
# ID['172.16.101.86'] = "Masha"

coc = []
class MyHandler(socketserver.BaseRequestHandler):
    def handle(self):
        itr = 0
        print('Client connected', self.client_address)
        if self.client_address[0] not in ID:
            self.request.send(b"What is you name (for this seession)? \n")
            tryes = 0
            while tryes < 5:
                tryes += 1
                name = self.request.recv(10)
                try:
                    name = name.decode()
                except:
                    self.request.send(b"Invalid text, write only latin letters plz!\n")
                    continue
            ID[self.client_address[0]] = name[:len(name) - 1]
        name = ID[self.client_address[0]]
        coc.append(self.request)
        while True and itr < 100:
            data = self.request.recv(1024)
            try:
                data = data.decode()
            except:
                self.request.send(b"Invalid text, write only latin letters plz!\n")
                continue
            print(data)
            data = name + " : " + data
            #self.request.send(str(name + " : ").encode())
            print(data)
            # ans = input().encode()
            data = data.encode()
            for i in coc:
                if i != self.request:
                    try:
                        i.send(data)
                    except:
                        self.request.send(b"Sorry, some errors, try again plz(\n")

            #self.request.send(data)
            itr += 1


class MyServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
    allow_reuse_address = True


server = MyServer(('0.0.0.0', 10005), MyHandler)
server.serve_forever()