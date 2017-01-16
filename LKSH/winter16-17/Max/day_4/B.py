def pprint(arr):
    for i in range(len(arr)):
        print(i, ")", arr[i])


def find(arr, n):
    for i in range(len(arr)):
        if arr[i] == n:
            return i
    return -1


def dp_foo(n, k):
    if n <= 0:
        dp[n][k] = 0
        return 0
    if n <= k:
        dp[n][k] = 1
        return 1
    if dp[n][k] != -1:
        return dp[n][k]
    dp[n][k] = 0
    for i in range(1, k + 1):
        if dp_foo(n - i, i) == 0:
            dp[n][k] = 1
    return dp[n][k]


fin = open("sweets.in", "r")
fout = open("sweets.out", "w")

n, k = list(map(int, fin.readline().split()))
dp = [[-1 for j in range(k + 1)] for i in range(n + 1)]

done = 0
if n == k:
    done = k
if n % 2:
    done = 1

if done:
    print(done, file=fout)
else:
    dp_foo(n, k)
    for i in range(n - 1, n - k - 1, -1):
        if find(dp[i], 0) != -1 and find(dp[i], 1) == -1:
            print(n - i, file=fout)
            break
    else:
        print(0, file=fout)

fin.close()
fout.close()