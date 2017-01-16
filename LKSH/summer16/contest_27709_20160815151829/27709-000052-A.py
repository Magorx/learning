from collections import deque


file = open("queue.in", "r")
out = open("queue.out", "w")

file.readline()
string = file.readline()
queue = deque()
while string:
    if string[0] == "+":
        string = string[2:]
        queue.append(int(string))
    if string[0] == "-":
        print(queue.popleft(), file=out)
    string = file.readline()

file.close()
out.close()
