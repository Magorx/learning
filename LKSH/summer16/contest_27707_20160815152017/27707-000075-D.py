file = open("altom.in", "r")
out = open("altom.out", "w")

n = int(file.readline())
ans = [[0] * n for i in range(n)]
arr = [[] for i in range(n)]
for i in range(n):
    string = [int(i) for i in file.readline().split()]
    del string[0]
    for j in string:
        ans[i][j - 1] = 1
for i in ans:
    print(*i, file=out)

file.close()
out.close()
