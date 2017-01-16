fin = open("prevcomb.in", 'r')
fout = open("prevcomb.out", "w")

n, k = list(map(int, fin.readline().split()))
arr = list(map(int, fin.readline().split()))
nor = [i + 1 for i in range(len(arr))]
if nor == arr:
    print(0, file=fout)
    exit(0)
was = []
nn = n
for i in range(len(arr) - 1, -1, -1):
    if arr[i] - 1 != arr[i - 1]:
        arr[i] -= 1
        if arr[0] == 0:
            print(0, file=fout)
            exit(0)
        break
ar1 = arr[:i + 1]
ar2 = [0 for i in range(k - i - 1)]
for i in range(len(ar2)):
    ar2[i] = nn
    nn -= 1
ar2.reverse()
ar3 = ar1 + ar2
print(*ar3, file=fout)

fout.close()
