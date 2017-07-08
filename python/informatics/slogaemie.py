import sys
sys.setrecursionlimit = 10000000000


def gen(n, ready = [], sm = 0):
    if sm == n:
        print(*ready, file=fout)
        return
    mx = n
    if ready:
        mx = ready[-1]
    for i in range(1, mx + 1):
        if i + sm <= n:
            gen(n, ready + [i], sm + i)


fin = open("input.txt", "r")
fout = open("output.txt", "w")

num = int(fin.readline())
gen(num)

fin.close()
fout.close()