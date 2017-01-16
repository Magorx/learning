from math import factorial

fin = open("pascal.in", 'r')
fout = open("pascal.out", "w")

a = int(fin.readline())
a -= 1
arr = [factorial(a) // (factorial(a - i) * factorial(i))\
 for i in range(a + 1)]
print(*arr, file=fout)

fout.close()