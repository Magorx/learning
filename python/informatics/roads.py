fin = open("input.txt", "r")
fout = open("output.txt", "w")

n = int(fin.readline())
arr = [[0] * n for i in range(n)]
for i in range(n):
    num = fin.readline().split()
    for j in range(n):
        arr[i][j] = int(num[j])
count = 0
for i in range(len(arr)):
    for j in range(len(arr)):
        if arr[i][j] == 1:
            count += 1
count //= 2
print(count, file=fout)

fin.close()
fout.close()