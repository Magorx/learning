from math import factorial

fin = open("evenoddperm.in", 'r')
fout = open("evenoddperm.out", "w")

num = int(fin.readline())
arr = list(map(int, fin.readline().split()))
c1 = 0
c2 = 0

for i in arr:
    if i % 2:
        c1 += 1
    else:
        c2 += 1

print(factorial(c1) * factorial(c2), file=fout)


fout.close()