file = open("half-degree.in", "r")
out = open("half-degree.out", "w")

n = int(file.readline())
arr = [[0] * n for i in range(n)]
ans = [[[0, 0]] * n for i in range(n)]
for i in range(n):
    num = file.readline().split()
    for j in range(n):
        arr[i][j] = int(num[j])

for i in range(len(arr)):
    for j in range(len(arr)):
        if arr[i][j] == 1:
            ans[i][j][0] += 1
        if arr[j][i] == 1:
            ans[i][j][1] += 1

for i in range(len(ans)):
    print(ans[i][j][1], ans[i][j][0], file=out)

file.close()
out.close()
