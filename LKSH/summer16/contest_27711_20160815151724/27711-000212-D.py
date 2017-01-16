file = open("lcs.in", "r")
out = open("lcs.out", "w")

n = int(file.readline())
subsequence1 = [int(i) for i in file.readline().split()]
m = int(file.readline())
subsequence2 = [int(i) for i in file.readline().split()]
matrix = ([[0] * (m + 1)] +
          [[0 for i in range(m + 1)] for i in range(n)])
for i in range(n):
    for j in range(m):
        matrix[i + 1][j + 1] = max(matrix[i + 1][j], matrix[i][j + 1])
        if subsequence1[i] == subsequence2[j]:
            matrix[i + 1][j + 1] = matrix[i][j] + 1
print(matrix[-1][-1], file=out)

file.close()
out.close()
