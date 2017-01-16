import sys


def merge_sort(s, left=0, right=None, result=None):
    if result is None:
        result = [0] * len(s)
    if right is None:
        right = len(s)
    if right - left > 1:
        middle = (right + left) // 2
        merge_sort(s, left, middle, result)
        merge_sort(s, middle, right, result)
        merge(s, left, middle, right, result)


def key(turp):
    return turp[0]


def merge(s, left, middle, right, result):
    i = left
    j = middle
    for k in range(left, right):
        if i < middle and (j == right or key(s[i]) <= key(s[j])):
            result[k] = s[i]
            i += 1
        else:
            result[k] = s[j]
            j += 1
    for k in range(left, right):
        s[k] = result[k]


sys.setrecursionlimit(100000)
file = open("robots.in", "r")
out = open("robots.out", "w")

file.readline()
# num = [int(i) for i in file.readline().split()]
num = [tuple(int(i) for i in line.split()) for line in file]
merge_sort(num)
for i in num:
    print(*i, file=out)

file.close()
out.close()
