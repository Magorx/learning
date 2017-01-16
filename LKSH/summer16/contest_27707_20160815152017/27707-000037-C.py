file = open("mtoal.in", "r")
out = open("mtoal.out", "w")

n = int(file.readline())
arr = [[0] * n for i in range(n)]
ans = [[] for i in range(n)]

for i in range(n):
    num = file.readline().split()
    for j in range(n):
        arr[i][j] = int(num[j])

for i in range(n):
    for j in range(n):
        if arr[i][j] == 1:
            ans[i].append(j + 1)

for i in range(len(ans)):
    print(len(ans[i]), *ans[i], file=out)

file.close()
out.close()
