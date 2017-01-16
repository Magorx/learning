def game(n, k):
    if n % (k + 1):
        return True
    return False


fin = open("stones.in", "r")
fout = open("stones.out", "w")

num = int(fin.readline())
count = 0
for i in range(num):
    n, k = list(map(int, fin.readline().split()))
    if game(n, k):
        count += 1
print(count, file=fout)

fin.close()
fout.close()