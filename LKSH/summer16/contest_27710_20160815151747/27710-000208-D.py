file = open("muggers.in", "r")
out = open("muggers.out", "w")

length, jump = [int(i) for i in file.readline().split()]
jump += 1
dp = [int(i) for i in file.readline().split()]
dp = [0] + dp
for i in range(1, len(dp)):
    dp[i] = min(dp[max(i - jump, 0):i]) + dp[i]
print(dp[-1], file=out)

file.close()
out.close()
