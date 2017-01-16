file = open("turtle-way.in", "r")
out = open("turtle-way.out", "w")

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
i = h
j = w

dp = [[0, 0] for i in range(w + h - 1)]
n = 1
dp[0][0] = h
dp[0][1] = w
while i != 1 or j != 1:
    if work[i - 1][j] < work[i][j - 1]:
        i -= 1
    else:
        j -= 1
    dp[n][0] = i
    dp[n][1] = j
    n += 1
dp.reverse()
for i in dp:
    print(*i, file=out)

file.close()
out.close()
