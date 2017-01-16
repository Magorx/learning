file = open("numbers.in", "r")
out = open("numbers.out", "w")

n = int(file.readline())
matrix = [[1 for i in range(10)] for j in range(n)]
matrix[0][0] = 0
for i in range(1, n):
    for j in range(10):
        if j == 0:
            matrix[i][j] = matrix[i - 1][j] + matrix[i - 1][j + 1]
        elif j == 9:
            matrix[i][j] = matrix[i - 1][j] + matrix[i - 1][j - 1]
        else:
            matrix[i][j] = (matrix[i - 1][j - 1] + matrix[i - 1][j] +
                            matrix[i - 1][j + 1])
print(sum(matrix[-1]), file=out)

file.close()
out.close()
