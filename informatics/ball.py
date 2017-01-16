length = int(input())
dp = [1] * (length + 1)
for i in range(1, len(dp)):
    dp[i] = sum(dp[max(i - 3, 0):i])
print(dp[-1])