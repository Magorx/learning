file = open("genome.in", "r")
out = open("genome.out", "w")

n = int(file.readline())
arr = [[0, 0, 0, 0] for i in range(2)]
arr[0][0] = 1
arr[0][1] = 0
arr[0][2] = 1
arr[0][3] = 1
module = 10 ** 9 + 7
for i in range(n - 1):
    arr[1][0] = arr[0][2] + arr[0][3]
    arr[1][1] = arr[0][0] + arr[0][1] + arr[0][2]
    arr[1][2] = arr[0][1] + arr[0][2] + arr[0][3]
    arr[1][3] = arr[0][0] + arr[0][1] + arr[0][2] + arr[0][3]
    for j in range(len(arr[1])):
        arr[0][j] = arr[1][j] % module
print((arr[0][0] + arr[0][3]) % module, file=out)

file.close()
out.close()
