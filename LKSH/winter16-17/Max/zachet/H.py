fin = open("c3po.in", "r")
fout = open("c3po.out", "w")

a, b = list(map(int, fin.readline().split()))
if a != b:
    print("FIRST", file=fout)
    fout.close()
    exit(0)
if a == b:
    if a % 2:
        print("FIRST", file=fout)
        fout.close()
        exit(0)
    else:
        print("SECOND", file=fout)
        fout.close()
        exit(0)

fout.close()


        print(*arr, file=fout)
        exit(0)
else:
    if arr[0] > 1:
        arr[0] -= 1
        ar = [0 for i in range(k - 1)]
        for j in range(len(ar)):
            ar[j] = n
            n -= 1
            ar.reverse()
        arr = [arr[0]] + ar
if 0 in arr:
    print(0, file=fout)
    exit(0)
print(*arr, file=fout)