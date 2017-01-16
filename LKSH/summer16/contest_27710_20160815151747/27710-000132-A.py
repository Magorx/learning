file = open("grasshopper.in", "r")
out = open("grasshopper.out", "w")

length, jump = [int(i) for i in file.readline().split()]
dp = [1] * (length)
for i in range(1, len(dp)):
    dp[i] = sum(dp[max(i - jump, 0):i])
print(dp[-1], file=out)

file.close()
out.close()
