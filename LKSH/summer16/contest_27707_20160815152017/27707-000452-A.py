file = open("lights.in", "r")
out = open("lights.out", "w")

n, m = [int(i) for i in file.readline().split()]
string = file.readline()
arr = [0] * n
while string:
    start, end = [(int(i) - 1) for i in string.split()]
    arr[start] += 1
    arr[end] += 1
    string = file.readline()
print(*arr, file=out)

file.close()
out.close()
