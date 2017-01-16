def rotate(mas, n, m):
    n, m = m, n
    arr = [[0] * n for i in range(m)]
    for i in range(n):
        for j in range(m):
            arr[j][n - i - 1] = mas[i][j]
    return arr


file = open("rotate.in", "r")
out = open("rotate.out", "w")

n, m = [int(i) for i in file.readline().split()]
mas = [[0] * n for i in range(m)]
for i in range(m):
    mas[i] = [int(i) for i in file.readline().split()]
arr = rotate(mas, n, m)
for i in arr:
    print(*i, file=out)

file.close()
out.close()
