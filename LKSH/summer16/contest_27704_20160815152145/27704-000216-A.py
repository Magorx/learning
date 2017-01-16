import sys


def my_rev():
    num = file.readline().strip()
    if num != "":
        my_rev()
    print(num, file=out, end=' ')


file = open("reverse.in", "r")
out = open("reverse.out", "w")

a = file.readline()
sys.setrecursionlimit(100000)
my_rev()


file.close()
out.close()
