fin = open("rect-union.in", "r")
fout = open("rect-union.out", "w")

ar = [[0 for i in range(210)] for j in range(210)]
num = int(fin.readline())
arr = []
for i in range(num):
    string = fin.readline()
    string = list(map(int, string.split()))
    for i in range(len(string)):
        string[i] += 105
    arr.append(string)
for ii in arr:
    for i in range(ii[0], ii[2]):
        for j in range(ii[1], ii[3]):
            ar[i][j] += 1

cnt = 0
for i in ar:
    for j in i:
        if j:
            cnt += 1
print(cnt, file=fout)

fin.close()
fout.close()