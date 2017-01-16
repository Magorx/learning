def sim_check(arr):
    for i in range(len(arr)):
        for j in range(len(arr)):
            if arr[i][j] != arr[j][i] or (j == i and arr[i][j] == 1):
                return 0
    return 1


file = open("check.in", "r")
out = open("check.out", "w")

n = int(file.readline())
arr = [[0] * n for i in range(n)]
for i in range(n):
    num = file.readline().split()
    for j in range(n):
        arr[i][j] = int(num[j])

if sim_check(arr) == 0:
    print("NO", file=out)
else:
    print("YES", file=out)

file.close()
out.close()
