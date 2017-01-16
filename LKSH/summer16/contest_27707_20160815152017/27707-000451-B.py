file = open("rain.in", "r")
out = open("rain.out", "w")

n = int(file.readline())
arr = [[int(elem) for elem in file.readline().split()] for i in range(n)]
colors = [int(i) for i in file.readline().split()]
counter = 0
for i in range(n):
    for j in range(n):
        if arr[i][j] == 1:
            if colors[i] != colors[j]:
                counter += 1
print(counter // 2, file=out)

file.close()
out.close()
