fin = open("stones.in", 'r')
fout = open("stones.out", "w")

a = int(fin.readline())
if a % 3 == 1:
    print(1, file=fout)
elif a % 3 == 2:
    print(1, file=fout)
elif a % 3 == 0:
    print(2, file=fout)

fout.close()