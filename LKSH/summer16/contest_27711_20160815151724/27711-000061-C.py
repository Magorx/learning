file = open("lis.in", "r")
out = open("lis.out", "w")

n = int(file.readline())
arr = [int(i) for i in file.readline().split()]
work = [1] * len(arr)
work[0] = 1
for i in range(n):
    for j in range(i, -1, -1):
        if arr[i] > arr[j] and work[i] <= work[j]:
            work[i] = work[j] + 1
print(max(work), file=out)

file.close()
out.close()
