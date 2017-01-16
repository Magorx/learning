file = open("turtle.in", "r")
out = open("turtle.out", "w")

h, w = [int(i) for i in file.readline().split()]
n = float("+inf")
arr = ([[n] * (w + 1)] +
       [[n] + [int(elem) for elem in file.readline().split()]
        for i in range(h)])
work = ([[n] * (w + 1)] +
        [[n] + [0 for elem in range(w)]
         for i in range(h)])

for i in range(1, h + 1):
    for j in range(1, w + 1):
        if i == 1 and j == 1:
            work[i][j] = arr[i][j]
        else:
            work[i][j] = min(work[i - 1][j], work[i][j - 1]) + arr[i][j]
print(work[-1][-1], file=out)

file.close()
out.close()
