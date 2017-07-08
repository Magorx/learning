fin = open("input.txt", "r")
fout = open("output.txt", "w")

n, m = [int(i) for i in fin.readline().split()]
string = fin.readline()
arr = [0] * n
while string:
    start, end = [(int(i) - 1) for i in string.split()]
    arr[start] += 1
    arr[end] += 1
    string = fin.readline()
print(*arr, file=fout)

fin.close()
fout.close()