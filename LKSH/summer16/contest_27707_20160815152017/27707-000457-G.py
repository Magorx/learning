file = open("check.in", "r")
out = open("check.out", "w")

n, m = [int(i) for i in file.readline().split()]
string = file.readline()
arr = [[0 for elem in range(n)] for i in range(n)]
done = 0
while string:
    start, end = [(int(i) - 1) for i in string.split()]
    if arr[start][end] == 1:
        print("YES", file=out)
        done = 1
        break
    arr[start][end] = 1
    string = file.readline()
if done == 0:
    print("NO", file=out)

file.close()
out.close()
