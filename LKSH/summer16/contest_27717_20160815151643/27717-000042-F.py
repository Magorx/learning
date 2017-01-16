file = open("hoca.in", "r")
out = open("hoca.out", "w")

n = int(file.readline())
arr = ([[0] * (n + 1)] + [[0] + [0 for elem in range(n)] for i in range(n)])
arr[1][1] = 1
ans = 0
for i in range(1, n + 1):
    for j in range(1, n + 1):
        if not (i == 1 and j == 1):
            arr[i][j] = (arr[i - 1][j] + arr[i][j - 1]) % 9929
for i in range(1, n + 1):
    for j in range(1, n + 1):
        ans = (ans + arr[i][j] * arr[n - j + 1][n - i + 1]) % 9929
print(ans, file=out)

file.close()
out.close()
