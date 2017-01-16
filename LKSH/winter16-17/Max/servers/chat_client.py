import socket
import socketserver
import threading

# Create TCP client

# s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

def send():
    it = 0
    while it < 100:
        it += 1
        s.send(input().encode())


def hear():
    it = 0
    while it:
        it += 1
        print(s.recv(100))


s = socket.socket()
print("What's your name? ")
s.connect(('10.255.0.63', 10005))
itt = 0

th1 = threading.Thread(terget=send)
th2 = threading.Thread(target=hear)
th2.start()
th1.start()
 while True and itt < 100:
     string = input()
     s.send(string.encode())
    itt += 1

#     answer = s.recv(1024)
#     print(answer.decode())