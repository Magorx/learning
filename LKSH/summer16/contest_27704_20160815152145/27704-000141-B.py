import sys


def hanoi(n, sourse, middle, destination):
    global out
    if n == 1:
        print(sourse, destination, file=out)
    else:
        hanoi(n - 1, sourse, destination, middle)
        print(sourse, destination, file=out)
        hanoi(n - 1, middle, sourse, destination)
        
file = open("hanoi.in", "r")
out = open("hanoi.out", "w")

sys.setrecursionlimit(10000)
number = numbers = [int(i) for i in file.readline().split()]
num = numbers[0]
hanoi(num, 1, 3, 2)

file.close()
out.close()