import sys


def get_all_subsets(s, i=0, chosen=None):
    if chosen is None:
        chosen = []
    if i == len(s):
        if chosen:
            print(len(chosen), *chosen, file = out)
    else:
        get_all_subsets(s, i + 1, chosen)
        chosen.append(s[i])
        get_all_subsets(s, i + 1, chosen)
        chosen.pop()


sys.setrecursionlimit(100000)
file = open("subsequences.in", "r")
out = open("subsequences.out", "w")

num = int(file.readline())
numbers = []
for i in range(num):
    numbers += [i + 1]
get_all_subsets(numbers)

file.close()
out.close()
